#include <bits/stdc++.h>
using namespace std;


template <class Container>
string infix_to_postfix(string input, Container &precedence) {
	string postfix;
	stack <char> st;	//Char stack

	for (char ch: input) {
		if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
			postfix.push_back(ch);
		} else if (ch == '(') {
			st.push(ch);
		} else if (ch == ')') {
			while (st.top() != '(') {
				postfix.push_back(st.top());
				st.pop();
			}
			st.pop();
		} else {
			if (st.empty()) {
				st.push(ch);
			} else if (precedence[ch] > precedence[st.top()] || (ch == st.top() && ch == '^')) {
				st.push(ch);
			} else {
				while (!st.empty() && precedence[ch] <= precedence[st.top()]) {
					postfix.push_back(st.top());
					st.pop();
				}
				st.push(ch);
			}
		}
	}

	while (!st.empty()) {
		postfix.push_back(st.top());
		st.pop();
	}

	return postfix;
}


vector<string> assignment(string input) {
	map <char, int> precedence = {
		{'+', 0}, {'-', 0},
		{'*', 2}, {'/', 2},
		{'^', 3}
	};
	string res_var (string(1, input[0]));	//k=a+b, res_var=k
	input = input.substr(2);	//input=a+b

	string postfix (infix_to_postfix(input, precedence));
	vector <string> three_ac;
	stack <string> st;	//String stack since t1, t2.. are strings not char
	int reg_no = 1;

	cout << "Postfix: " << postfix << endl;

	for(char ch: postfix) {
		if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
			st.push(string(1, ch));
		} else {
			string reg_name (string(1, 't') + to_string(reg_no++));
			string output (reg_name + string(1, '='));
			string opr2 (st.top()); st.pop();
			string opr1 (st.top()); st.pop();
			output += opr1 + string(1, ch) + opr2;
			three_ac.push_back(output);

			st.push(reg_name);
		}
	}
	string reg_name (string(1, 't') + to_string(--reg_no));
	three_ac.push_back(res_var + string(1, '=') + reg_name);

	return three_ac;
}


vector<string> boolean(string input) {
	map <char, int> precedence = {
		{'|', 0}, 
		{'&', 1},
		{'>', 2}, {'<', 2}, {':', 2}, {';', 2}, {'=', 2}, {',', 2},
		{'!', 3}
	};
	map <char, string> op_dict = {
		{'|', "||"}, 
		{'&', "&&"},
		{'>', ">"}, {'<', "<"}, {':', ">="}, {';', "<="}, {'=', "=="}, {',', "!="},
		{'!', "!"}
	};	
	string res_var (string(1, input[0]));	//k=a+b, res_var=k
	input = input.substr(2);	//input=a+b

	for (auto it: op_dict) {
		string from = it.second;
		string to = string(1, it.first);
		size_t start_pos = 0;
		while ((start_pos = input.find(it.second, start_pos)) != std::string::npos) {
			input.replace(start_pos, from.length(), to);
			start_pos += to.length();
		}
	}
	string postfix (infix_to_postfix(input, precedence));
	cout << "Postfix: " << postfix << endl;

	vector <string> three_ac;
	stack <string> st;	//String stack since t1, t2.. are strings not char
	int reg_no = 1, line_no = 100;

	for(char ch: postfix) {
		if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
			st.push(string(1, ch));
		} else if (ch == '!') {
			string reg_name (string(1, 't') + to_string(reg_no++));
			string output (to_string(line_no++) + ": " + reg_name + string(1, '='));
			output += " not ";
			string opr1 (st.top()); st.pop();
			output += opr1;
			three_ac.push_back(output);
			st.push(reg_name);
		} else {
			string op_name = op_dict[ch];
			string reg_name (string(1, 't') + to_string(reg_no++));
			string opr2 (st.top()); st.pop();
			string opr1 (st.top()); st.pop();

			if (op_name == "&&" || op_name == "||") {
				string output (to_string(line_no++) + ": " + reg_name + string(1, '='));
				if (op_name == "&&")
					output += opr1 + " and " + opr2;
				else
					output += opr1 + " or " + opr2;
				three_ac.push_back(output);	
			} else {
				string output1 (to_string(line_no++) + ": If ");
				output1 += opr1 + op_name + opr2 + " goto " + to_string(line_no+2);
				string output2 (to_string(line_no++) + ": " + reg_name + "=0");
				string output3 (to_string(line_no++) + ": " + "goto " + to_string(line_no+2));
				string output4 (to_string(line_no++) + ": " + reg_name + "=1");
				three_ac.push_back(output1);
				three_ac.push_back(output2);
				three_ac.push_back(output3);
				three_ac.push_back(output4);
			}
			st.push(reg_name);
		}
	}
	string reg_name (string(1, 't') + to_string(--reg_no));
	three_ac.push_back(to_string(line_no++) + ": " + res_var + string(1, '=') + reg_name);

	return three_ac;
}


vector<string> control(vector<string> in_vec) {
	vector <string> three_ac;
	int reg_no = 1, line_no = 100;

	string first_line = in_vec[0];
	size_t open_br = first_line.find("(");
	size_t close_br = first_line.find(")");
	string condn = first_line.substr(open_br+1, close_br-open_br-1);

	string output1 (to_string(line_no++) + ": If " + condn);
	output1 += " goto " + to_string(line_no+1);
	string output2 (to_string(line_no++) + ": goto ");
	three_ac.push_back(output1);
	three_ac.push_back(output2);

	for(int i=1; i<in_vec.size(); i++) {
		string line = in_vec[i];
		if(line.find("{") == string::npos && line.find("}") == string::npos) {
			if(line.find("if") == string::npos) {
				string output (to_string(line_no++) + ": " + line);
				three_ac.push_back(output);
			} else {
				open_br = line.find("(");
				close_br = line.find(")");
				condn = line.substr(open_br+1, close_br-open_br-1);
				string output1 (to_string(line_no++) + ": If " + condn);
				output1 += " goto " + to_string(line_no+1);

				int j = i;
				while (true) {
					j++;
					string templine = in_vec[j];
					if(templine.find("}") != string::npos)
						break;
				}
				string output2 (to_string(line_no++) + ": goto " + to_string(line_no+j-i-2+1));
				three_ac.push_back(output1);
				three_ac.push_back(output2);
			}
		}
	}
	string output (to_string(line_no++) + ": " + "goto " + to_string(100));
	three_ac.push_back(output);
	three_ac[1] += to_string(line_no);

	return three_ac;
}


int main() {
	string input;
	vector <string> three_ac;

	int selection;
	cout << "1.Assignment\t2.Boolean\t3.Control : ";
	cin >> selection;
	cout << "Enter Input: " << endl;

	if (selection == 1) {
		cin >> input;
		three_ac = assignment(input);
	} else if (selection == 2) {
		cin >> input;
		three_ac = boolean(input);
	} else {
		cin.ignore();
		vector <string> in_vec;
		while(getline(cin, input) && !input.empty()) {
			in_vec.push_back(input);
		}
		three_ac = control(in_vec);
	}

	cout << endl << "Intermediate Code: " << endl;
	for (auto it: three_ac)
		cout << it << endl;

	return 0;
}

/*
1.Assignment	2.Boolean	3.Control : 1
Enter Input: k=a+b*c-d/e*f
Postfix: abc*+de/f*-

Intermediate Code: 
t1=b*c
t2=a+t1
t3=d/e
t4=t3*f
t5=t2-t4
k=t5


1.Assignment	2.Boolean	3.Control : 2
Enter Input: k=a>b&&!c>d&&e<f
Postfix: ab>c!d>&ef<&

Intermediate Code: 
100: If a>b goto 103
101: t1=0
102: goto 104
103: t1=1
104: t2= not c
105: If t2>d goto 108
106: t3=0
107: goto 109
108: t3=1
109: t4=t1 and t3
110: If e<f goto 113
111: t5=0
112: goto 114
113: t5=1
114: t6=t4 and t5
115: k=t6


1.Assignment	2.Boolean	3.Control : 3
Enter Input: 
while(i<20)
{
i=i*2;         
if(i == 5)
{
count++;
flag=1;
}
count--;
}


Intermediate Code: 
100: If i<20 goto 102
101: goto 109
102: i=i*2;
103: If i == 5 goto 105
104: goto 107
105: count++;
106: flag=1;
107: count--;
108: goto 100
*/