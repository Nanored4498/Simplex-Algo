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

	// Solve the simplex with the rule `rule` and print arrays at each pivot if `show` is true
	void simplex_solve(int rule, bool show) const;

private:
	// Arrays of fractions to represent the linear prog
	Fraction *objective, *rh_constraints, **lh_constraints;

	// Number of variables and number of constraints
	int nV, nC;

	// Load linear prog from a stream
	void load(std::istream &stream);
	
	friend class LPArray;
};

#endif