# The Process

I think of ML (machine learning) as being broken down into three stages:

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
