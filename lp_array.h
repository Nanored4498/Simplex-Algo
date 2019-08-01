#ifndef DEF_LP_ARRAY
#define DEF_LP_ARRAY

#include "fraction.h"
#include "linear_prog.h"
#include <set>

class LPArray {
public:
	// Create an array from a linear prog
	LPArray(LinearProg const& prog);

	~LPArray();

	// Integers to represent rules and a function to get their names
	static const int MAX = 0, BLAND = 1, OWN = 2;
	static std::string getRuleName(int rule);

	// Do a pivot with `entering_var` entering and the variable satisfying `constraint` leaving
	void do_pivot(int entering_var, int constraint);

	// Choose which variable will enter the basis with the rule `rule`
	int choose_entering(int rule) const;

	// return the constraint with the lower ratio for the variable `entering`
	int choose_constraint(int entering) const;

	// Execute one phase with the rule `rule` and return true iff the simplex is unbounded. Print arrays if `show` is true
	bool one_phase(int rule, bool show);

	// Change the size of the array and the objective function to go to the step 2
	void step_one_to_two();

	// Print the array
	void print() const;

	// Return the optimal value
	Fraction get_result() const { return -mat[0][m-1]; };

	// Return an optimal solution
	Fraction* get_solution() const;

	// Return the number of pivots done
	int get_num_pivots() const { return num_pivot; };

	// Returns set of basic and non-basic variables
	std::set<int> const& get_basic() const { return basic_vars; };
	std::set<int> const& get_nonbasic() const { return non_basic_vars; };

private:
	int n, m, m2; // Dimensions of the array
	Fraction **mat, *objective; // Matrix of the array and the objective function for phase 2
	int *map_const_var; // A map from constraints to variables that satisify these constraints
	std::set<int> basic_vars, non_basic_vars; // Sets of basic and non-basic variables
	int num_pivot; // The number of pivots done
	int *num_entering; // An array that gives for a variable, the number of times the variable entered in the basis
};

#endif