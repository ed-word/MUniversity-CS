#include <bits/stdc++.h>
using namespace std;

int var = (int)'K';

template <class Container>
void split(string &str, Container &cont, char delim)
{
    stringstream ss(str);
    string token;
    while (std::getline(ss, token, delim)) {
        cont.insert(token);
    }
}

map <string, vector <string> > alreadyCalled;
template <class Container>
int find_leftrec(string variable, set<string> prod_set, string called_var, Container &production_map, set<string> &alpha, set <string> &beta) {
	string str;
	set <string> tokens;
	string epsilon (u8"\u03B5");
	int flag=0;

	if (find(alreadyCalled[variable].begin(), alreadyCalled[variable].end(), called_var) != alreadyCalled[variable].end()) {
		if (find(prod_set.begin(), prod_set.end(), variable) == prod_set.end())
			return 0;
		return 1;
	}
	alreadyCalled[variable].push_back(called_var);

	for(auto i: prod_set) {
		str = i[0];
		char x = i[0];
		
		if (variable.compare(str) == 0) {
			//Left Recursion
			alpha.insert(i.substr(1, i.length()));
			flag = 1;
		} else if ((x >= 'A' && x <= 'Z')) {
			if (variable != str) {
				flag = find_leftrec(variable, production_map[str], str, production_map, alpha, beta);
				if (flag == 1) 
					alpha.insert(i.substr(1, i.length()));
			}
		} else {
			beta.insert(i);
		}
	}
	if (variable == called_var) {
		if(!alpha.empty()) {
			//A->beta1A'|beta2A'
			for(auto k: beta) {
				tokens.insert(k + string(1, (char)var));
			}
			production_map[variable] = tokens;
			tokens.clear();

			//A'->alpha1A'|alpha2A'|ε
			for(auto k: alpha) {
				if (!k.empty())
					tokens.insert(k + string(1, (char)var));
			}
			tokens.insert(epsilon);	//Epsilon
			production_map[string(1, (char)var)] = tokens; 
			tokens.clear();
			var++;			
		}
	} else {
		return flag;
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
	for (auto it: production_map) {
		alpha.clear();
		beta.clear();
		find_leftrec(it.first, it.second, it.first, production_map, alpha, beta);
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
A->B|C|f
B->Ae
C->Ad

Result: 
A->fK|
B->Ae|
C->Ad|
K->dK|eK|ε|
*/
