# TAIL RISK FUND

author: [@sparshsah](https://github.com/sparshsah)

## Principles

When building a "tail risk" or "convexity" fund, I would start with three things:

1. Explicitly identify the reference index. That is, whose tails are you attempting to hedge, or in other words, with respect to what are you trying to be convex?
   An easy choice is just "SPX". It is representative of the global risk-on-risk-off factor, and it's easy to get historical data on it.
   But if you don't have a lot of equity risk in your portfolio, then a "tail risk" fund tied to SPX isn't really much different from any old absolute-return fund to you.
   And on the other hand if you _do_ have a lot of equity risk but it's all foreign small-caps, then you might be taking a lot of "basis", i.e.
   your tail risk fund could pay off despite very muted moves in your personal portfolio, or, in the asymetrically worse case,
   it could _fail to pay off_ despite violent gyrations in your personal portfolio.

2. Focus on intuition. It's 2023Q4 and I have a lot of smart friends putting on a US yield-curve steepener as an alpha bet.
   That makes sense to me, but this is _not_ a very obvious convexity bet to me, even conditional on our high-and-inverted yield curve.
   It's hard enough to decide the optimal points to use (10Y-1Y? 5Y-2Y?) and leverage to apply,
   without having to benchmark it to your personal portfolio's exposure to recession risk.

3. Prefer transparent instruments. Prefer a strategy that doesn't expect to require a lot of tactical trading churn, and, if possible,
   that uses liquid instruments that are easy to monitor.

## Strategies

Assuming that the benchmark is some risk-on portfolio, we'll suggest some strategies, in order
from cleanest hedge (and, therefore, also usually most expensive, since there's a lot of demand for this sort of mechanical insurance policy)
to dirtiest hedge (things that try to indirectly pick up on a potential "flight to quality/stability" by the animal spirits,
which will probably---but not necessarily---accompany a crash in your personal portfolio).

* Long puts (or calls). There are two considerations here:
    * Despite appearances, these are not "perfect". For example, say you buy a Dec 15 put on a stock.
      On Dec 10, the company announces that it will be releasing big news after Christmas.
      People are nervous that it might be something like Meta's widely-panned pivot to the metaverse, and the volatility of your stock jumps.
      You probably realize some mark-to-market gains before Dec 15 simply thanks to the vol spike, and maybe the put even expires in-the-money.
      But now you have to roll forward into a Mar 15 put (or else just go commando), and this means paying the new very-high option premium (implied-vol spike).
    * Over the long term, these tend to be expensive relative to the amount of protection you get: This is the well-documented Volatility Risk Premium.
      And in fact, it gets worse as you go further out-of-the-money: This is the well-documented Volatility Smirk.
      Roni Israelov argues that the slow bleed of a naive put-protection strategy decreases your long-term ER without a commensurate decrease to things like max drawdown.
      On the other hand, Vineer Bhansali shows that this tradeoff can be much improved---maybe even become ER-_enhancing_---with some reasonably-simple systematic trading rules.
* Long volatility-index futures.
