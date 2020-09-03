#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <random>
#include "EuropeanOption.h"
#include "BinLattice.h"
#include "AsianOption.h"
#include "AmericanOption.h"
#include <chrono>


using namespace std;

int main(int argc, char **argv)
{
	double S = 100;         //underlying price
	double K = 100;         //strike price
	double r = 0.03;        //interest rate
	double T = 1;           //maturity (years)
	double sigma = 0.25;	//volatility
	int N = 100;			//iterations
	double b = 0;			//cost of carry

	cout << "------------------------------" << endl;
	cout << "Current price (S)   : " << S << endl;
	cout << "Strike (K)          : " << K << endl;
	cout << "Risk-free rate (r)  : " << r << endl;
	cout << "Maturity (T)        : " << T << endl;
	cout << "Volatility (sigma)  : " << sigma << endl;
	cout << "Iterations (N)      : " << N << endl;
	cout << "Cost of carry (b)   : " << b << endl;
	cout << "------------------------------" << endl;

	EuropeanOption euCall(r, sigma, K, T, S, N, b, call);
	EuropeanOption euPut(r, sigma, K, T, S, N, b, put);

	cout << "European Option - Black & Scholes formula : " << endl;
	cout << "Call : " << euCall.blackScholesFormula(0.5) << endl;
	cout << "Put  : " << euPut.blackScholesFormula(0.5) << endl;
	cout << "-------------------" << endl;
	cout << "European Option - Delta : " << endl;
	cout << "Call : " << euCall.delta(0.5) << endl;
	cout << "Put  : " << euPut.delta(0.5) << endl;
	cout << "-------------------" << endl;
	cout << "European Option - Price : " << endl;
	cout << "Call : " << euCall.price() << endl;
	cout << "Put  : " << euPut.price() << endl;
	cout << "-------------------" << endl;
	cout << "European Option - Closed-Form formula : " << endl;
	cout << "Call : " << euCall.closedForm() << endl;
	cout << "Put  : " << euPut.closedForm() << endl;

	/*
	BinLattice binLat;
	binLat.setN(3);
	binLat.setNode(1, 1, 4);
	cout << binLat.getNode(1, 1) << endl;
	binLat.display();
	*/

	cout << "-------------------" << endl;
	cout << "European Option - Monte Carlo :" << endl;
	cout << "Call : " << euCall.monteCarlo(10000) << endl;
	cout << "Put  : " << euPut.monteCarlo(10000) << endl;
	cout << "-------------------" << endl;
	cout << "Asian Option Monte Carlo :" << endl;

	AsianOption asianOp(r, sigma, K, T, S, call);
	cout << "Call : " << asianOp.monteCarlo(1000000) << endl;
	cout << "-------------------" << endl;

	AmericanOption americanOp(r, sigma, K, T, S, N, call);
	cout << "American Option Black & Scholes :" << endl;
	cout << "Call : " << americanOp.blackScholesFormula(0.5) << endl;
	cout << "-------------------" << endl;
	cout << "American Option binomial :" << endl;
	cout << "Call : " << americanOp.price() << endl;

	std::cin.get();

	return 0;
}
