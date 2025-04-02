#include <iostream>
#include <stack>
#include <cctype>
#include <cmath>
#include <sstream>
using namespace std;

int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

double applyOp(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return b != 0 ? a / b : throw runtime_error("Division by zero");
        case '^': return pow(a, b);
        default: throw runtime_error("Invalid operator");
    }
}

double evaluate(string expression) {
    stack<double> values;
    stack<char> ops;
    
    for (size_t i = 0; i < expression.length(); i++) {
        if (isspace(expression[i])) continue;
        
        if (isdigit(expression[i]) || expression[i] == '.') {
            stringstream num;
            while (i < expression.length() && (isdigit(expression[i]) || expression[i] == '.')) {
                num << expression[i];
                i++;
            }
            values.push(stod(num.str()));
            i--;
        }
        else if (expression[i] == '(') {
            ops.push(expression[i]);
        }
        else if (expression[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                double val2 = values.top(); values.pop();
                double val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            if (!ops.empty()) ops.pop();
        }
        else {
            while (!ops.empty() && precedence(ops.top()) >= precedence(expression[i])) {
                double val2 = values.top(); values.pop();
                double val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            ops.push(expression[i]);
        }
    }
    
    while (!ops.empty()) {
        double val2 = values.top(); values.pop();
        double val1 = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(applyOp(val1, val2, op));
    }
    
    return values.top();
}

int main() {
    string expression;
    cout << "Enter an arithmetic expression: ";
    getline(cin, expression);
    try {
        double result = evaluate(expression);
        cout << "Result: " << result << endl;
    } catch (const exception &e) {
        cout << "Invalid expression" << endl;
    }
    return 0;
}
