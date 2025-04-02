#include <iostream>
#include <vector>
#include <stack>
#include <cctype>
#include <sstream>
using namespace std;

struct Quadruple {
    string op, arg1, arg2, result;
};

vector<Quadruple> quadruples;
int tempVarCount = 1;

string newTemp() {
    return "t" + to_string(tempVarCount++);
}

int precedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

string generateQuadruple(string op, string arg1, string arg2) {
    string res = newTemp();
    quadruples.push_back({op, arg1, arg2, res});
    return res;
}

string parseExpression(string expr) {
    stack<string> values;
    stack<char> ops;
    
    for (size_t i = 0; i < expr.length(); i++) {
        if (isspace(expr[i])) continue;
        
        if (isdigit(expr[i])) {
            stringstream num;
            while (i < expr.length() && isdigit(expr[i])) {
                num << expr[i];
                i++;
            }
            values.push(num.str());
            i--;
        }
        else if (expr[i] == '(') {
            ops.push(expr[i]);
        }
        else if (expr[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                string val2 = values.top(); values.pop();
                string val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(generateQuadruple(string(1, op), val1, val2));
            }
            ops.pop();
        }
        else {
            while (!ops.empty() && precedence(ops.top()) >= precedence(expr[i])) {
                string val2 = values.top(); values.pop();
                string val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(generateQuadruple(string(1, op), val1, val2));
            }
            ops.push(expr[i]);
        }
    }
    
    while (!ops.empty()) {
        string val2 = values.top(); values.pop();
        string val1 = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(generateQuadruple(string(1, op), val1, val2));
    }
    
    return values.top();
}

void printQuadruples() {
    cout << "Operator\tOperand 1\tOperand 2\tResult" << endl;
    for (const auto &quad : quadruples) {
        cout << quad.op << "\t\t" << quad.arg1 << "\t\t" << quad.arg2 << "\t\t" << quad.result << endl;
    }
}

int main() {
    string expression;
    cout << "Enter an arithmetic expression: ";
    getline(cin, expression);
    
    try {
        parseExpression(expression);
        printQuadruples();
    } catch (const exception &e) {
        cout << "Invalid expression" << endl;
    }
    
    return 0;
}
