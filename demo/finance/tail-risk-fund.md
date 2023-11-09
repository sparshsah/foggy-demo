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
