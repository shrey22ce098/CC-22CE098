#include <stdio.h>
#include <string.h>

int validate_string(const char *str) {
    int length = strlen(str);

    // Ensure the string has at least two characters: "bb"
    if (length < 2) {
        return 0;  // Not valid if the string is too short
    }

    // Check if the last two characters are 'b'
    if (str[length - 1] != 'b' || str[length - 2] != 'b') {
        return 0;  // Invalid if the last two characters are not 'b'
    }

    // Check all characters before the last two must be 'a'
    for (int i = 0; i < length - 2; i++) {
        if (str[i] != 'a') {
            return 0;  // Invalid if any character before the last two is not 'a'
        }
    }

    return 1;  // Valid string
}

int main() {
    const char *test_str1 = "aaabb";   // Valid
    const char *test_str2 = "abb";     // Valid
    const char *test_str3 = "aabbb";  // Invalid
    const char *test_str4 = "ab";      // Invalid
    const char *test_str5 = "bbaa";    // Invalid

    printf("Test 1: %s\n", validate_string(test_str1) ? "Valid" : "Invalid");
    printf("Test 2: %s\n", validate_string(test_str2) ? "Valid" : "Invalid");
    printf("Test 3: %s\n", validate_string(test_str3) ? "Valid" : "Invalid");
    printf("Test 4: %s\n", validate_string(test_str4) ? "Valid" : "Invalid");
    printf("Test 5: %s\n", validate_string(test_str5) ? "Valid" : "Invalid");

    return 0;
}
