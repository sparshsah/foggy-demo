Some miscellaneous stream-of-consciousness musings on ML (machine learning).

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
* Machine-learned function mapping input features to output outcomes
    - E.g. A mapping from macro and idiosyncratic signals to an asset-level vector of ERs (expected returns) and matrix of covariances, based on which the machine each day spits out new ER and risk/volatility forecasts

## Optimization/Action

Finally, you optimize actions---with e.g. traditional constrained optimization or RL (reinforcement learning)---deciding what to do to achieve the best outcome.

* In investing, this could be Markowitz (AKA mean-variance) optimization with risk-management constraints and tcosts.
* In lending, this could be framed as a multi-armed bandit problem wherein you explore new market geos and segments subject to regulations.

# Simple Buzzwords

## Point: Bias-Variance Tradeoff

Regularization or early stopping can help
* With permitting a complex (low-bias, high-variance) model architecture
* Without leading to overfitting.

## Counterpoint: Double-Descent Curve

We can have "salutary overparameterization" or "benign overfitting" / "benign interpolation".
* Even in plain-vanilla linear regression (just using the pseudoinverse to make the solution defined, which corresponds to choosing the minimum-norm interpolating solution)!
* But especially in deep learning.

## Ensemble Methods

* Bagging (bootstrap-aggregating)
* Boosting (e.g. AdaBoost or Gradient Boosting)
* Stacking

## The Evolution of NLP toward LLMs (as of 2026Q1)

NLP is "natural-language processing". LLMs are "large language models".

Model Architectures:
* RNN (recurrent NN (neural network)) ->
* Gated RNN (e.g. GRU (gated recurrent unit) or LSTM (long short-term memory)) ->
* Attention-enabled NN (e.g. transformer)

Training Algorithms and Adaptation Techniques:
* Pretraining ->
    - Optimizing hyperparameters and settling pretrained weights based on the "self-supervised" next-token-prediction task on large, generic datasets e.g. Wikipedia or Reddit or StackOverflow
* Foundation models ->
    - Massive-scale pretrained models intended to be broadly useful
* Continued / domain-adaptive pretraining ->
    - Still based on the self-supervised next-token-prediction task on large, unlabeled datasets e.g. a medical journal's archives
    - Note that everyone I've seen introduce this technique brings up the risk of "catastrophic forgetting" in the next breath like it's a knee-jerk reaction, so I'll do the same...
* Fine-tuning ->
    - E.g. Freezing the hyperparameters and "backbone" (earlier layers) and just doing low-learning-rate backpropagation on the "head" (later, closer-to-output layers), but now doing supervised learning on smaller domain-specific labeled datasets
* RAG (retrieval-augmented generation) ->
    - Providing domain-specific authoritative text as context to a trained LLM, at prompt time, _by injecting that text into the prompt_
    - E.g. A Claude Code `SKILL.md` which is automatically retrieved when relevant
* Context compaction/compression ->
    - E.g. When a chat becomes so long that it quadratically slows down the bot's responses, or literally becomes too big to fit into the bot's context window, you can keep just a summary of the conversation so far as context for the conversation going forward

## RL

I am semi-making up / abusing a term, calling RL as "bootstrap-supervised" or "asymptotically-supervised".
* To me, RL has a "supervised" flavor
    - If you stretch, you can think of RL's purpose as spitting out a "classification label" (the optimal action chosen from the set defined and provided by the scientist) given some "features" (a state or information about a state)
    - In principle, there is a true "correct" answer here given the scientist's utility function and the current state
* But also an "unsupervised" flavor
    - The scientist doesn't explicitly specify a mapping to action from state in the training data.
* We call LLM's next-token prediction task as "self-supervised" because the correct answer---the actual next token---is explicitly found in the dataset even though it doesn't necessarily fit into the traditional schema of tabular rows with a "y" and an "X".
    - Nevertheless, if you had an infinite-sized table, you could build these rows where "y" is the actual next token and "X" is the sequence that preceded it.
* So I call RL's "choose the best action" task as "bootstrap-supervised" or "asymptotically-supervised" because the latent correct answer---the actual optimal action given the scientist's economic utility function---can be unambiguously calculated by simulating every possible path for an infinite number of steps.
    - In Q-Learning, if we had infinite memory and infinite compute and a well-behaved process, our bootstrap-updating of the value function would converge to the true function.
    - And that bootstrap-updated value function in a very meaningful way identifies---"labels"---the actual best action from a given state.

RL classically often boiled down to
* Applying Q-Learning (off-policy) or SARSA (on-policy) to optimize or evaluate an action policy
* By letting an agent explore in a bootstrap-supervised manner the state space of an MDP (Markov Decision Process)
* Wherein the value function can be written as a Bellman equation.

TODO(sparshsah): There's been a lot of progress here, e.g. policy-gradient, actor-critic...

## Industrial Automation

You could perform RL on digital twins to impose MPC (model-predictive control) on PID (proportional-integral-derivative) controllers.

For example, pretend you're trying to run a nuclear power plant. The tradeoff boils down to balancing safety, product yield/quality, and cost.

* You have a safe operating temperature range: Going outside that range risks equipment longevity or people.
* Within that range, there's an optimal temperature at which product yield or quality is highest.
* But maintaining that optimal point costs energy and water.

So you balance it: While always respecting the hard safety constraints, you aim for the temperature that maximizes profit, considering increased yield/quality minus the extra cost.

* To learn the safe temperature range you could use a first-principles physics-based model (with the solution either in closed form or numerically);
* To learn the optimal temperature within that range (based on yield/quality minus costs at each temperature) you could use RL.

The ultimate expression of this paradigm is the closed-loop system, wherein the agent acts online based on live sensor data with live (human-overridable) control of the plant.

## Bayesian HPT vs MBRL (work in progress)

HPT is "hyperparameter tuning". MBRL is "model-based reinforcement learning".

There are Bayesian-inspired HPT methods like TPE (tree-structured Parzen estimator) or GP-EI (Gaussian process with expected improvement) or HEBOSearch (heteroscedastic evolutionary Bayesian optimization).
* These methods try to (oversimplifying here) build a surrogate representation of the behavior of a blackbox function given hyperparameters, and iteratively improve hyperparameters by aiming for something like `argmax_{hyperparameters}(goodness_of_blackbox | hyperparameters)`.

Separately, there is MBRL
* Which also builds surrogate representations and can apply Bayesian-style optimization to converge toward an optimal action policy.

I have to formalize this a bit more (chatbots push back on me here, which is why above I said "Bayesian-inspired" or "Bayesian-style" instead of "Bayesian"), but I feel there's a distinct kernel of Bayesian strategy that unifies both.

# Infusing the Machine with Human Intuition

I see two big ways to infuse machines with human intuition:

* Imitation learning
* Explainability

## Imitation Learning

First is to assert that humans make ex-ante "correct" or "optimal" decisions, and just learn to imitate/replicate/mimic that.

* For example, in investing, you might assert that human-decided positions are "right", and if they end up losing money ex-post in the real world, then that's just an unlucky noisy draw.
    - This takes all the noise out of the target (remember, we asserted this).
    - So, rather than training on noisy returns data, you train on noiseless positions data.
    - That is, rather than trying to predict returns directly, you try to predict what portfolio a human would build, and assert that that portfolio reflects the ex-ante best expectation of asset returns.
* Or, rather than building a "digital twin" and simulating what would happen under different scenarios then using RL to learn a value function and action policy, you just try to systematize---infer and write down---the expert human operator's observed action policy.

## Explainability

Second is things like SHAP explanations, which help you as the human try to understand "what the blackbox is doing".

## Caveat

Ten years ago, I would have reckoned that humans are better than machines at reasoning their way out of rare, severe situations. Especially if you can get a human who is well-rested (not tired), calm (not emotionally agitated), and trusted to act in good faith (not disgruntled/saboteur). After all, machines are just doing "pattern recognition", and if they encounter a situation that wasn't in their training sample, they'll go haywire or, worse, "hallucinate" (a term-of-art that hadn't really entered the popular consciousness ten years ago!). But as time has gone on, I'm not so sure... I've found that OpenAI's ChatGPT or Anthropic's Claude is faster and better at debugging and recovering from system incidents than human engineers. After all, the human brain is just a highly-advanced computer, equally prone to panicking or overconfidence as the machine is prone to going haywire or hallucinating. That's to say nothing of bonafide mistakes, which it goes without saying that both can make, too.
