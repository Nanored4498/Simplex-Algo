#include "lp_array.h"

LPArray::LPArray(LinearProg const& prog) {
	num_pivot = 0;
	n = prog.nC + 1;
	m = prog.nV + prog.nC + 1;
	mat = new Fraction*[n];
	objective = new Fraction[m];
	map_const_var = new int[n];
	m2 = m;
	for(int i = 0; i < n; i++)
		if(prog.rh_constraints[i] < 0) m2 += 1;
	for(int i = 0; i < n; i++)
		mat[i] = new Fraction[m2];
	num_entering = new int[m2-1];
	for(int j = 0; j < m2-1; j++)
		num_entering[j] = 0;

	// Initialization of the first line for phase 1
	for(int j = 0; j < m2; j++)
		mat[0][j] = 0;
	// And we store the objective for phase 2
	for(int j = 0; j < prog.nV; j++)
		objective[j] = prog.objective[j];
	for(int j = prog.nV; j < m; j++)
		objective[j] = 0;

	// Initialization of constraints
	int new_var = m-1;
	for(int i = 0; i < prog.nC; i++) {
		Fraction rhc = prog.rh_constraints[i];
		bool positive = rhc >= 0;
		for(int j = 0; j < prog.nV; j++)
			mat[i+1][j] = positive ? prog.lh_constraints[i][j] : -prog.lh_constraints[i][j];
		for(int j = prog.nV; j < m2; j++)
			mat[i+1][j] = 0;
		mat[i+1][prog.nV+i] = positive ? 1 : -1;
		mat[i+1][m2-1] = positive ? rhc : -rhc;
		if(!positive) {
			basic_vars.insert(new_var);
			map_const_var[i+1] = new_var;
			non_basic_vars.insert(prog.nV + i);
			mat[i+1][new_var++] = 1;
			mat[0][prog.nV+i] = -1;
			for(int j = 0; j < prog.nV; j++)
				mat[0][j] += mat[i+1][j];
			mat[0][m2-1] -= rhc;
		} else {
			basic_vars.insert(prog.nV+i);
			map_const_var[i+1] = prog.nV + i;
		}
	}

	// Insert linear programm variables in non_basic_vars
	for(int j = 0; j < prog.nV; j++)
		non_basic_vars.insert(j);

	// inverse m and m2
	int temp = m;
	m = m2;
	m2 = temp;
}

LPArray::~LPArray() {
	if(mat) {
		for(int i = 0; i < n; i++)
			if(mat[i]) delete[] mat[i];
		delete[] mat;
	}
	if(objective) delete[] objective;
	if(map_const_var) delete[] map_const_var;
	if(num_entering) delete[] num_entering;
	basic_vars.clear();
	non_basic_vars.clear();
}

void LPArray::do_pivot(int entering_var, int constraint) {
	if(basic_vars.count(entering_var) > 0)
		throw "You try to enter a variable that was already a basic variable in the set of basic variables";
	Fraction d = mat[constraint][entering_var];
	if(d != 1)
		for(int j = 0; j < m; j++) mat[constraint][j] /= d;
	for(int i = 0; i < n; i++) {
		if(i != constraint) {
			Fraction mul = mat[i][entering_var];
			for(int j = 0; j < m; j++)
				mat[i][j] -= mul * mat[constraint][j];
		}
	}
	int leaving_var = map_const_var[constraint];
	basic_vars.erase(leaving_var);
	non_basic_vars.erase(entering_var);
	basic_vars.insert(entering_var);
	non_basic_vars.insert(leaving_var);
	map_const_var[constraint] = entering_var;
	num_pivot ++;
}

int LPArray::choose_entering(int rule) const {
	int entering;
	Fraction max = 0;
	int min;
	switch(rule) {
	
	case MAX:
		entering = -1;
		for(int v : non_basic_vars)
			if(mat[0][v] > max) {
				max = mat[0][v];
				entering = v;
			}
		return entering;
	
	case BLAND:
		for(int v : non_basic_vars)
			if(mat[0][v] > 0)
				return v;
		return -1;
	
	case OWN:
		entering = -1;
		for(int v : non_basic_vars)
			if(mat[0][v] > 0 && (entering == -1 || num_entering[v] < min)) {
				min = num_entering[v];
				entering = v;
			}
		return entering;

	default:
		std::cerr << "You try to use a rule that doesn't exist !!!\n";
		throw;
	
	}
}

int LPArray::choose_constraint(int entering) const {
	int cons = -1;
	int leaving;
	Fraction min, min2;
	for(int i = 1; i < n; i++) {
		if(mat[i][entering] > 0) {
			min2 = mat[i][m-1] / mat[i][entering];
			if(cons == -1 || min2 < min || (min2 == min && map_const_var[i] < leaving)) {
				min = min2;
				cons = i;
				leaving = map_const_var[i];
			}
		}
	}
	return cons;
}

bool LPArray::one_phase(int rule, bool show) {
	int entering, constraint;
	if(show) {
		std::cout << "The initial tableau is:\n\n";
		print();
	}
	while((entering = choose_entering(rule)) != -1)
		if((constraint = choose_constraint(entering)) == -1)
			return true;
		else {
			int leaving = map_const_var[constraint];
			do_pivot(entering, constraint);
			if(show) {
				std::cout << "\nThe entering variable is x_" << entering+1;
				std::cout << "\nThe leaving variable is x_" << leaving+1 << "\n\n";
				print();
			}
		}
	return false;
}

void LPArray::step_one_to_two() {
	for(int j = m2-1; j < m-1; j++)
		if(non_basic_vars.count(j) > 0)
			non_basic_vars.erase(j);
		else {
			int entering = *(non_basic_vars.begin());
			int constraint = 0;
			while(mat[++constraint][j] == 0);
			do_pivot(entering, constraint);
			non_basic_vars.erase(j);
		}
	for(int i = 1; i < n; i++)
		mat[i][m2-1] = mat[i][m-1];
	m = m2;
	for(int j = 0; j < m; j++)
		mat[0][j] = objective[j];
	for(int i = 1; i < n; i++) {
		int bv = map_const_var[i];
		Fraction mul = mat[0][bv];
		if(mul != 0) {
			for(int j = 0; j < m; j++)
				mat[0][j] -= mul * mat[i][j];
		}
	}
}

void LPArray::print() const {
	int *max_size = new int[m];
	int line_size = 0;
	for(int j = 0; j < m; j++) {
		int ms = 0;
		for(int i = 0; i < n; i++)
			ms = std::max(ms, mat[i][j].str_len());
		max_size[j] = ms;
		line_size += ms;
	}
	line_size += (m-1)*2 + 1;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			int nspaces = max_size[j] - mat[i][j].str_len();
			int ns2 = nspaces / 2;
			for(int k = 0; k < ns2; k++) std::cout << ' ';
			std::cout << mat[i][j];
			for(int k = ns2; k < nspaces; k++) std::cout << ' ';
			if(j == m-2) std::cout << " | ";
			else if(j == m-1) std::cout << "\n";
			else std::cout << "  ";
		}
		if(i == 0) {
			for(int j = 0; j < line_size; j++) std::cout << '-';
			std::cout << '\n';
		}
	}
}

Fraction* LPArray::get_solution() const {
	int nV = m - n;
	Fraction *res = new Fraction[nV];
	for(int j = 0; j < nV; j++)
		res[j] = 0;
	for(int i = 1; i < n; i++) {
		int v = map_const_var[i];
		if(v < nV) res[v] = mat[i][m-1];
	}
	return res;
}

std::string LPArray::getRuleName(int rule) {
	switch(rule) {
	case MAX:
		return "MAXIMUM COEFFICIENT";
	case BLAND:
		return "BLAND";
	case OWN:
		return "LESS ENTERING";
	default:
		return "THIS IS NOT A RULE";
	}
}