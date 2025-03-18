//https://github.com/ahmedibrahimX/Mini-Compiler?tab=readme-ov-file
#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

struct Quadruple {
    string op;
    string arg1;
    string arg2;
    string result;
};

int tempCount = 1;

// Function to generate temporary variable names
string newTemp() {
    return "t" + to_string(tempCount++);
}

// Function to check operator precedence
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Convert infix expression to postfix (Shunting Yard Algorithm)
string infixToPostfix(const string& expression) {
    stack<char> operators;
    string postfix;

    for (char c : expression) {
        if (isdigit(c) || c == '.') {
            postfix += c;  // Append operand to postfix expression
        } else if (c == '(') {
            operators.push(c);
        } else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix += ' ';
                postfix += operators.top();
                operators.pop();
            }
            operators.pop();  // Pop '('
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            postfix += ' ';
            while (!operators.empty() && precedence(operators.top()) >= precedence(c)) {
                postfix += operators.top();
                operators.pop();
            }
            operators.push(c);
        }
    }

    while (!operators.empty()) {
        postfix += ' ';
        postfix += operators.top();
        operators.pop();
    }

    return postfix;
}

// Generate quadruples for a postfix expression
vector<Quadruple> generateQuadruples(const string& postfix) {
    stack<string> operands;
    vector<Quadruple> quadruples;

    string temp = "";
    for (char c : postfix) {
        if (isdigit(c) || c == '.') {
            temp += c;
        } else if (c == ' ') {
            if (!temp.empty()) {
                operands.push(temp);
                temp.clear();
            }
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            string arg2 = operands.top(); operands.pop();
            string arg1 = operands.top(); operands.pop();
            string result = newTemp();
            quadruples.push_back({string(1, c), arg1, arg2, result});
            operands.push(result);
        }
    }

    return quadruples;
}

void displayQuadruples(const vector<Quadruple>& quadruples) {
    cout << "Operator\tOperand1\tOperand2\tResult\n";
    for (const auto& q : quadruples) {
        cout << q.op << "\t\t" << q.arg1 << "\t\t" << q.arg2 << "\t\t" << q.result << "\n";
    }
}

int main() {
    string expression;
    cout << "Enter an arithmetic expression: ";
    getline(cin, expression);

    string postfix = infixToPostfix(expression);
    vector<Quadruple> quadruples = generateQuadruples(postfix);

    displayQuadruples(quadruples);

    return 0;
}
