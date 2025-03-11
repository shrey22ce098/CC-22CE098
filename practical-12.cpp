#include <iostream>
#include <string>
#include <regex>
#include <map>
using namespace std;
string evaluateExpression(const string& expr) {
    regex pattern("(\\d+\\.\\d+|\\d+)\\s*([+*/-])\\s*(\\d+\\.\\d+|\\d+)");
    string result = expr;

    while (regex_search(result, pattern)) {
        smatch match;
        if (regex_search(result, match, pattern)) {
            double a = stod(match[1].str());
            double b = stod(match[3].str());
            char op = match[2].str()[0];

            double res;
            switch (op) {
            case '+':
                res = a + b;
                break;
            case '-':
                res = a - b;
                break;
            case '*':
                res = a * b;
                break;
            case '/':
                if (b != 0)
                    res = a / b;
                else
                    throw runtime_error("Division by zero");
                break;
            default:
                throw runtime_error("Unsupported operator");
            }

            result = regex_replace(result, pattern, to_string(res));
        }
    }

    return result;
}

string constantFolding(const std::string& input) {
    regex pattern("\\d+\\.\\d+|\\d+");
    auto words_begin = sregex_iterator(input.begin(), input.end(), pattern);
    auto words_end = sregex_iterator();

    string result = input;

    bool allConstants = true;
    for (char c : input) {
        if (c == 'x' || c == 'r' || c == 'a' || c == 'c' || c == 'g') {
            allConstants = false;
            break;
        }
    }

    if (allConstants) {
        return evaluateExpression(input);
    } else {
        regex opPattern("(\\d+\\.\\d+|\\d+)\\s*([+*/-])\\s*(\\d+\\.\\d+|\\d+)");
        while (regex_search(result, opPattern)) {
            smatch match;
            if (regex_search(result, match, opPattern)) {
                double a = stod(match[1].str());
                double b = stod(match[3].str());
                char op = match[2].str()[0];

                double res;
                switch (op) {
                case '+':
                    res = a + b;
                    break;
                case '-':
                    res = a - b;
                    break;
                case '*':
                    res = a * b;
                    break;
                case '/':
                    if (b != 0)
                        res = a / b;
                    else
                        throw runtime_error("Division by zero");
                    break;
                default:
                    throw runtime_error("Unsupported operator");
                }

                result = regex_replace(result, opPattern, to_string(res));
            }
        }

        return result;
    }
}

int main() {
    string input;
    cout << "Enter an arithmetic expression: ";
    getline(cin, input);

    string output = constantFolding(input);
    cout << "Optimized expression: " << output << endl;

    return 0;
}
