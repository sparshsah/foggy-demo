Using the ideas [here](https://github.com/sparshsah/foggy-demo/blob/main/demo/finance/pflio-food.pdf),
we can construct a "model portfolio":

Beta (say 0.65 Sharpe net of reasonable fees) at 50% risk allocation
  - We could use the
    [AQR Multi-Asset Risk-Parity Mutual Fund (AQRNX)](https://funds.aqr.com/funds/multi-asset/aqr-multi-asset-fund/aqrnx),
    which charges 1.06% adjusted expense ratio.
  - It targets % annualized volatility,
    so in light of our other choices,
    we'd allocate about 48% notional in an unlevered portfolio.
Macro (say 0.30 Sharpe net of reasonable fees) at 20% risk allocation
  - We could use the
    [AQR Managed Futures Mutual Fund (AQMNX)](https://funds.aqr.com/funds/alternatives/aqr-managed-futures-strategy-fund/aqmnx),
    which charges 1.51% adjusted expense ratio.
  - It targets 10% annualized volatility,
    so in light of our other choices,
    we'd allocate about 19% notional in an unlevered portfolio.
3. [Styles](https://github.com/sparshsah/foggy-demo/blob/main/demo/finance/styles4u.ipynb) (say 0.25 Sharpe net of reasonable fees) at 20% risk allocation
  - We could use the
    [Vanguard Market-Neutral Equity Mutual Fund (VMNFX)](https://investor.vanguard.com/investment-products/mutual-funds/profile/vmnfx),
    which charges 1.83% adjusted expense ratio.
  - It (I infer) targets 7% annualized volatility,
    so in light of our other choices,
    we'd allocate about 19% notional in an unlevered portfolio.
4. Special Situations (say 0.25 Sharpe net of reasonable fees) at 15% risk allocation
  - We could use the
    [AQR Diversified Arbitrage Mutual Fund (ADANX)](https://funds.aqr.com/funds/alternatives/aqr-diversified-arbitrage-fund/adanx),
    which charges 1.50% adjusted expense ratio.
  - It effectively targets a bit less than 5% annualized volatility but with a bit more kurtosis than usual,
    so in light of our other choices,
    we'd allocate about 14% notional in an unlevered portfolio.
