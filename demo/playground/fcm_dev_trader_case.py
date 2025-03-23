from typing import Final
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd


# DATA AND SANITY CHECKS

DATA_FILENAME: Final[str] = "FCM_Dev Trader_Case.xlsx"
# TODO(sparsh): Not provided, but could look up actual financing rates
#     based on e.g. 3M TBill + assumed spread.
FINANCING_RATE: Final[pd.Series | float] = 0.0


def get_universe() -> pd.DataFrame:
    """Get coverage universe and some static data."""
    universe = pd.read_excel(
        DATA_FILENAME,
        sheet_name="Coverage Universe",
        usecols="B:M",
        index_col=0,
        skiprows=1,
    )
    universe["IPO Date"] = pd.to_datetime(
        universe["IPO Date"]
        .replace("#N/A Invalid Security", pd.NaT)
    )
    universe["Most Recent Trading Day"] = pd.to_datetime(
        universe["Most Recent Trading Day"]
    )
    # we are focused on 2024 for this analysis
    universe = universe.loc[
        (
            (universe["IPO Date"] <= "2024-01-01")
            | universe["IPO Date"].isna()
        )
        & (
            (universe["Most Recent Trading Day"] >= "2024-01-01")
            | universe["Most Recent Trading Day"].isna()
        ),
        :,
    ]
    return universe


universe = get_universe()


def get_mapping_from_bbg_to_fernbridge_ticker() -> pd.Series:
    return pd.Series(
        {
            bbg_ticker: fernbridge_ticker
            for fernbridge_ticker, bbg_ticker
            in universe["BBG Ticker to Fetch Info"].items()
        }
    )


mapping_from_bbg_to_fernbridge_ticker = get_mapping_from_bbg_to_fernbridge_ticker()


def get_excess_returns_for_index(
    financing_rate: pd.Series | float = FINANCING_RATE,
) -> pd.DataFrame:
    """Get excess returns for indices, provided a financing rate."""
    px = pd.read_excel(
        DATA_FILENAME,
        sheet_name="Raw Market Data",
        usecols="A:D",
        index_col=0,
        skiprows=2,
    )
    px = px.asfreq(freq="D")
    px = px.ffill()
    r = px / px.shift() - 1
    # Get rid of spurious zero returns over weekends.
    # TODO(sparsh): Take into account trading holidays
    #     using e.g. `holidays` or `pandas-market-calendars`.
    r = r.asfreq(freq="B")
    xr = r - financing_rate
    return xr


excess_returns_for_index = get_excess_returns_for_index()


def get_excess_returns_for_stocks(
    financing_rate: pd.Series | float = FINANCING_RATE,
) -> pd.DataFrame:
    """Get excess returns for stocks, provided a financing rate."""
    r = pd.read_excel(
        DATA_FILENAME,
        sheet_name="Raw Market Data",
        usecols="H,O:KY",
        index_col=0,
        skiprows=2,
    )
    # drop blank first row
    r = r.iloc[1:, :]
    r = r.dropna(axis="columns", how="all")
    r = r.asfreq(freq="D")
    r = r.fillna(0)
    # Get rid of spurious zero returns over weekends.
    # TODO(sparsh): Take into account trading holidays
    #     using e.g. `holidays` or `pandas-market-calendars`.
    r = r.asfreq(freq="B")
    xr = r - financing_rate
    # rename
    unmapped_tickers = xr.columns.difference(
        mapping_from_bbg_to_fernbridge_ticker.index
    )
    if not unmapped_tickers.empty:
        raise RuntimeError(f"Unmapped tickers! {unmapped_tickers}")
    xr = xr.rename(columns=mapping_from_bbg_to_fernbridge_ticker)
    xr = xr.reindex(columns=universe.index)
    # null out pre-IPO returns
    for ticker, ipo_date in universe["IPO Date"].items():
        ipo_date = ipo_date if pd.notna(ipo_date) else None
        xr[ticker] = xr.loc[ipo_date:, ticker]
    # null out post-trading returns
    for ticker, most_recent_trading_day in universe["Most Recent Trading Day"].items():
        most_recent_trading_day = (
            most_recent_trading_day
            if pd.notna(most_recent_trading_day)
            else None
        )
        xr[ticker] = xr.loc[:most_recent_trading_day, ticker]
    return xr


excess_returns_for_stocks = get_excess_returns_for_stocks()


def get_compounded_returns(
    excess_returns: pd.Series,
    financing_rate: pd.Series | float = FINANCING_RATE,
) -> pd.Series:
    total_returns = excess_returns + financing_rate
    compounded_returns = (
        (1 + total_returns.fillna(0))
        .cumprod()
        .iloc[-1, :]
        - 1
    )
    return compounded_returns


compounded_returns_for_index = get_compounded_returns(
    excess_returns=excess_returns_for_index,
)

compounded_returns_for_stocks = get_compounded_returns(
    excess_returns=excess_returns_for_stocks,
)


compounded_returns_for_stocks_binned = pd.qcut(
    compounded_returns_for_stocks,
    q=10,
    labels=range(1, 11),
)


def _get_pflio_dta() -> pd.DataFrame:
    """Pull info from "Portfolio" tab."""
    dta = pd.read_excel(
        DATA_FILENAME,
        sheet_name="Portfolio",
        usecols="B:K",
        index_col=[0, 2, 3],
        parse_dates=[3],
        skiprows=2,
    )
    dta = dta.sort_index()
    return dta


_pflio_dta = _get_pflio_dta()


def get_fund_nav() -> pd.Series:
    """Get fund-level NAV by day."""
    nav = _pflio_dta.loc[("Fund", "Fund Total"), "Combined_Exposure_EOD"]
    nav = nav.asfreq("D")
    nav = nav.ffill()
    nav = nav.asfreq("B")
    return nav


fund_nav = get_fund_nav()


def get_equal_wts() -> pd.DataFrame:
    """
    Get portfolio weights for an equal-weighted portfolio.

    Coverage can change as stocks IPO or retire.
    """
    stock_is_live = excess_returns_for_stocks.notna().astype(int)
    wts = stock_is_live.divide(
        stock_is_live.sum(axis="columns"),
        axis="index",
    )
    return wts


equal_wts = get_equal_wts()


def get_pflio_wts_eod() -> pd.DataFrame:
    """Get portfolio weights by day."""
    dta = _pflio_dta.loc["Stock", :]
    # sign
    true_sign_of_exposure = np.sign(dta["Combined_G/L_Daily"])
    unsigned_exposure = dta["Combined_Exposure_EOD"]
    recorded_sign_of_exposure = np.sign(unsigned_exposure)
    assert not (recorded_sign_of_exposure < 0).any(), "Assumed sign convention is wrong!"
    signed_exposure = true_sign_of_exposure * unsigned_exposure
    assert isinstance(signed_exposure, pd.Series), type(signed_exposure)
    signed_exposure = signed_exposure.unstack(level="Adjusted Label")
    signed_exposure = signed_exposure.asfreq(freq="D")
    signed_exposure = (
        signed_exposure
        .ffill()
        # if we've never held this position, propagate zero
        .fillna(0)
    )
    signed_exposure = signed_exposure.asfreq("B")
    wts = signed_exposure.divide(fund_nav, axis="index")
    unrecognized_tickers = wts.columns.difference(universe.index)
    if not unrecognized_tickers.empty:
        raise RuntimeError(unrecognized_tickers)
    wts = wts.reindex(columns=universe.index).fillna(0)
    return wts


pflio_wts_eod = get_pflio_wts_eod()


# CASE STUDY

print(compounded_returns_for_index)

# assumes no rebalancing
print(compounded_returns_for_stocks.mean())

# assumes daily rebalancing
equal_wt_xr = (equal_wts * excess_returns_for_stocks).sum(axis="columns")
print(
    (
        1
        + equal_wt_xr
    ).cumprod()
)


# assumes no rebalancing
for q in compounded_returns_for_stocks_binned.unique().sort_values():
    ret = compounded_returns_for_stocks.loc[
        compounded_returns_for_stocks_binned == q
    ]
    min_ret = ret.min()
    avg_ret = ret.mean()
    max_ret = ret.max()
    print(f"Decile {q}: {min_ret:.1%} ... {avg_ret:.1%} ... {max_ret:.1%}")


print(
    pd.Series(
        {
            q: compounded_returns_for_stocks.loc[
                compounded_returns_for_stocks_binned == q
            ].mean()
            for q in compounded_returns_for_stocks_binned.unique().sort_values()
        }
    ).apply(lambda pct: f"{pct:.1%}").to_frame().T
)


print(
    pd.DataFrame(
        {
            q: pd.Series(
                compounded_returns_for_stocks_binned[
                    compounded_returns_for_stocks_binned == q
                ].index,
            )
            for q in compounded_returns_for_stocks_binned.unique().sort_values()
        },
    ).fillna("")
)


pflio_wts_eod_avg = pflio_wts_eod.mean()


pflio_wts_eod_avg_where_live = pflio_wts_eod.where(
    pflio_wts_eod.abs() > 0
).mean()


pflio_wts_eod_abs_avg = pflio_wts_eod.abs().mean()


pflio_xr = (
    pflio_wts_eod  # .shift()
    * excess_returns_for_stocks
)
pflio_xr.loc[pflio_xr.index[-1]] = pflio_xr.iloc[-1, :].fillna(0)


print(
    equal_wt_xr.corr(
        pflio_xr.sum(axis="columns")
    )
)

print(
    equal_wt_xr.rolling(3).mean().corr(
        pflio_xr.sum(axis="columns").rolling(3).mean()
    )
)


print(equal_wt_xr.std()*261**0.5)

print(
excess_returns_for_index.corrwith(
    pflio_xr.sum(axis="columns")
)
)

print(
excess_returns_for_index.rolling(3).mean().corrwith(
    pflio_xr.sum(axis="columns").rolling(3).mean()
)
)


print(excess_returns_for_index.std() * 261**0.5)

print(pflio_xr.sum(axis="columns").std() * 261**0.5)

# beta
corr_to_beta_scaler = pflio_xr.sum(axis="columns").std() / excess_returns_for_index.std()
print(corr_to_beta_scaler)


print(
excess_returns_for_index.rolling(3).mean().corrwith(
    pflio_xr.sum(axis="columns").rolling(3).mean()
) * corr_to_beta_scaler
)

pflio_cret = (
    1 + pflio_xr + FINANCING_RATE
).cumprod().iloc[-1, :] - 1
pflio_cret = pflio_cret.loc[
    pflio_cret != 0
]
pflio_cret_df = pd.DataFrame(
    {
        "Contribution/Detraction (bps)": (pflio_cret * 1_00_00).round().astype(int),
        "Average Absolute Portfolio Weight (%)": (pflio_wts_eod_abs_avg[pflio_cret.index] * 1_00).round(1),
    }
)


print(pflio_cret_df.sort_values("Contribution/Detraction (bps)"))
print(pflio_cret_df.sort_values("Contribution/Detraction (bps)", ascending=False))

print(
# portfolio
(
    1
    + (
        pflio_wts_eod  # .shift()
        * excess_returns_for_stocks
    ).sum(axis="columns")
).cumprod()
)


for ticker in pflio_cret.index:
    _df = pd.DataFrame(
        {
            "r": excess_returns_for_stocks[ticker],
            "w": pflio_wts_eod[ticker],
            "rw": pflio_xr[ticker],
        }
    )
    df = _df.resample("M").mean()
    # rescale returns to be ~monthly total
    df[["r", "rw"]] *= 30
    is_notable = (df["r"].abs() > 0.10) & (df["w"].abs() > 0.04)
    is_contributor = df["rw"] > 0
    is_notable_contributor = is_notable & is_contributor
    if is_notable_contributor.any():
        print(ticker)
        print(df.loc[is_notable_contributor, :])
        print()
        for month in is_notable_contributor[is_notable_contributor].index.strftime("%Y-%m"):
            _df.loc[month, :].plot(kind="bar", title=f"{ticker} {month}")
            plt.show()
    del is_notable_contributor, is_contributor, is_notable, df, _df

for ticker in pflio_cret.index:
    _df = pd.DataFrame(
        {
            "r": excess_returns_for_stocks[ticker],
            "w": pflio_wts_eod[ticker],
            "rw": pflio_xr[ticker],
        }
    )
    df = _df.resample("M").mean()
    # rescale returns to be ~monthly total
    df[["r", "rw"]] *= 30
    is_notable = (df["r"].abs() > 0.10) & (df["w"].abs() > 0.04)
    is_detractor = df["rw"] < 0
    is_notable_detractor = is_notable & is_detractor
    if is_notable_detractor.any():
        print(ticker)
        print(df.loc[is_notable_detractor, :])
        print()
        for month in is_notable_detractor[is_notable_detractor].index.strftime("%Y-%m"):
            _df.loc[month, :].plot(kind="bar", title=f"{ticker} {month}")
            plt.show()
    del is_notable_detractor, is_detractor, is_notable, df, _df
