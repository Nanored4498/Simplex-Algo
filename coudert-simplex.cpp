#include <iostream>
#include "linear_prog.h"
#include "lp_array.h"
#include <string.h>

using namespace std;

int main(int argc, char* argv[]) {
	bool use_file = false;
	bool show = false;
	bool help = false;
	int rule = -1;
	string filename;
	for(int i = 1; i < argc; i++) {
		char* p = argv[i];
		if(p[0] == '-') {
			if(strcmp(p, "-h") == 0) help = true;
			else if(strcmp(p, "-m") == 0) {
				if(rule == -1) rule = LPArray::MAX;
				else {
					cerr << "You gave severals rule parameters. Only one rule should be given.\n";
					return 1;
				}
			} else if(strcmp(p, "-b") == 0) {
				if(rule == -1) rule = LPArray::BLAND;
				else {
					cerr << "You gave severals rule parameters. Only one rule should be given.\n";
					return 1;
				}
			} else if(strcmp(p, "-o") == 0) {
				if(rule == -1) rule = LPArray::OWN;
				else {
					cerr << "You gave severals rule parameters. Only one rule should be given.\n";
					return 1;
				}
			} else if(strcmp(p, "-v") == 0) show = true;
		} else {
			if(use_file) {
				cerr << "You gave severals filenames. Only one filename should be given.\n";
				return 1;
			} else {
				use_file = true;
				filename = p;
			}
		}
	}
	if(help) {
		cout << "This is a simplex algorithm !\n"
				"Usage: ./coudert-exec [-h] [-m -b -o] [-v] [filename] .\n"
				"Arguments:\n"
				"\t[-h]: Show help for this executable.\n"
				"\t[-m -b -o]: The RULE used.\n"
				"\t\t-m for MAXIMUM COEFFICIENT RULE.\n"
				"\t\t-b for BLAND'S RULE.\n"
				"\t\t-o for OWN RULE.\n"
				"\t[-v]: Verbose mode.\n"
				"\t[filename]: Name of the file where is stored the linear program. If there is no filename the program is readen in standard input.\n";
				return 0;
	}
	if(rule == -1) {
		cerr << "A rule should be given. Use -h option for more details.\n";
		return 1;
	}
	if(use_file)
		LinearProg(filename).simplex_solve(rule, show);
	else
		LinearProg(cin).simplex_solve(rule, show);
	return 0;
}