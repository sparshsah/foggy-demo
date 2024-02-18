# Realized Sharpe Ratios of Some Major Funds

As always, these suffer from survivorship bias --
I wouldn't be writing about them if they hadn't performed well.
It's not possible to know with certainty how much of that good performance
was attributable to true goodness, and how much to dumb luck.
Even with that luck sprinkled on, notice that none is 2+!
It is very hard to kill it at capacity.

Also, definitely don't interpret this as a ranking of go-forward goodness.
Although most of these histories are long enough to reject the hypothesis that
an individual's ER is zero (to get the t-stat, just multiply the annualized Sharpe by
the square root of the length of the review period in years --
and don't tell your Stats prof that you're ignoring the multiple-hypotheses correction),
none of them is long enough to confidently conclude that any one has a
higher or lower Sharpe than any other one.
And on top of that, the choice of time period, which just came down to whatever sources I could find,
makes a huge difference. Two Sigma's ARP fund was incepted in 2015, and my review ended in 2021.
The 2018-2020 period (the so-called "Quant Winter") was infamously tough for ARP,
and so its tepid Sharpe of 0.14 is in some sense unfair.
They just happened to launch at an unlucky time, but I have extreme conviction
(in a non-financial-advice way)
that the strategy over the long term will achieve a Sharpe closer to 0.40,
and based on this conviction I remain invested in a similar fund elsewhere.

To that point, the ostensible winner based on the numbers below, DE Shaw's Composite fund,
shit the bed so hard during the GFC that they had to lay off 10\% of their staff in one day.
People wondered aloud whether the firm was long for this Earth, and then Composite went on to post
a decade of great performance, and everyone immediately forgot about the first thing,
and now they're all clamoring to pay 4-and-40 to get into a fund that in 2009
they were battering down the gates to get out of ([ref](https://www.institutionalinvestor.com/article/2btgdofw34j872f1b8fls/premium/d-e-shaw-opens-gates-expects-3-3-billion-to-flee-magazine-version)).

Finally, one last note: Sharpe by construction is a standalone risk-adjusted return measure,
and tells me nothing about (a) absolute risk loadings or (b) risk contributions in a portfolio context.
Say you offer me a zero-Sharpe fund for a flat 2% management fee.
Doesn't seem that attractive... Until you follow up that it's Universa's tail-risk fund,
and the slow bleed 9-years-out-of-10 will be rewarded by a meltup whenever the stock market melts down.
This could actually be _very_ attractive: It lets me more comfortably load up on cheap equity beta,
harvesting the long-term ER thereof,
by promising to try to protect me in the odd unlucky year where there's a panic.
Now, whether you believe that Universa can continue to make good on that promise, is up to you.
I'm just saying that if you do believe it, then as Aaron Brown [explains](https://www.bloomberg.com/view/articles/2020-05-26/twitter-spat-over-market-risks-is-a-teaching-moment):
> Your hedge does not have to actually make money by itself: The key is [geometric] asymmetry, in that a 50% loss (in a crash) followed by a 100% gain (in a recovery) produces a final return of zero. If your hedge can reduce both by 25%, so you have a 25% loss followed by a 75% gain, you end up instead with a final return of more than 30%.

These are all net-of-fees, net-of-tcost, excess-of-cash, unless otherwise noted.
Sources for each of these figures are stored in `./files`.

## Renaissance Medallion

* Strategy: God only knows.
* 1978 (inception) - present: forty-two gazillion.
* Caveat: They keep this for themselves and give crap to clients. Ref 2020 performance divergence between their stuff and clients' stuff.

## DE Shaw Composite Fund

* Quant + Disco Multi-Asset
* 2001 Mar (fund inception) - 2011 Jun (review date): 1.33 (from an investment consultancy report prepared by Cliffwater)
* This is so good that in 2018 DE Shaw started charging 3-and-40 for it!

## Two Sigma Absolute Return Enhanced Strategy

* Quant Multi-Asset, probably the best brand name in all of quant asset management (real stuff, not RenTec -- cf above).
* 2011 Nov (fund inception) - 2022 Dec (review date): 1.1 (from an investment consultancy report prepared by RVK for the ND Board of Lands)

## Two Sigma Alternative Risk Premia

* Quant Multi-Asset
* 2015 (fund inception) - 2021 (review date): 0.14 (from a pitch deck provided by Two Sigma to Meketa for the Oakland PFRS)
* Note: Their timing here was terrible, they launched into an infamously tough period for ARP (the so-called "Quant Winter").

## AQR Absolute Return Fund

* Quant + Disco Multi-Asset
* 1998 (fund inception) - 2023 (review date): 0.9 (calculated by me)

## Bridgewater Pure Alpha 18% vol

* The most storied global-macro fund on record.
* 1991 (fund inception) - 2015 (review date): 0.67 (from an article in P&I)

## Two Sigma Compass sleeve

* Quant Macro
* 2005 (strategy inception) - 2023 (review date): 0.7 (reported to me)

## Warren Buffett

* Stock Selection + Private Equity -- A legend!
* 1976 (30Y lookback) - 2017 (review date): 0.76 (GROSS of fees, from a paper by AQR)
