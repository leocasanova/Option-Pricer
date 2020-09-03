#ifndef AMERICANOPTION_H
#define AMERICANOPTION_H
#include "Option.h"
#include "BinLattice.h"

class AmericanOption : public Option
{
private:
	int N;
	BinLattice binLattice;
public:
	AmericanOption(double _r, double _sigma, double _K, double _T, double _S, int _N, Type _type);
	~AmericanOption();
	double approxN(const double& x);
	double blackScholesFormula(double t);
	double payOff(double S);
	double up(int i);
	double down(int i);
	double riskNeutralProbability();
	double stock(int n, int i);
	double max(double a, double b);
	void setPrices();
	bool isExercisable(int n, int i);
	double price();
};

#endif // AMERICANOPTION_H
