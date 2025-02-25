#include <iostream>
#include <string>

using namespace std;

class RecursiveDescentParser {
private:
    string input;
    int index;

    bool match(char expected_char) {
        if (index < input.length() && input[index] == expected_char) {
            index++;
            return true;
        }
        return false;
    }

    bool S() {
        if (match('a')) {
            return true;
        } else if (match('(')) {
            if (L()) {
                if (match(')')) {
                    return true;
                }
            }
        }
        return false;
    }

    bool L() {
        if (S()) {
            return LPrime();
        }
        return false;
    }

    bool LPrime() {
        if (match(',')) {
            if (S()) {
                return LPrime();
            }
            return false;
        }
        return true; // ε (epsilon case)
    }

public:
    RecursiveDescentParser(string str) {
        input = str;
        index = 0;
    }

    void parse() {
        if (S() && index == input.length()) {
            cout << "Valid string" << endl;
        } else {
            cout << "Invalid string" << endl;
        }
    }
};

int main() {
    string test_cases[] = {"a", "(a)", "(a,a)", "(a,(a,a),a)", "(a,a),(a,a)", "a)", "(a", "a,a", "a,","(a,a),a"};

    for (const string& test : test_cases) {
        cout << "Input: " << test << " → ";
        RecursiveDescentParser parser(test);
        parser.parse();
    }

    return 0;
}
