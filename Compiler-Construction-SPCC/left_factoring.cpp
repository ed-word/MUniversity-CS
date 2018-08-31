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
	string str, variable, productions, strtemp;
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

	for(auto it : production_map) {
		variable = it.first;	//it.first: Key, it.second: Vector

		for(auto i: it.second) {
			alpha.clear();
			beta.clear();
			
			str = i[0];
			//A->strAlpha1|strAlpha2|strAlpha3|beta1|beta2...
			for(auto j: it.second) {
				if(i.compare(j) != 0) {
					strtemp = j[0];
					if(str.compare(strtemp) == 0) {
						alpha.insert(j.substr(1, j.length()));
					}
					else {
						beta.insert(j);	
					}
				}
			}

			if(!alpha.empty()) {
				//A->strAlpha1|strAlpha2|strAlpha3|beta1|beta2... changes to
				//A->strA'|beta1|beta2... & A'->Alpha1|Alpha2...
				beta.insert(str + variable+'\'');
				alpha.insert(i.substr(1, i.length()));
				production_map[variable+'\''] = alpha;
				production_map[variable] = beta;
				break;
			}
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
S->aSSbS|aSaSb|abb|b

Result: 
S->aS'|b|
S'->SS''|bb|
S''->SbS|aSb|
*/
