Some miscellaneous musings on ML (machine learning).

# The Process

I think of ML as being broken down into three stages:

1. Data
2. Model
3. Optimization/Action

## Data

To start, you synthesize (from a theoretical ground-truth DGP (data-generating process)) or collect (from the real world) and organize data.

This might be:

* Simulating data based on randomly-sampled causal graphs (as in TabPFN)
* Conducting a double-blind RCT (randomized controlled trial) (as in many clinical medical trials)
* Downloading historical futures-returns data (as in investing)

## Model

Then, you define or construct or learn a model of the world.

This could be a:

* Known theoretical structure or representation
    - E.g. A states-and-flows model of the economy
* Digital twin
    - E.g. A simulated nuclear power plant based on continuous measurements of a real plant
* Machine-learned function mapping input features to ouput outcomes
    - E.g. A mapping from macro and idiosyncratic signals to an asset-level vector of ERs (expected returns) and matrix of covariances, based on which the machine each day spits out new ER and risk/volatility forecasts

## Optimization/Action

Finally, you optimize actions---with e.g. traditional constrained optimization or RL (reinforcement learning)---deciding what to do to achieve the best outcome.

* In investing, this could be Markowitz (AKA mean-variance) optimization with risk-management constraints and tcosts.
* In lending, this could be framed as a RL problem wherein you explore new market geos and segments subject to regulations.

# Infusing the Machine with Human Intuition

I see two big ways to infuse machines with human intuition:

* Imitation learning
* Explainability

## Imitation Learning

First is to assert that humans make ex-ante "correct" or "optimal" decisions, and just learn to imitate/replicate/mimic that.

* For example, in investing, you might assert that human-decided positions are "right", and if they end up losing money ex-post in the real world, then that's just an unlucky noisy draw. This takes all the noise out of the target (remember, we asserted this). So, rather than training on noisy returns data, you train on noiseless positions data. That is, rather than trying to predict returns directly, you try to predict what portfolio a human would build, and assert that that portfolio reflects the ex-ante best expectation of asset returns.
* Or, rather than building a "digital twin" and simulating what would happen under different scenarios then using RL to learn a value function and action policy, you just try to systematize---infer and write down---the expert human operator's observed action policy.

## Explainability

Second is things like SHAP explanations, which help you as the human try to understand "what the blackbox is doing".

## Caveat

Five years ago, I would have reckoned that humans are better than machines at reasoning their way out of rare, severe situations. Especially if you can get a human who is well-rested (not tired), calm (not emotionally agitated), and trusted to act in good faith (not disgruntled/saboteur). After all, machines are just doing "pattern recognition", and if they encounter a situation that wasn't in their training sample, they'll go haywire or, worse, "hallucinate" (a term-of-art that we didn't have five years ago!). But as time has gone on, I'm not so sure... I've found that OpenAI's ChatGPT or Anthropic's Claude is faster and better at debugging and recovering from system incidents than human engineers. After all, the human brain is just a highly-advanced computer, equally prone to panicking or overconfidence as the machine is prone to going haywire or hallucinating. That's to say nothing of bonafide mistakes, which it goes without saying that both can make, too.
