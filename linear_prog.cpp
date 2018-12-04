#include "linear_prog.h"
#include <fstream>
#include <iostream>
#include <math.h>
#include "lp_array.h"


void LinearProg::load(std::istream &stream) {
	stream >> nV >> nC;
	objective = new Fraction[nV];
	for(int i = 0; i < nV; i++)
		stream >> objective[i];
	rh_constraints = new Fraction[nC];
	for(int i = 0; i < nC; i++)
		stream >> rh_constraints[i];
	lh_constraints = new Fraction*[nC];
	for(int i = 0; i < nC; i++) {
		lh_constraints[i] = new Fraction[nV];
		for(int j = 0; j < nV; j++)
			stream >> lh_constraints[i][j];
	}
}

LinearProg::LinearProg(std::istream &stream) {
	load(stream);
}

LinearProg::LinearProg(std::string const& filename) {
	std::ifstream stream;
	stream.open(filename);
	load(stream);
	stream.close();
}

LinearProg::~LinearProg() {
	if(objective) delete[] objective;
	if(rh_constraints) delete[] rh_constraints;
	if(lh_constraints) {
		for(int i = 0; i < nC; i++)
			if(lh_constraints[i]) delete[] lh_constraints[i];
		delete[] lh_constraints;
	}
}

int frac_len(Fraction *fs, int j) {
	Fraction f = fs[j];
	return (j == 0 || f >= 0) ? f.str_len() : f.str_len() - 1;
}

void print_frac(Fraction *fs, int *sizes, int j) {
	Fraction f = fs[j];
	int s = sizes[j];
	if(f == 0) {
		for(int i = 0; i < s + 3 + log10(j+1); i++) std::cout << ' ';
		if(j > 0) std::cout << ' ';
	} else {
		int n_spaces = s - f.str_len();
		if(j > 0) {
			std::cout << ' ';
			if(f >= 0) std::cout << '+';
			else n_spaces += 1;
		}
		std::cout << f << "x_" << j+1;
		for(int i = 0; i < n_spaces; i++) std::cout << " ";
	}
}

void LinearProg::print() const {
	std::cout << "Maximize  ";
	int *max_size = new int[nV];
	for(int j = 0; j < nV; j++) {
		max_size[j] = frac_len(objective, j);
		for(int i = 0; i < nC; i++)
			max_size[j] = std::max(max_size[j], frac_len(lh_constraints[i], j));
		print_frac(objective, max_size, j);
	}
	std::cout << "\nSuch that ";
	for(int i = 0; i < nC; i++) {
		if(i > 0) std::cout << "          ";
		for(int j = 0; j < nV; j++) print_frac(lh_constraints[i], max_size, j);
		std::cout << " <= " << rh_constraints[i] << '\n';
	}
	std::cout << "          ";
	for(int j = 0; j < nV; j++) {
		if(j > 0) std::cout << ", ";
		std::cout << "x_" << j+1;
	}
	std::cout << " are non-negative\n";
	delete[] max_size;
}

void LinearProg::simplex_solve(int rule, bool show) const {
	LPArray a(*this);
	std::cout << "OUTPUT\nThe input linear program is:\n\n";
	print();
	if(show) std::cout << "\nPhase 1:\n";
	a.one_phase(rule, show);
	if(show) std::cout << "\n";
	if(a.get_result() != 0) {
		std::cout << "This linear program is INFEASIBLE.\n";
		return;
	}
	if(show) std::cout << "Phase 2:\n";
	a.step_one_to_two();
	bool unbouded = a.one_phase(rule, show);
	if(show) std::cout << "\n";
	if(unbouded) {
		std::cout << "This linear program is FEASIBLE but the solution value is UNBOUNDED.\n";
		return;
	}
	Fraction *solution = a.get_solution();
	std::cout << "One optimal solution is:  ";
	for(int i = 0; i < nV; i++) {
		if(i > 0) std::cout << ", ";
		std::cout << "x_" << i+1 << " = " << solution[i];
	}
	delete[] solution;
	std::cout << "\nThe objective value of this solution is:  " << a.get_result();
	std::cout << "\nThe number of pivots is:  " << a.get_num_pivots();
	std::cout << "\nThe pivot rule used:  " << LPArray::getRuleName(rule) << "\n";
}