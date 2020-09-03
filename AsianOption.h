#ifndef ASIANOPTION_H
#define ASIANOPTION_H
#include "Option.h"

class AsianOption : public Option
{
public:
	AsianOption(double _r, double _sigma, double _K, double _T, double _S, Type _type);
	~AsianOption();
	double max(double a, double b);
	double payOff(double steps);
	double monteCarlo(int steps);
};

#endif // ASIANOPTION_H
