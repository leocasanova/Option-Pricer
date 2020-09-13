# Option-Pricer

Pricing options (European, American, Asian and Digital) with different models such as the Black & Scholes formula, Closed-form formula, Cox-Ross-Rubinstein procedure and Monte Carlo method.

# Definitions
K: strike price
S: underlying price
r: risk-free interest rate
T: expiry date (maturity)
t: time
N: number of iterations
sigma: volatility

# Binomial Model

In this model, the stock prices evolve randomly by moving up by a factor 1 + U or down by 1 + D independently at each time step starting from the spot price S(0).
As a result the stock price becomes:
S(n, i) = S(0) * (1 + U)^i * (1 + D)^(n - i) where S(0) > 0, U > D > - 1 and n >= i >= 0.

There is also a risk-free security growing by a factor 1 + R > 0 during each time step
Within the binomial model, the price H(n, i) at each node (n, i) of a European option with the expiry date N and payoff h(S(N)) can be computed by using the Cox-Ross-Rubinstein (CRR) procedure which proceeds by backward induction :

## At the expiry date N

	H(N, i) = h(S(N, i)) for each node i = 0, 1, ..., N

## If H(n + 1, i) is already known at each node i = 0, 1, ..., n + 1 for some n = 0, ..., N - 1 then
	
	H(n, i) = (q * H(n + 1, i + 1) + (1 - q) * H(n + 1, i)) / (1 + R) for each i = 0, ..., n

Here q = (R - D) / (U - D) is the risk-neutral probability

## Payoff function h(z)

	For all z > 0,

	if (option.type == call) {
		return (z > K) ? (z - K) : 0;
	} else {
		return (z < K) ? (K - z) : 0;
	}

# Closed-form formula

The CRR method provides also a closed-form formula for option pricing, instead of the previous iterative procedure.

