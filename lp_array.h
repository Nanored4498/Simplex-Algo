#ifndef DEF_LP_ARRAY
#define DEF_LP_ARRAY

#include "fraction.h"
#include "linear_prog.h"
#include <set>

class LPArray {
public:
	LPArray(LinearProg const& prog);

	~LPArray();

	static const int MAX = 0, BLAND = 1, OWN = 2;
	static std::string getRuleName(int rule);

	void do_pivot(int entering_var, int constraint);
	int choose_entering(int rule) const;
	int choose_constraint(int entering) const;
	//Execute one phase and return true iff the simplex is unbounded
	bool one_phase(int rule, bool show);
	void step_one_to_two();

	void print() const;

	Fraction get_result() const { return -mat[0][m-1]; };
	Fraction* get_solution() const;
	int get_num_pivots() const { return num_pivot; };
	std::set<int> const& get_basic() const { return basic_vars; };
	std::set<int> const& get_nonbasic() const { return non_basic_vars; };

private:
	int n, m, m2;
	Fraction **mat, *objective;
	int *map_const_var;
	std::set<int> basic_vars, non_basic_vars;
	int num_pivot;
	int *num_entering;
};

#endif