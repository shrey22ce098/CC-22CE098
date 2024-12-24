#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATES 10
#define MAX_ALPHABET 36

// Define the maximum number of states and alphabet size
int numStates, numAcceptingStates, numAlphabet;
int startState;
int acceptingStates[MAX_STATES];
char alphabet[MAX_ALPHABET];
int transition[MAX_STATES][MAX_ALPHABET];  // Transition table

// Function to get the index of the character in the alphabet
int getAlphabetIndex(char ch) {
    for (int i = 0; i < numAlphabet; i++) {
        if (alphabet[i] == ch) {
            return i;  // Correct indexing: 0 to numAlphabet-1
        }
    }
    return -1;  // Return -1 if the character is not in the alphabet
}

// Function to check if a state is an accepting state
int isAcceptingState(int state) {
    for (int i = 0; i < numAcceptingStates; i++) {
        if (acceptingStates[i] == state) {
            return 1;  // State is accepting
        }
    }
    return 0;  // State is not accepting
}

// Function to simulate the finite automaton
int simulateFA(char *input) {
    int currentState = startState;

    // Process each character in the input string
    for (int i = 0; i < strlen(input); i++) {
        int symbolIndex = getAlphabetIndex(input[i]);
        if (symbolIndex == -1) {
            printf("Invalid symbol in input string: %c\n", input[i]);
            return 0;  // Invalid input
        }

        // Transition to the next state based on the symbol
        currentState = transition[currentState - 1][symbolIndex];  // Adjust for 0-based indexing
    }

    // Check if the current state is an accepting state
    if (isAcceptingState(currentState)) {
        return 1;  // Accept the string
    } else {
        return 0;  // Reject the string
    }
}

int main() {
    // Input the number of states
    printf("Enter the number of states: ");
    scanf("%d", &numStates);

    // Input the starting state
    printf("Enter the starting state (1 to %d): ", numStates);
    scanf("%d", &startState);

    // Input the number of accepting states
    printf("Enter the number of accepting states: ");
    scanf("%d", &numAcceptingStates);

    // Input the accepting states
    printf("Enter the accepting states: ");
    for (int i = 0; i < numAcceptingStates; i++) {
        scanf("%d", &acceptingStates[i]);
    }

    // Input the input alphabet
    printf("Enter the number of symbols in the alphabet: ");
    scanf("%d", &numAlphabet);
    printf("Enter the symbols in the alphabet: ");
    for (int i = 0; i < numAlphabet; i++) {
        scanf(" %c", &alphabet[i]);  // Use space before %c to skip whitespace
    }

    // Input the transition function
    printf("Enter the transition function:\n");
    for (int i = 0; i < numStates; i++) {
        for (int j = 0; j < numAlphabet; j++) {
            printf("Transition for state %d with input symbol '%c': ", i + 1, alphabet[j]);
            scanf("%d", &transition[i][j]);
        }
    }

    // Input the string to simulate the FA
    char inputString[100];
    printf("Enter the input string to test: ");
    scanf("%s", inputString);

    // Simulate the finite automaton
    if (simulateFA(inputString)) {
        printf("The input string is accepted.\n");
    } else {
        printf("The input string is rejected.\n");
    }

    printf("The program is written by Shrey_22CE098.\n");

    return 0;
}
