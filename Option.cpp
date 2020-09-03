#include "Option.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>


using namespace std;

Option::Option(double _S, double _K, double _r, double _T, double _sigma, Type _type) {
	S = _S;
	K = _K;
	r = _r;
	T = _T;
	sigma = _sigma;
	type = _type;
}

Option::~Option() {
}
