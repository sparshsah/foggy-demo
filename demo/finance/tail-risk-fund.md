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
   without also having to benchmark it to your personal portfolio's exposure to recession risk.

3. Prefer transparent instruments. Prefer a strategy that doesn't expect to require a lot of tactical trading churn, and, if possible,
   that uses liquid instruments that are easy to monitor.

## Strategies

Assuming that the benchmark is some risk-on portfolio, we'll suggest some strategies, in order
from cleanest hedge (and, therefore, also usually most expensive, since there's a lot of demand for this sort of mechanical insurance policy)
to dirtiest hedge (things that try to indirectly pick up on a potential "flight to quality/stability" by the animal spirits,
which will probably---but not necessarily---accompany a crash in your personal portfolio).
But notice that the very dirtiest hedges near the bottom are actually long-term _positive ER_ strategies!

To any of these, you could add a tactical timing component that takes the exposure off when your full alpha model thinks it's too expensive
(e.g. if put premia are too high relative to recent realized volatility).

It can also make sense to scale leverage with e.g. the VIX -- When volatility is elevated, loss magnitudes tend to be larger.
For example, if ex-ante vol is 10%, then quarterly vol is 10%/sqrt(4)=5%, so a -3STD quarterly loss is -15%.
But if ex-ante vol is 20%, then quarterly vol is 20%/sqrt(4)=10%, so a -3STD quarterly loss is -30%.
If you have a vanilla put, you're still protected, because the payoff is benchmarked to some fixed strike.
But if you have e.g. a trend-following strategy as a tail hedge, you might want to take up exposure to
increase the potential payoff from the hedge commensurately with the increase in potential losses in your personal portfolio.

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
    * The main idea here is to take advantage of the reliable spot-vol correlation: When prices fall, people tend to get more anxious and uncertain, so volatility spikes.
      And conversely, when big jumps happen, they tend to be toward the downside. This gives the VIX its reputation on CNBC as a "fear gauge".
      Of course, you will also profit in case there's a big move to the upside that triggers a volatility spike. (Note that this isn't unique to VIX futures. Puts are also long vol:
      Even with the puts above, if a big up-move triggers a vol spike in the underlying at some point before expiration, you will likely see a mark-to-market profit.)
    * Again, these tend to be expensive, because of the futures rolldown.
      The VRP is stronger for further-in-the-future expirations (another Volatility Smirk, in a different direction).
      Spot VIX is not tradable, so the spot-futures no-arbitrage relationship is not guaranteed.
      In fact, in reality you might see the VIX at 20pts while a 3-month VIX futures contract carries a futures price of $25 (neglect financing rates for simplicity).
      Now suppose the VIX stays flat, at expiry you are on the hook to pay the short counterparty $5, despite nothing happening.
      And even suppose that spot VIX actually jumps to 25pts by expiration: You will get nothing despite being "right" about the direction of the VIX.

* Long credit-default-swap index (CDX, e.g. CDX.NA.IG.05) which tracks default risk of corporate debt,
  or short ABX/CMBX which track _inverse_ default risk of residential/commercial mortgage-backed securities.
    * Related: Interest-Rate-Swap Spreads. These became popular "tail hedges" after they blew out in the 2008 GFC. They have since fallen out of favor a bit.
      The idea is that in an interest-rate swap, a company will agree to pay the fixed leg, which is essentially just the govie rate.
      But during bad times, people are afraid that the company will go bankrupt and be unable to fulfill its obligation.
      So people will demand higher-than-govie rates on the fixed leg from the company to compensate for the uncertainty.
      I am not overly familiar with this engineered instrument (not transparent), and I have to think hard about the dynamics (not intuitive).
      So I don't personally favor the Swap Spread, as it goes against my last two Principles from above.
      Stick to the CDX.

* Long safe-haven currencies (e.g. USD, JPY, CHF) vs a basket of emerging-market currencies.
  Because FX carry is generally the exact opposite portfolio, this strategy is sometimes called "short FX carry".

* Long safe-haven commodities like gold.

* Long Treasuries. Not only are Treasuries considered safe-haven assets, but also the Fed tends to drop rates during recessions to stimulate the economy.
  So you benefit from that. However, during times of stagflation, the Fed can obstinately fuck with your strategy by refusing to drop rates.
  So be careful here!

* Trend-following or macro-fundamental momentum.
  Weirdly, trend strategies have historically exhibited convexity relative to major risk asset classes _even when applied to completely-unrelated asset classes_.
  For example, a trend-following strategy on market-neutral stock-selection factors has exhibited convexity relative to SPX,
  despite the fact that each underlying factor portfolio is point-in-time hedged to have zero beta to SPX.
  But be careful, because obviously any Trend strategy runs the risk of being caught wrong-footed during abrupt reversals.

* Long "defensive quality" i.e. long quality stocks and short junk stocks (QMJ).
  Note: Something that _doesn't_ work well here is BAB, despite the fact that BAB is long low-volatility stocks and short high-volatility stocks.
  The problem is that BAB has to lever the low-vol stocks to pick up on the Sharpe ratio differential.
  In crises, we tend to see "beta compression", where betas compress toward unity across the board.
  In that scenario, you are 2x long A and 1x short B, where both have fallen -5% at the same time. Not a good outcome for you.

* Long risk-targeted whatever and short leverage-targeted whatever.
  Time after time, authors have shown that risk-targeting---whether for individual assets like SPX or entire strategies like FX carry---improves Sharpes.
  Not only that, the spread tends to be convex as well.
  For example, consider (A) a point-in-time 16%-vol targeted SPX allocation, and (B) a unit-levered SPX allocation.
  The former tends to have higher ER despite both realizing about 16% vol over the long term.
  Not only that, but it tends to outperform _more_ when the overall thing is falling. This one is closely related to the "trend following observation".
  Consider that (A) will take up exposures during low-vol times and take down exposures during high-vol times.
  But we've observed (spot-vol correlation) that low-vol times tend to be rising-price times and high-vol times tend to be falling-price times.
  So (A) will tend to take up exposures during rising-price times and take down exposures during falling-price times.
  Sounds like trend-following to me!
