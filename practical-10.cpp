#include <iostream>
#include <stack>
#include <cmath>
#include <cctype>
#include <string>

using namespace std;

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

double applyOperation(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return pow(a, b);
        default: return 0;
    }
}

double evaluateExpression(const string& expr) {
    stack<double> values;
    stack<char> operators;

    for (size_t i = 0; i < expr.length(); i++) {
        if (isspace(expr[i])) continue;
        if (isdigit(expr[i]) || expr[i] == '.') {
            string value = "";
            while (i < expr.length() && (isdigit(expr[i]) || expr[i] == '.')) {
                value += expr[i];
                i++;
            }
            i--;
            values.push(stod(value));
        }
        else if (expr[i] == '(') {
            operators.push(expr[i]);
        }
        else if (expr[i] == ')') {
            while (!operators.empty() && operators.top() != '(') {
                char op = operators.top(); operators.pop();
                double b = values.top(); values.pop();
                double a = values.top(); values.pop();
                values.push(applyOperation(a, b, op));
            }
            if (!operators.empty() && operators.top() == '(') {
                operators.pop();
            } else {
                throw invalid_argument("Invalid expression: mismatched parentheses.");
            }
        }
        else if (isOperator(expr[i])) {
            while (!operators.empty() && precedence(operators.top()) >= precedence(expr[i])) {
                char op = operators.top(); operators.pop();
                double b = values.top(); values.pop();
                double a = values.top(); values.pop();
                values.push(applyOperation(a, b, op));
            }
            operators.push(expr[i]);
        } else {
            throw invalid_argument("Invalid expression: unexpected character.");
        }
    }

    while (!operators.empty()) {
        char op = operators.top(); operators.pop();
        double b = values.top(); values.pop();
        double a = values.top(); values.pop();
        values.push(applyOperation(a, b, op));
    }

    if (values.size() != 1) {
        throw invalid_argument("Invalid expression: too many values left.");
    }

    return values.top();
}

int main() {
    string expression;
    cout << "Enter an arithmetic expression: ";
    getline(cin, expression);

    try {
        double result = evaluateExpression(expression);
        cout << "Result: " << result << endl;
    } catch (const exception& e) {
        cout << e.what() << endl;
    }

    return 0;
}
