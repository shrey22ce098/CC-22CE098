#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

// Structure to represent a production rule
struct Production {
    string nonTerminal;
    vector<string> terminals;
};

// Function to compute FIRST set
void computeFirst(map<string, vector<Production>>& grammar, map<string, vector<string>>& first) {
    for (auto& rule : grammar) {
        for (auto& prod : rule.second) {
            if (prod.terminals[0][0] >= 'a' && prod.terminals[0][0] <= 'z') {
                first[rule.first].push_back(prod.terminals[0]);
            } else {
                // Recursively compute FIRST for non-terminals
                for (auto& term : prod.terminals) {
                    if (term[0] >= 'A' && term[0] <= 'Z') {
                        if (first.find(term) != first.end()) {
                            first[rule.first].insert(first[rule.first].end(), first[term].begin(), first[term].end());
                        }
                    } else {
                        first[rule.first].push_back(term);
                    }
                }
            }
        }
    }
}

// Function to compute FOLLOW set
void computeFollow(map<string, vector<Production>>& grammar, map<string, vector<string>>& follow) {
    for (auto& rule : grammar) {
        for (auto& prod : rule.second) {
            if (prod.terminals.size() > 1) {
                for (int i = 0; i < prod.terminals.size() - 1; ++i) {
                    if (prod.terminals[i][0] >= 'A' && prod.terminals[i][0] <= 'Z') {
                        if (follow.find(prod.terminals[i]) == follow.end()) {
                            follow[prod.terminals[i]] = {};
                        }
                        // Add FIRST of next terminal to FOLLOW
                        if (prod.terminals[i + 1][0] >= 'a' && prod.terminals[i + 1][0] <= 'z') {
                            follow[prod.terminals[i]].push_back(prod.terminals[i + 1]);
                        } else {
                            // Recursively add FIRST for non-terminals
                            for (auto& term : prod.terminals) {
                                if (term[0] >= 'A' && term[0] <= 'Z') {
                                    if (follow.find(term) != follow.end()) {
                                        follow[prod.terminals[i]].insert(follow[prod.terminals[i]].end(), follow[term].begin(), follow[term].end());
                                    }
                                } else {
                                    follow[prod.terminals[i]].push_back(term);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

// Function to construct predictive parsing table
void constructParsingTable(map<string, vector<Production>>& grammar, map<string, vector<string>>& first, map<string, vector<string>>& follow, map<string, map<string, string>>& parsingTable) {
    for (auto& rule : grammar) {
        for (auto& prod : rule.second) {
            for (auto& term : prod.terminals) {
                if (term[0] >= 'a' && term[0] <= 'z') {
                    parsingTable[rule.first][term] = prod.nonTerminal + " -> " + prod.terminals[0];
                } else {
                    // Handle non-terminals and epsilon
                    if (term == "ε") {
                        for (auto& f : follow[rule.first]) {
                            parsingTable[rule.first][f] = prod.nonTerminal + " -> ε";
                        }
                    }
                }
            }
        }
    }
}

// Function to check if grammar is LL(1)
bool isLL1(map<string, map<string, string>>& parsingTable) {
    for (auto& rule : parsingTable) {
        map<string, string> entries;
        for (auto& entry : rule.second) {
            if (entries.find(entry.second) != entries.end()) {
                return false; // Conflict found
            }
            entries[entry.second] = "";
        }
    }
    return true;
}

// Function to validate input string against grammar
bool validateString(map<string, map<string, string>>& parsingTable, string input) {
    vector<string> stack = {"S"}; // Start symbol
    input += "$"; // End marker

    while (!stack.empty()) {
        string top = stack.back();
        stack.pop_back();

        if (top[0] >= 'a' && top[0] <= 'z') {
            if (top != string(1, input[0])) return false; // Terminal mismatch
            input.erase(input.begin()); // Consume input
        } else {
            if (parsingTable.find(top) == parsingTable.end()) return false; // Non-terminal not in table
            if (input.empty()) return false; // Input exhausted prematurely

            if (parsingTable[top].find(string(1, input[0])) == parsingTable[top].end()) return false; // No production for input

            string prod = parsingTable[top][string(1, input[0])];
            // Push production onto stack in reverse order
            size_t pos = prod.find("->");
            string rhs = prod.substr(pos + 2);
            vector<string> rhsTerms;
            string term;
            for (char c : rhs) {
                if (c == ' ') {
                    if (!term.empty()) {
                        rhsTerms.push_back(term);
                        term.clear();
                    }
                } else {
                    term += c;
                }
            }
            if (!term.empty()) rhsTerms.push_back(term);

            for (int i = rhsTerms.size() - 1; i >= 0; --i) {
                stack.push_back(rhsTerms[i]);
            }
        }
    }

    return input == "$"; // Input fully consumed
}

int main() {
    int numRules;
    cout << "Enter the number of production rules: ";
    cin >> numRules;
    cin.ignore(); // Ignore newline character

    map<string, vector<Production>> grammar;

    for (int i = 0; i < numRules; ++i) {
        string nonTerminal, production;
        cout << "Enter non-terminal for rule " << i + 1 << ": ";
        getline(cin, nonTerminal);

        cout << "Enter production for rule " << i + 1 << " (space-separated, e.g., A B C): ";
        getline(cin, production);

        vector<string> terminals;
        size_t pos = 0;
        while ((pos = production.find(" ")) != string::npos) {
            terminals.push_back(production.substr(0, pos));
            production.erase(0, pos + 1);
        }
        terminals.push_back(production);

        Production prod;
        prod.nonTerminal = nonTerminal;
        prod.terminals = terminals;

        if (grammar.find(nonTerminal) == grammar.end()) {
            grammar[nonTerminal] = {};
        }
        grammar[nonTerminal].push_back(prod);
    }

    // Compute FIRST and FOLLOW sets
    map<string, vector<string>> first;
    map<string, vector<string>> follow;
    computeFirst(grammar, first);
    computeFollow(grammar, follow);

    // Construct predictive parsing table
    map<string, map<string, string>> parsingTable;
    constructParsingTable(grammar, first, follow, parsingTable);

    // Check if grammar is LL(1)
    if (isLL1(parsingTable)) {
        cout << "Grammar is LL(1)" << endl;
    } else {
        cout << "Grammar is not LL(1)" << endl;
    }

    // Validate input string
    string input;
    cout << "Enter the input string to validate: ";
    cin >> input;

    if (validateString(parsingTable, input)) {
        cout << "Valid string" << endl;
    } else {
        cout << "Invalid string" << endl;
    }

    return 0;
}
