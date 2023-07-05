# Headline PM Stats for a Strategy

I try to be explicit, but if it's not specified you can safely assume that a stat is
(a) taken to be normalized by NAV, (b) annualized, and (c) if it's supposed to summarize a timeseries, take the mean.

Also, just be aware that once we've nailed down the definitions of these quantities,
it's much easier to work with position sizes not in terms of dol's,
but rather to normalize them by NAV and turn them into portfolio weights.
For example, defining `x[t,n]` to be the signed (long or short) position size in dol's at day `t` on asset `n`, with daycount 261,
and `nav[t]` to be the NAV in dol's at day `t`, so that `w[t,n] := x[t,n] / nav[t]` is the signed portfolio weight in percentage points (`0.01` = `1%`) at day `t` on asset `n`:
* Annualized turnover on NAV is just `w.abs().sum(axis="columns").mean() * 261`;
* Gross (rsp net) leverage on NAV is just `w.sum(axis="columns").mean()` (rsp `w.abs().sum(axis="columns").mean()`).

P.S. It turns out that, at 10% vol, 10x TO on GLev and 10x GLev are pretty reasonable for either a global-macro or a stock-selection strategy. Nice little back-of-the-envelope round figures.

Note: I had to replace all the "dollar signs" with the word "dol" because GitHub's markdown engine tries to support LaTeX notation.

## The stats

* I won't even mention alpha or beta. Your strategy's beta (to SPX, US10Y, or crude) should be either point-in-time (for XS strategies) or long-term (for TS strategies) zero ex-ante, and full-sample close to zero realized. Your pnl should be pure alpha.

* Net (Annualized) Sharpe Ratio: Net Sharpe, or Net SR.
* Net (Annualized) Expected Return (on NAV): Net ER.
* Gross (Annualized) Sharpe Ratio: Gross Sharpe, or Gross SR.
* Gross (Annualized) Expected Return (on NAV): Gross ER.
* (Annualized) Volatility (on NAV): Vol.
    * Of all, this one is most important to report both ex-ante and ex-post. Ex-ante can be summarized as a long-term median, or mean, or root-mean-square of daily point-in-time ex-ante vol (the latter exactly accounting for vol-of-vol effect assuming pnl is independent across days), but if ex-post comes in wildly different from ex-ante, you must understand why. For example, a manager who internally targets constant point-in-time ex-ante (annualized) vol of 10% might choose to disclose a target of 12% to make allowance for tail surprises like the quant crisis of 2007.
* (Annualized) Tcost (on NAV) (AKA "transaction cost" AKA "trading cost") := dol's of market impact + dol's of brokerage commissions and fees + dol's of transaction taxes, over the course of a year, normalized by dol's of NAV.
* (Annualized) Turnover on Gross Leverage: TO on GLev := dol's traded over the course of a year, normalized by long-term average dol's of gross leverage.
    * This gives a better sense of how aggressively the strategy trades than turnover on NAV. A strategy that goes in on AAPL at 10x leverage on day 0 then closes out the position all-at-once on day 261 (pretend NAV is dol1 and AAPL is flat over this period) trades at (|+dol10| + |-dol10|) / dol1 = 20x annualized turnover on NAV, which seems aggressive -- But it trades at just (|+dol10| + |-dol10|) / dol10 = 2x annualized turnover on gross leverage, which is quite modest. The tcost on NAV will of course be paid on the entire turnover on NAV, but it can be cleaner to attribute this to two separate components: (1) TO on GLev (how aggressively the strategy trades), and (2) GLev (how aggressively the strategy takes risk).
* (Annualized) Turnover on NAV: TO on NAV := dol's traded over the course of a year, normalized by dol's of NAV.
* Net Leverage on NAV: NLev := long-term mean dol's long - long-term mean dol's short, normalized by dol's of NAV. Also useful to report the long-term 95th percentile magnitude.
* Gross Leverage on NAV: GLev := long-term mean of "absolute dol position sizes summed over assets", normalized by dol's of NAV. Also useful to report the long-term 95th percentile magnitude.
    * Neither Net nor Gross Leverage tells the full story. They are really only a sanity check or a backstop to risk-taking as measured by ex-ante vol.
        * For example, suppose with dol1 NAV you're long dol1 of AAPL and long dol1 of MSFT. Both NLev and GLev are 2x, representatively indicating that you're taking about twice the risk of the average passive asset.
        * But now suppose you are long dol1 of AAPL and short dol1 of MSFT. You are so tightly hedged that the net leverage of 0x tells a more useful story than the gross leverage of 2x. This becomes even more obvious if you consider being long dol1 of AAPL in account A and short dol1 of AAPL in account B. You are perfectly hedged, with no market risk (counterparty risk or enterprise risk notwithstanding), whereas the gross leverage of 2x naively makes it seem like you're taking a lot of risk.
        * On the other hand, suppose you're instead long dol1 of AAPL and short dol1 of 30Y Treasury Bonds. You're very exposed to the global-risk-on factor, so the gross leverage of 2x tells a much more useful story than the net leverage of 0x.
        * And of course I'll reiterate that leverage caps are only a backstop, not an alternative, to ex-ante vol caps. Consider dol1 invested in SPY vs dol1 invested in a microcap tech stock: These positions look the same according to leverage, but in reality the latter is so concentrated ("un-diversified") that it's likely to be way riskier.
