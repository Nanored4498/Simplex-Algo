#ifndef DEF_LINEAR_PROG
#define DEF_LINEAR_PROG

#include "fraction.h"
#include <iostream>

class LinearProg {
public:
	// Load a linear programm using a stream
	LinearProg(std::istream &stream);
	// Load a linear programm from a file
	LinearProg(std::string const& filename);

	~LinearProg();

	// Print this linear programm
	void print() const;
	void simplex_solve(int rule, bool show) const;

private:
	Fraction *objective, *rh_constraints, **lh_constraints;
	int nV, nC;

	void load(std::istream &stream);
	
	friend class LPArray;
};

#endif