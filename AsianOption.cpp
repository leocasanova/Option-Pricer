#include "AsianOption.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <random>
#include <chrono>


using namespace std;

AsianOption::AsianOption(double _r, double _sigma, double _K, double _T, double _S, Type _type) :
	Option(_S, _K, _r, _T, _sigma, _type) {
}

AsianOption::~AsianOption() {
}

double AsianOption::max(double a, double b) {
	return a < b ? b : a;
}

double AsianOption::payOff(double steps) {
	std::default_random_engine generator;
	std::normal_distribution<double> distribution(0.0, 1.0);
	double h = 0;
	double St = 0;
	for (int i = 0; i < steps; i++) {
		St = S * exp((r - 0.5 * sigma * sigma) * T + sigma * sqrt(T) * distribution(generator));
		h += max(St - K, 0.0);
	}
	return h;
}

double AsianOption::monteCarlo(int steps) {
	return exp(-r * T) * payOff(steps) / double(steps);
}
