#include "DigitalOption.h"


DigitalOption::DigitalOption(double _r, double _sigma, double _K, double _T, double _S, double _b, Type _type) :
	Option(_S, _K, _r, _T, _sigma, _type) {
}

DigitalOption::~DigitalOption() {
}

double DigitalOption::payOff(double S) {
	if (type == call) {
		return K < S ? 1 : 0;
	}
	else {
		return K > S ? 1 : 0;
	}
}
