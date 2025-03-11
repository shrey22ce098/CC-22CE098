#include <stdio.h>
#include <stdbool.h>
#include <string.h>

char *input;
bool L();
bool S();
bool L_prime();

bool S() {
    if (*input == '(') {
        input++;
        if (L()) {
            if (*input == ')') {
                input++;
                return true;
            }
        }
        return false;
    } else if (*input == 'a') {
        input++;
        return true;
    }
    return false;
}

bool L() {
    if (S()) {
        if (L_prime()) {
            return true;
        }
    }
    return false;
}

bool L_prime() {
    if (*input == ',') {
        input++;
        if (S()) {
            if (L_prime()) {
                return true;
            }
        }
        return false;
    }
    return true;
}

void validateString(const char *str) {
    input = str;
    if (S() && *input == '\0') {
        printf("Valid string\n");
    } else {
        printf("Invalid string\n");
    }
}

int main() {
    const char *testcases[] = {"a", "(a)", "(a,a)", "(a,(a,a),a)", "(a,a),(a,a)",
                               "a)", "(a", "a a,a", "(a,a", "(a,a,a,a"};
    int num_testcases = sizeof(testcases) / sizeof(testcases[0]);

    for (int i = 0; i < num_testcases; i++) {
        printf("Input: %s -> ", testcases[i]);
        validateString(testcases[i]);
    }

    return 0;
}
