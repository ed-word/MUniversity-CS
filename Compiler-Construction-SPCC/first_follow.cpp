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


template <class Container>
set<string> find_first(string variable, Container &production_map) {
	set <string> tokens, temp;
	set <string> production_set = production_map[variable];

	for(auto it: production_set) {
		for(int i=0; i < it.length(); i++) {
			char x = it[i];
			//Terminals
			if(!(x >= 'A' && x <= 'Z')) {
				tokens.insert(string(1,x));
				break;
			}
			else {
				temp = find_first(string(1, x), production_map);
				auto j = find(temp.begin(),temp.end(),string(1,'e'));
				if(j == temp.end()) {
					//No epsilon found
					tokens.insert(temp.begin(), temp.end());
					break;
				}
				else {
					//Epsilon found
					//Check if last character of production
					if(i != it.length()-1) {
						temp.erase(j);
					}
					tokens.insert(temp.begin(), temp.end());					
				}		
			}
		}
	}
	return tokens;
}


template <class Container>
set<string> find_follow(string variable, Container &production_map, Container &first, Container &follow, string start_symbol) {
	set <string> tokens, temp;
	int flag=0;
	if(!follow[variable].empty()) {
		return follow[variable];
	}
	if(variable == start_symbol)
		tokens.insert(string(1, '$'));

	for(auto it: production_map) {
		string thisvariable = it.first;
		for(auto i: it.second) {
			for(int k=0; k<i.length(); k++) {
				char x = i[k];
				if(string(1,x) == variable) {
					if(k == i.length()-1) {
						//Last char, find follow of lhs of production
						//Check if lhs is same as variable eg B->aB
						if(variable != thisvariable) {
							temp = find_follow(thisvariable, production_map, first, follow, start_symbol);
							tokens.insert(temp.begin(), temp.end());
						}
					}
					else {
						flag = 0;
						while(k < i.length()) {
							k++;	//First of next symbol
							x = i[k];
							if(!(x >= 'A' && x <= 'Z')) {
								tokens.insert(string(1, x));
								if(x != 'e') {
									flag = 1;
									goto nextProd;
								}
							}
							else {
								temp = first[string(1, x)];
								auto j = find(temp.begin(),temp.end(),string(1,'e'));
								if(j == temp.end()) {
									//No epsilon found
									tokens.insert(temp.begin(), temp.end());
									flag = 1;
									goto nextProd;
								}
								else {
									//Epsilon found
									temp.erase(j);
									tokens.insert(temp.begin(), temp.end());
									//Check if last character of production
									//if last char and epsilon, find follow of lhs
									if(k == i.length()-1) {
										temp = find_follow(thisvariable, production_map, first, follow, start_symbol);
										tokens.insert(temp.begin(), temp.end());
									}					
								}						
							}
						}
					}
				}
				nextProd:
				if(flag == 1)
					break;
			}
		}
	}
	return tokens;
}


int main() {
	string str, variable, productions, strtemp;
	set <string> tokens, alpha, beta, temp;
	map < string, set<string> > production_map;	//Hash map with key as Variable and productions in set
	map < string, set<string> > first, follow;
	set <string> set_of_terminals;	//Set to eliminate duplicate terminals in first and follow
	string start_symbol;

	cout << "Enter Productions: " << endl;
	while(getline(cin, str) && !str.empty()) {
		//eg str = "A->abc|Ab"
		variable = str[0];
		productions = str.substr(3, str.length());
		split(productions, tokens, '|');
		production_map[variable] = tokens;	//map[key] = production set;
		tokens.clear();
	}
	cout << "Enter Start Symbol: ";
	cin >> start_symbol;

	//First
	for(auto it : production_map) {
		variable = it.first;	//it.first: Key, it.second: Vector
		temp = find_first(variable, production_map);
		first[variable] = temp;
	}
	
	//Follow
	for(auto it : production_map) {
		variable = it.first;	//it.first: Key, it.second: Vector
		temp = find_follow(variable, production_map, first, follow, start_symbol);
		if(temp.empty() || variable == start_symbol)
			temp.insert(string(1, '$'));
		follow[variable] = temp;
	}

	cout << "Variable\tFirst\t\tFollow" << endl;
	for(auto it: first) {
		cout << it.first << "\t->";	
		
		cout << "\t{ ";
		for(auto i: it.second)
			cout << i << " ";
		cout << "}";
		
		cout << "\t\t{ ";
		for(auto i: follow[it.first])
			cout << i << " ";
		cout << "}";

		cout << endl;
	}
	return 0;
}

/*
Enter Productions: 
S->ACB|CbB|Ba
A->da|BC
B->g|e
C->h|e

Enter Start Symbol: S
Variable	First		Follow
A	->	{ d e g h }		{  $ g h }
B	->	{ e g }		{  $ a g h }
C	->	{ e h }		{  $ b g h }
S	->	{ a b d e g h }		{ $ }
*/
