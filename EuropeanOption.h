#ifndef EUROPEANOPTION_H
#define EUROPEANOPTION_H
#include "Option.h"


class EuropeanOption : public Option
{
private:
	int N;    //iterations
	double b; //cost of carry
public:
	EuropeanOption(double _r, double _sigma, double _K, double _T, double _S, int _N, double _b, Type _type);
	~EuropeanOption();
	void display();
	double approxN(const double& x);
	double blackScholesFormula(double t);
	double delta(double t);
	double payOff(double S);
	double up(int i);
	double down(int i);
	double riskNeutralProbability();
	double stock(int n, int i);
	double price();
	double factorielle(int n);
	double closedForm();
	double max(double a, double b);
	double monteCarlo(int steps);
};

#endif // EUROPEANOPTION_H
