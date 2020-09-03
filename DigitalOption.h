#ifndef DIGITALOPTION_H
#define DIGITALOPTION_H
#include "Option.h"


class DigitalOption : public Option
{
public:
	DigitalOption(double _r, double _sigma, double _K, double _T, double _S, double _b, Type _type);
	~DigitalOption();
	double payOff(double S);
};

#endif // DIGITALOPTION_H
