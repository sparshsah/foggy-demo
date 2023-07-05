# Headline PM Stats for a Strategy

I try to be explicit, but if it's not specified you can safely assume that a stat is
(a) taken to be normalized by NAV, (b) annualized, and (c) if it's supposed to summarize a timeseries, take the mean.
Also, just be aware that once we've nailed down the definitions of these quantities,
it's much easier to work with position sizes not in terms of $'s,
but rather to normalize them by NAV and turn them into portfolio weights.
For example, defining `w[t,n]` to be the signed portfolio weight at day `t` on asset `n`, with daycount 261:
Annualized turnover on NAV is just `w.abs().sum(axis="columns").mean() * 261`;
Similarly, gross (rsp net) leverage on NAV is just `w.sum(axis="columns").mean()` (rsp `w.abs().sum(axis="columns").mean()`).

* Net (Annualized) Sharpe Ratio
* Net (Annualized) Expected Return on NAV
* Gross (Annualized) Sharpe Ratio
* Gross (Annualized) Expected Return on NAV
* (Annualized) Volatility on NAV
    * Of all, this one is most important to report both ex-ante and ex-post. Ex-ante can be summarized as a long-term median, or mean, or root-mean-square of daily point-in-time ex-ante vol (the latter exactly accounting for vol-of-vol effect assuming pnl is independent across days), but if ex-post comes in wildly different from ex-ante, you must understand why. For example, a manager who internally targets constant point-in-time ex-ante (annualized) vol of 10% might choose to disclose a target of 12% to make allowance for tail events like the quant crisis of 2007.
* (Annualized) Tcost on NAV (AKA "transaction cost" AKA "trading cost") := $'s of market impact + $'s of brokerage commissions and fees + $'s of transaction taxes, over the course of a year, normalized by $'s of NAV
* (Annualized) Turnover on Gross Leverage = $'s traded over the course of a year, normalized by $'s of gross leverage
    * This gives a better sense of how aggressively the strategy trades than turnover on NAV. A strategy that goes in on AAPL at 10x leverage on day 0 then closes out the position all-at-once on day 261 (pretend NAV is $1 and AAPL is flat over this period) trades at (|+$10| + |-$10|) / $1 = 20x annualized turnover on NAV, which seems aggressive -- But it trades at just (|+$10| + |-$10|) / $10 = 2x annualized turnover on gross leverage, which is quite modest. The tcost on NAV will of course be paid on the entire turnover on NAV, but it can be cleaner to attribute this to two separate components: (1) Turnover on GLev (how aggressively the strategy trades), and (2) GLev (how aggressively the strategy takes risk).
* (Annualized) Turnover on NAV = $'s traded over the course of a year, normalized by $'s of NAV
* Net Leverage on NAV = long-term mean $'s long - long-term mean $'s short, normalized by 
