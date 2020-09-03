#define _USE_MATH_DEFINES
#include "AmericanOption.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <random>


using namespace std;

AmericanOption::AmericanOption(double _r, double _sigma, double _K, double _T, double _S, int _N, Type _type) :
	Option(_S, _K, _r, _T, _sigma, _type) {
	N = _N;
}

AmericanOption::~AmericanOption() {
}

//Estimation of the standard normal distribution with Taylor formula
double AmericanOption::approxN(const double& x) {
	double k = 1.0 / (1.0 + 0.2316419*x);
	double k_sum = k * (0.319381530 + k * (-0.356563782 + k * (1.781477937 + k * (-1.821255978 + 1.330274429*k))));
	if (x >= 0.0) {
		return (1.0 - (1.0 / (pow(2 * M_PI, 0.5)))*exp(-0.5*x*x) * k_sum);
	}
	else {
		return 1.0 - approxN(-x);
	}
}

double AmericanOption::blackScholesFormula(double t) {
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

double AmericanOption::payOff(double S) {
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

double AmericanOption::up(int i) {
	return pow(exp((r + 0.5 * sigma * sigma) * T / N + sigma * sqrt(T / N)), i);
}

double AmericanOption::down(int i) {
	return pow(exp((r + 0.5 * sigma * sigma) * T / N - sigma * sqrt(T / N)), i);
}

double AmericanOption::riskNeutralProbability() {
	return (exp(r * T / N) - down(1)) / (up(1) - down(1));
}

double AmericanOption::stock(int n, int i) {
	return S * up(i) * down(n - i);
}

double AmericanOption::max(double a, double b) {
	return a < b ? b : a;
}

void AmericanOption::setPrices() {
	binLattice.setN(N);
	double q = riskNeutralProbability();
	vector<double> vec = binLattice.getVector(N);
	for (int i = 0; i < N + 1; i++) {
		vec[i] = payOff(stock(N, i));
	}
	binLattice.setVector(N, vec);
	vector<double> vecTemp;
	for (int n = N - 1; n >= 0; n--) {
		vec = binLattice.getVector(n);
		vecTemp = binLattice.getVector(n + 1);
		for (int i = 0; i <= n; i++) {
			vec[i] = max((q * (vecTemp[i + 1]) + (1 - q) * (vecTemp[i])) / exp(r * T / N), payOff(stock(n, i)));
		}
		binLattice.setVector(n, vec);
	}
}

bool AmericanOption::isExercisable(int n, int i) {
	setPrices();
	double val = binLattice.getNode(n, i);
	if (val <= 0) return false;
	return val == payOff(stock(n, i)) ? true : false;
}

double AmericanOption::price() {
	setPrices();
	return binLattice.getNode(0, 0);
}