#include <iostream>
#include <vector>
using namespace std;

struct Transition {
    int current_state;
    char symbol;
    int next_state;
};

int main() {
    int num_symbols, num_states, num_accepting, initial_state, num_transitions;
    vector<char> symbols;
    vector<int> accepting_states;
    vector<Transition> transitions;
    string input_string;

    cout << "Number of input symbols: ";
    cin >> num_symbols;
    cout << "Input symbols: ";
    for (int i = 0; i < num_symbols; i++) {
        char sym;
        cin >> sym;
        symbols.push_back(sym);
    }

    cout << "Enter number of states: ";
    cin >> num_states;
    cout << "Initial state: ";
    cin >> initial_state;
    cout << "Number of accepting states: ";
    cin >> num_accepting;
    cout << "Accepting states: ";
    for (int i = 0; i < num_accepting; i++) {
        int state;
        cin >> state;
        accepting_states.push_back(state);
    }

    cout << "Enter number of transitions: ";
    cin >> num_transitions;
    cout << "Transition table: " << endl;
    for (int i = 0; i < num_transitions; i++) {
        int current, next;
        char symbol;
        cin >> current >> symbol >> next;
        transitions.push_back({current, symbol, next});
    }

    cout << "Input string: ";
    cin >> input_string;

    int current_state = initial_state;
    for (char ch : input_string) {
        bool found = false;
        for (auto t : transitions) {
            if (t.current_state == current_state && t.symbol == ch) {
                current_state = t.next_state;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Invalid string" << endl;
            return 0;
        }
    }

    for (int state : accepting_states) {
        if (current_state == state) {
            cout << "Valid string" << endl;
            return 0;
        }
    }

    cout << "Invalid string" << endl;
    return 0;
}
