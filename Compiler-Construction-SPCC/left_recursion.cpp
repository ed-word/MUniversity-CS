#include <bits/stdc++.h>
using namespace std;


template <class Container>
void split(string &str, Container &cont, char delim)
{
    stringstream ss(str);
    string token;
    while (std::getline(ss, token, delim)) {
        cont.insert(token);
    }
}


int main() {
	string str, variable, productions;
	string epsilon (u8"\u03B5");
	set <string> tokens, alpha, beta;
	map < string, set<string> > production_map;	//Hash map with key as Variable and productions in set

	cout << "Enter Productions: " << endl;
	while(getline(cin, str) && !str.empty()) {
		//eg str = "A->abc|Ab"
		variable = str[0];
		productions = str.substr(3, str.length());
		
		split(productions, tokens, '|');
		production_map[variable] = tokens;	//map[key] = production set;
		tokens.clear();
	}

	for(auto it: production_map) {
		alpha.clear();
		beta.clear();

		variable = it.first;	//it.first: Key, it.second: Vector
		for(auto i: it.second) {
			str = i[0];
			if(variable.compare(str) == 0) {
				//Left Recursion
				alpha.insert(i.substr(1, i.length()));
			}
			else {
				beta.insert(i);
			}
		}
		if(!alpha.empty()) {
			//A->beta1A'|beta2A'
			for(auto k: beta) {
				tokens.insert(k + variable+'\'');
			}
			production_map[variable] = tokens;
			tokens.clear();

			//A'->alpha1A'|alpha2A'|ε
			for(auto k: alpha) {
				tokens.insert(k + variable+'\'');
			}
			tokens.insert(epsilon);	//Epsilon
			production_map[variable+'\''] = tokens;
			tokens.clear();			
		}	
	}

	cout << "Result: " << endl;
	for(auto it: production_map) {
		cout << it.first << "->";
		for(auto i: it.second)
			cout << i << "|";
		cout << endl;
	}
}

/*
Enter Productions: 
S->S0S1S|01

Result: 
S->01S'|
S'->0S1SS'|ε|
*/