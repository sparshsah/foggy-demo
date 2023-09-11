Using the ideas [here](https://github.com/sparshsah/foggy-demo/blob/main/demo/finance/pflio-food.pdf),
we can construct a "model portfolio":

1. Beta (say 0.80 Sharpe gross of fees)
    - We could use the [AQR Multi-Asset Risk-Parity Mutual Fund (AQRNX)](https://funds.aqr.com/funds/multi-asset/aqr-multi-asset-fund/aqrnx).
    - It targets 10% annualized volatility, which implies 0.80 * 10% = 8% annualized ER gross of fees.
    - It charges 1.06% annualized adjusted expense ratio, which implies 8% - 1.06% = 6.94% annualized ER net of fees.
    - That implies 6.94% / 10% which is about 0.70 Sharpe net of fees.
    - In light of our other (uncorrelated) choices, we'd want to allocate 0.70 / (0.70 + 0.35 + 0.15 + 0.15) = 52% mean-variance-optimal risk, which normalizing by 10% vol let's call it 5.2 units. So, in an unlevered portfolio we'd allocate 5.2 / (5.2 + 2.6 + 1.6 + 1.8) = 47% notional.

2. Macro (say 0.50 Sharpe gross of fees)
    - We could use the [AQR Managed Futures Mutual Fund (AQMNX)](https://funds.aqr.com/funds/alternatives/aqr-managed-futures-strategy-fund/aqmnx).
    - It targets 10% annualized volatility, which implies 0.50 * 10% = 5% annualized ER gross of fees.
    - It charges 1.51% annualized adjusted expense ratio, which implies 5% - 1.51% = 3.49% annualized ER net of fees.
    - That implies 3.49% / 10% which is about 0.35 Sharpe net of fees.
    - In light of our other (uncorrelated) choices, we'd want to allocate 0.35 / (0.70 + 0.35 + 0.15 + 0.15) = 26% mean-variance-optimal risk, which normalizing by 10% vol let's call it 2.6 units. So, in an unlevered portfolio we'd allocate 2.6 / (5.2 + 2.6 + 1.6 + 1.8) = 23% notional.

3. [Styles](https://github.com/sparshsah/foggy-demo/blob/main/demo/finance/styles4u.ipynb) (say 0.40 Sharpe gross of fees)
    - We could use the [Vanguard Market-Neutral Equity Mutual Fund (VMNFX)](https://investor.vanguard.com/investment-products/mutual-funds/profile/vmnfx).
    - It (I infer) targets 7% annualized volatility, which implies 0.40 * 7% = 2.8% annualized ER gross of fees.
    - It charges 1.83% annualized adjusted expense ratio, which implies 2.8% - 1.83% = 0.97% annualized ER net of fees.
    - That implies 0.97% / 7% which is about 0.15 Sharpe net of fees.
    - In light of our other (uncorrelated) choices, we'd want to allocate 0.15 / (0.70 + 0.35 + 0.15 + 0.15) = 11% mean-variance-optimal risk, which normalizing by 7% vol let's call it 1.6 units. So, in an unlevered portfolio we'd allocate 1.8 / (5.2 + 2.6 + 1.6 + 1.8) = 14% notional.

4. Special Situations (say 0.40 Sharpe gross of fees)
    - We could use the
      [AQR Diversified Arbitrage Mutual Fund (ADANX)](https://funds.aqr.com/funds/alternatives/aqr-diversified-arbitrage-fund/adanx).
    - It targets a bit less than 5% annualized volatility but with a bit more kurtosis than usual, so let's call it effectively 6% volatility, which implies 0.40 * 6% = annualized 2.4% ER gross of fees.
    - It charges 1.50% annualized adjusted expense ratio, which implies 2.4% - 1.50% = 0.90% annualized ER net of fees.
    - That implies 0.90% / 6% which is about 0.15 Sharpe net of fees.
    - In light of our other (uncorrelated) choices, we'd want to allocate 0.15 / (0.70 + 0.35 + 0.15 + 0.15) = 11% mean-variance-optimal risk, which normalizing by 6% vol let's call it 1.8 units. So, in an unlevered portfolio we'd allocate 1.8 / (5.2 + 2.6 + 1.6 + 1.8) = 16% notional.

All together, the unlevered portfolio yields 0.47\*0.0694 + 0.23\*0.0349 + 0.14\*0.0097 + 0.16\*0.0090 = 4.2% annualized ER net of fees, on sqrt((0.47^2)\*(0.10^2) + (0.23^2)\*(0.10^2) + (0.14^2)\*(0.07^2) + (0.16^2)\*(0.06^2)) = 5.4% annualized volatility, for a 4.2% / 5.4% = 0.78 Sharpe net of fees.
