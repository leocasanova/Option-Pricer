#define _USE_MATH_DEFINES
#include "EuropeanOption.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <random>


using namespace std;

EuropeanOption::EuropeanOption(double _r, double _sigma, double _K, double _T, double _S, int _N, double _b, Type _type) :
	Option(_S, _K, _r, _T, _sigma, _type) {
	N = _N;
	b = _b;
}

EuropeanOption::~EuropeanOption() {
}

void EuropeanOption::display() {
	cout << "------------------------------" << endl;
	cout << "Current price (S)   : " << S << endl;
	cout << "Strike (K)          : " << K << endl;
	cout << "Risk-free rate (r)  : " << r << endl;
	cout << "Maturity (T)        : " << T << endl;
	cout << "Volatility (sigma)  : " << sigma << endl;
	cout << "Cost of carry (b)   : " << b << endl;
	if (type == call) {
		cout << "Type                : Call" << endl;
	}
	else {
		cout << "Type                : Put" << endl;
	}
	cout << "------------------------------" << endl;
}

//estimation of the standard normal distribution with Taylor formula
double EuropeanOption::approxN(const double& x) {
	double k = 1.0 / (1.0 + 0.2316419*x);
	double k_sum = k * (0.319381530 + k * (-0.356563782 + k * (1.781477937 +
		k * (-1.821255978 + 1.330274429*k))));
	if (x >= 0.0) {
		return (1.0 - (1.0 / (pow(2 * M_PI, 0.5)))*exp(-0.5*x*x) * k_sum);
	}
	else {
		return 1.0 - approxN(-x);
	}
}

double EuropeanOption::blackScholesFormula(double t) {
	double price = 0;
	double d1 = (log(S / K) + (r + 0.5 * sigma * sigma) * (T - t)) / (sigma * sqrt(T - t));
	double d2 = d1 - sigma * sqrt(T - t);
	if (type == call) {
		price = S * approxN(d1) - K * exp(r * (t - T)) * approxN(d2);
	}
	else {
		price = K * exp(r * (t - T)) * approxN(-d2) - S * approxN(-d1);
	}
	return price;
}

double EuropeanOption::delta(double t) {
	double delt = 0;
	double d1 = (log(S / K) + (r + 0.5 * sigma * sigma) * (T - t)) / (sigma * sqrt(T - t));
	if (type == call) {
		delt = approxN(d1);
	}
	else {
		delt = approxN(d1) - 1;
	}
	return delt;
}

double EuropeanOption::payOff(double S) {
	if (S > 0) {
		if (type == call) {
			return (S > K) ? (S - K) : 0;
		}
		else {
			return (S < K) ? (K - S) : 0;
		}
	}
	else {
		cout << "[ERROR]: Negative parameter in PayOff." << endl;
		return -1;
	}
}

//Implementation of the binomial model

double EuropeanOption::up(int i) {
	return pow(exp(sigma * sqrt(T / N)), i);
}

double EuropeanOption::down(int i) {
	return pow(exp(-sigma * sqrt(T / N)), i);
}

double EuropeanOption::riskNeutralProbability() {
	return (exp(r * T / N) - down(1)) / (up(1) - down(1));
}

//Stock price at node (n, i)
double EuropeanOption::stock(int n, int i) {
	return S * up(i) * down(n - i);
}

double EuropeanOption::price() {
	double * arr = new double[N + 1];
	double q = riskNeutralProbability();
	for (int i = 0; i <= N; i++) {
		arr[i] = payOff(stock(N, i));
	}
	for (int n = N - 1; n >= 0; n--) {
		for (int i = 0; i <= n; i++) {
			arr[i] = (q * (arr[i + 1]) + (1 - q) * (arr[i])) / exp(r * T / N);
		}
	}
	return arr[0];
}

double EuropeanOption::factorielle(int n) {
	return n > 1 ? factorielle(n - 1) * n : 1;
}

double EuropeanOption::closedForm() {
	double result = 0;
	double q = riskNeutralProbability();
	for (int i = 0; i < N; i++) {
		result += factorielle(N) / (factorielle(i) * factorielle(N - i)) * pow(q, i)
			* pow(1 - q, N - i) * payOff(stock(N, i));
	}
	return result / exp(r * T);
}

double EuropeanOption::max(double a, double b) {
	return a < b ? b : a;
}

double EuropeanOption::monteCarlo(int steps) {
	std::default_random_engine generator;
	std::normal_distribution<double> distribution(0.0, 1.0);
	double H = 0;
	double St = 0;
	for (int i = 0; i < steps; i++) {
		St = S * exp((r - 0.5 * sigma * sigma) * T + sigma * sqrt(T) * distribution(generator));
		if (type == call) {
			H += max(St - K, 0.0);
		}
		else {
			H += max(K - St, 0.0);
		}
	}
	return exp(-r * T) * H / double(steps);
}
