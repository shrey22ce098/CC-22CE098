#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Define constants
#define MAX_TOKEN_SIZE 100
#define MAX_SYMBOL_TABLE_SIZE 100

// Define token categories
typedef enum {
    KEYWORD,
    IDENTIFIER,
    CONSTANT,
    STRING,
    PUNCTUATION,
    OPERATOR,
    ERROR
} TokenType;

// Structure to hold tokens
typedef struct {
    char lexeme[MAX_TOKEN_SIZE];
    TokenType type;
} Token;

// Symbol table to store identifiers
char symbolTable[MAX_SYMBOL_TABLE_SIZE][MAX_TOKEN_SIZE];
int symbolTableCount = 0;

// List of C keywords
const char *keywords[] = {
    "int", "char", "return", "void", "struct", "long", "float", "scanf", "printf", "if", "else", "for", "while", "do"
};
const int keywordCount = 14;

// Punctuation characters
const char punctuation[] = ";,(){}";

// Operators
const char *operators[] = {"+", "-", "", "/", "=", "==", "!=", "<", ">", "<=", ">="};
const int operatorCount = 11;

// Function prototypes
int isKeyword(const char *word);
int isOperator(const char *word);
int isPunctuation(char ch);
int isIdentifier(const char *word);
int isConstant(const char *word);
void addToSymbolTable(const char *identifier);
void tokenizeLine(const char *line, Token tokens[], int *tokenCount, int *errorCount);
void printTokens(Token tokens[], int tokenCount);
void printSymbolTable();
void interactiveInput();

int main() {
    printf("Enter your C code line by line. Type 'END' to finish.\n");

    Token tokens[1000];
    int tokenCount = 0, errorCount = 0;

    interactiveInput(tokens, &tokenCount, &errorCount);

    printf("\nTOKENS\n");
    printTokens(tokens, tokenCount);

    printf("\nSYMBOL TABLE\n");
    printSymbolTable();

    printf("\nLEXICAL ERRORS\n");
    printf("Total Errors: %d\n", errorCount);

    return 0;
}

// Check if a word is a keyword
int isKeyword(const char *word) {
    for (int i = 0; i < keywordCount; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Check if a word is an operator
int isOperator(const char *word) {
    for (int i = 0; i < operatorCount; i++) {
        if (strcmp(word, operators[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Check if a character is punctuation
int isPunctuation(char ch) {
    for (int i = 0; i < strlen(punctuation); i++) {
        if (ch == punctuation[i]) {
            return 1;
        }
    }
    return 0;
}

// Check if a word is a valid identifier
int isIdentifier(const char *word) {
    if (!isalpha(word[0]) && word[0] != '_') {
        return 0;
    }
    for (int i = 1; i < strlen(word); i++) {
        if (!isalnum(word[i]) && word[i] != '_') {
            return 0;
        }
    }
    return 1;
}

// Check if a word is a constant
int isConstant(const char *word) {
    for (int i = 0; i < strlen(word); i++) {
        if (!isdigit(word[i])) {
            return 0;
        }
    }
    return 1;
}

// Add an identifier to the symbol table
void addToSymbolTable(const char *identifier) {
    for (int i = 0; i < symbolTableCount; i++) {
        if (strcmp(symbolTable[i], identifier) == 0) {
            return; // Already in the table
        }
    }
    strcpy(symbolTable[symbolTableCount++], identifier);
}

// Tokenize a line of code
void tokenizeLine(const char *line, Token tokens[], int *tokenCount, int *errorCount) {
    char buffer[MAX_TOKEN_SIZE];
    int bufferIndex = 0;

    for (int i = 0; line[i] != '\0'; i++) {
        char ch = line[i];

        if (isspace(ch)) {
            // Process buffer if it contains a token
            if (bufferIndex > 0) {
                buffer[bufferIndex] = '\0';
                if (isKeyword(buffer)) {
                    strcpy(tokens[*tokenCount].lexeme, buffer);
                    tokens[*tokenCount].type = KEYWORD;
                } else if (isOperator(buffer)) {
                    strcpy(tokens[*tokenCount].lexeme, buffer);
                    tokens[*tokenCount].type = OPERATOR;
                } else if (isIdentifier(buffer)) {
                    strcpy(tokens[*tokenCount].lexeme, buffer);
                    tokens[*tokenCount].type = IDENTIFIER;
                    addToSymbolTable(buffer);
                } else if (isConstant(buffer)) {
                    strcpy(tokens[*tokenCount].lexeme, buffer);
                    tokens[*tokenCount].type = CONSTANT;
                } else {
                    strcpy(tokens[*tokenCount].lexeme, buffer);
                    tokens[*tokenCount].type = ERROR;
                    (*errorCount)++;
                }
                (*tokenCount)++;
                bufferIndex = 0;
            }
        } else if (isPunctuation(ch)) {
            // Handle punctuation
            if (bufferIndex > 0) {
                buffer[bufferIndex] = '\0';
                strcpy(tokens[*tokenCount].lexeme, buffer);
                tokens[*tokenCount].type = isIdentifier(buffer) ? IDENTIFIER : ERROR;
                if (tokens[*tokenCount].type == IDENTIFIER) {
                    addToSymbolTable(buffer);
                }
                (*tokenCount)++;
                bufferIndex = 0;
            }
            tokens[*tokenCount].lexeme[0] = ch;
            tokens[*tokenCount].lexeme[1] = '\0';
            tokens[*tokenCount].type = PUNCTUATION;
            (*tokenCount)++;
        } else {
            // Add character to buffer
            buffer[bufferIndex++] = ch;
        }
    }
}

// Print tokens
void printTokens(Token tokens[], int tokenCount) {
    for (int i = 0; i < tokenCount; i++) {
        printf("%s: %s\n",
            tokens[i].type == KEYWORD ? "Keyword" :
            tokens[i].type == IDENTIFIER ? "Identifier" :
            tokens[i].type == CONSTANT ? "Constant" :
            tokens[i].type == STRING ? "String" :
            tokens[i].type == PUNCTUATION ? "Punctuation" :
            tokens[i].type == OPERATOR ? "Operator" : "Error",
            tokens[i].lexeme);
    }
}

// Print symbol table
void printSymbolTable() {
    for (int i = 0; i < symbolTableCount; i++) {
        printf("%d) %s\n", i + 1, symbolTable[i]);
    }
}

// Interactive input function
void interactiveInput(Token tokens[], int *tokenCount, int *errorCount) {
    char line[1000];
    while (1) {
        printf("> ");
        fgets(line, sizeof(line), stdin);
        if (strcmp(line, "END\n") == 0) {
            break;
        }
        tokenizeLine(line, tokens, tokenCount, errorCount);
    }
}
