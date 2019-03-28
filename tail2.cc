/**
 *	@file	tail2.cc
 *	@author	Simon Sedlacek, FIT
 *	@date	28.3.2019
 *	@note	Reseni: IJC-DU2, priklad 1b)
 *	Prelozeno: g++ 8.3.1 - Fedora release 29 (Twenty Nine) x86_64 
 */

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <cstring>

using namespace std;


/** @brief Prints the last n lines from a file */
void tail(istream& source, unsigned n);

/** @brief Prints all the lines starting from line n */
void tailPlus(istream& source, unsigned n);

/** @brief Parses the arguments for the program */
int parseArguments(int argc, char *argv[], ifstream& source, unsigned& n, bool& plus);


int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);

    unsigned n = 10;
    bool plus = false;
    ifstream source;

    if (parseArguments(argc, argv, source, n, plus) == 1)
        return 1;

    if (n == 0 && plus == false) {
        if (source.is_open())
            source.close();
        return 0;
    }

    if (source.is_open()) {

        if (plus)
            tailPlus(source, n);
        else
            tail(source, n);

        source.close();

    } else {

        if (plus)
            tailPlus(cin, n);
        else
            tail(cin, n);
    }

    return 0;
}


/*============================================================*/
/*                    Function definitions                    */

void tail(istream& source, unsigned n) {
    string line;
    queue<string> lines;

    while (getline(source, line)) {
        if (lines.size() >= n) {
            lines.pop();
            lines.push(line);
        }
    }

    while (!lines.empty()) {
        cout << lines.front() << endl;
        lines.pop();
    }
}

void tailPlus(istream& source, unsigned n) {
    string line;

    /* Start indexing from 1 because +0 and +1 options have to behave
     * the same way */
    for (unsigned i = 1; i < n; i++)
        getline(source, line);

    while (getline(source, line))
        cout << line << endl; 
}

int parseArguments(int argc, char *argv[], ifstream& source, unsigned& n, bool& plus) {
        char *endptr = NULL;

        if (argc == 1) {
            return 0;

        } else if (argc == 2) {
            source.open(argv[1]);
            if (source.is_open() == false) {
                cerr << "Error: could not open file " << argv[1] << endl;
                return 1;
            }

        } else if (argc == 3 || argc == 4) {
            if (strcmp("-n", argv[1])) {
                cerr << "Error: unknown program argument " << argv[1] << endl;
                return 1;
            }

            if (argv[2][0] == '+')
                plus = true;
            if (argv[2][0] == '-') {
                cerr << "Error: the argument '-n' does "
                        "not accept negative values" << endl;
                return 1;
            }

            n = strtoul(argv[2], &endptr, 10);

            if (strcmp(endptr, "")) {
                cerr << "Error: parameter of '-n' "
                    "is not decimal" << endl;
                return 1;
            }

            if (argc == 4) {
                source.open(argv[3]);
                if (source.is_open() == false) {
                    cerr << "Error: could not open file " << argv[3] << endl;
                    return 1;
                }

            } else {
                return 0;
            }

        } else {
            cerr << "Error: Too many program arguments" << endl;
            return 1;
    }
    return 0;
}
