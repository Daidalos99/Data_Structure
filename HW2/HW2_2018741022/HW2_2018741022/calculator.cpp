#include <stack>
#include <cctype>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>

using namespace std;

int priority(char c)
// precondition: input char must be an operator(+-*/)
// postcondition: returns priority of specific operator
{
	switch (c)
	{
	case '(':
	case '{':
	case '[':
		return 0;
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	default:
		break;
	}
}

double evaluate(char oper, double opr1, double opr2) 
// precondition: opr1, opr2 should be positive real number, oper must be an operator
// postcondition: returns the result of operation using parameters
{
	switch (oper) {
	case '+': return (opr1 + opr2);
	case '-': return (opr1 - opr2);
	case '*': return (opr1 * opr2);
	case '/': return (opr1 / opr2);
	}
}

string in2post(string infix) 
// precondition: needs a infix notation
// postcondition: returns postfix notation
{
	string postfix;
	stack<char> operations;

	for (int i = 0; i < infix.length(); i++) {
		// left parentheses
		if (infix[i] == '(' || infix[i] == '{' || infix[i] == '[') {
			operations.push(infix[i]);
		}
		// number or decimal point(operand)
		else if ((infix[i] >= '0' && infix[i] <= '9') || infix[i] == '.') {
			postfix += infix[i];
		}
		// operator(+-*/)
		else if (strchr("+-*/", infix[i]) != NULL) {
			postfix += ' ';
			if (!operations.empty()) {
				if (operations.top() != '(' && operations.top() != '{' && operations.top() != '[') {
					if (priority(operations.top()) >= priority(infix[i])) {
						while (operations.top() != '(' && operations.top() != '{' && operations.top() != '[') {
							postfix += operations.top();
							postfix += ' ';
							operations.pop();
							if (operations.empty()) break;
						}
						operations.push(infix[i]);
					}
					else if (priority(operations.top()) < priority(infix[i])) {
						operations.push(infix[i]);
					}
				}
				else operations.push(infix[i]);
			}
			else operations.push(infix[i]);
		}
		// right parentheses
		else if (infix[i] == ')' || infix[i] == '}' || infix[i] == ']') {
			while (true) {
				// Cases for unbalanced parentheses
				if (infix[i] == ')') {
					if (operations.top() == '{' || operations.top() == ']') {
						return "err";
					}
					else if (operations.top() == '(') break;
					else {
						postfix += ' ';
						postfix += operations.top();
						operations.pop();
					}
				}
				else if (infix[i] == '}') {
					if (operations.top() == '(' || operations.top() == ']') {
						return "err";
					}
					else if (operations.top() == '{') break;
					else {
						postfix += ' ';
						postfix += operations.top();
						operations.pop();
					}
				}
				else if (infix[i] == ']') {
					if (operations.top() == '(' || operations.top() == '{') {
						return "err";
					}
					else if (operations.top() == '[') break;
					else {
						postfix += ' ';
						postfix += operations.top();
						operations.pop();
					}
				}
			}
			operations.pop();
		}
	}
	// if there is something still left in stack, add to postfix and pop
	if (!operations.empty()) {
		postfix += ' ';
		postfix += operations.top();
		operations.pop();
	}
	return postfix;
}

double post_eval(string postfix) 
// precondition: before starting this method, you need a postfix notation of your input.
// postcondition: After this method, you'll get the evaluate of the postfix.
{
	double answer;
	string temp;
	stack<double> operands;
	for (int i = 0; i < postfix.length(); i++) {
		if (postfix[i] != ' ') {
			// if the current element is operand
			if ((postfix[i] >= '0' && postfix[i] <= '9') || postfix[i] == '.') {
				temp += postfix[i];
			}
			// if the current element is operator
			else if (strchr("+-*/", postfix[i]) != NULL) {
				double opr2 = operands.top();
				operands.pop();
				double opr1 = operands.top();
				operands.pop();
				operands.push(evaluate(postfix[i], opr1, opr2));			
			}
		}
		else if (postfix[i] == ' ') {
			if (temp != "") { // if not an empty string
				operands.push(stod(temp));
			}
			temp = ""; // reinitialize temp to empty string
		}
	}
	if (!operands.empty()) {
		answer = operands.top();
		operands.pop();
		return answer;
	}
	exit(0); 
}

void Calculator() 
// postcondition: After completing this method, you will get teh answer of your infix input.
//				  Works as a Calculator.
{
	string infix;	// input of calculator
	double answer;

	while (true) {
		cin >> infix;
		if (infix == "EOI") break; // Break when EOI
		string postfix = in2post(infix);
		if (postfix == "err") cout << "Error!: unbalanced parentheses" << endl;
		else {
			cout << postfix << endl;
			answer = post_eval(postfix);
			if (!isfinite(answer)) cout << "Error!: dvide by zero" << endl;
			else cout << round(answer * 1000) / 1000 << endl;	// round off to the nearest thousandth
		}
		cout << endl;
	}
}

int main() {
	Calculator();
	return 0;
}