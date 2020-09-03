#include "BinLattice.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>


using namespace std;

BinLattice::BinLattice() {
	N = 0;
}

BinLattice::~BinLattice() {
}

void BinLattice::setN(int _N) {
	N = _N;
	lattice.resize(N + 1);
	for (int i = 0; i < N + 1; i++) {
		lattice[i].resize(i + 1);
	}
}

void BinLattice::setNode(int n, int i, double val) {
	if (i < 0 || i > 2 * N || n > N) {
		cout << "[ERROR]: Error in setNode() parameters." << endl;
	}
	else {
		vector<double> vec = lattice[n];
		vec[i] = val;
		lattice[n] = vec;
	}
}

double BinLattice::getNode(int n, int i) {
	vector<double> vec = lattice[n];
	return vec[i];
}

vector<double> BinLattice::getVector(int n) {
	return lattice[n];
}

void BinLattice::setVector(int n, vector<double> vec) {
	lattice[n] = vec;
}

void BinLattice::display() {
	vector<double> vec;
	for (int i = 0; i < N + 1; i++) {
		vec = lattice[i];
		for (int j = 0; j < i + 1; j++) {
			cout << "Node(" << i << ", " << j << ")" << endl;
			cout << vec[j] << endl;
		}
	}
}
