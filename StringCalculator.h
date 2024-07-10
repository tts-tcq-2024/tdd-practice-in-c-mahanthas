#ifndef STRINGCALCULATOR_H
#define STRINGCALCULATOR_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_INPUT_LENGTH 1024
#define DELIMITER_MAX_LENGTH 10

int add(const char* numbers) {
    if (numbers == NULL || *numbers == '\0') {
        return 0;
    }

    char delimiters[DELIMITER_MAX_LENGTH] = ",\n";
    char numStr[MAX_INPUT_LENGTH];
    strncpy(numStr, numbers, MAX_INPUT_LENGTH);

    // Handle custom delimiter
    if (numStr[0] == '/' && numStr[1] == '/') {
        char* newline_pos = strchr(numStr, '\n');
        if (newline_pos != NULL) {
            size_t delimiter_length = newline_pos - (numStr + 2);
            if (delimiter_length < DELIMITER_MAX_LENGTH) {
                strncpy(delimiters, numStr + 2, delimiter_length);
                delimiters[delimiter_length] = '\0';
            }
            memmove(numStr, newline_pos + 1, strlen(newline_pos));
        }
    }

    int sum = 0;
    char* token = strtok(numStr, delimiters);
    bool has_negative = false;
    char negative_numbers[MAX_INPUT_LENGTH] = "";

    while (token != NULL) {
        int number = atoi(token);

        if (number < 0) {
            has_negative = true;
            char buffer[20];
            snprintf(buffer, sizeof(buffer), "%d ", number);
            strncat(negative_numbers, buffer, sizeof(negative_numbers) - strlen(negative_numbers) - 1);
        } else if (number <= 1000) {
            sum += number;
        }

        token = strtok(NULL, delimiters);
    }

    if (has_negative) {
        fprintf(stderr, "Negatives not allowed: %s\n", negative_numbers);
        exit(EXIT_FAILURE);
    }

    return sum;
}

#endif // STRINGCALCULATOR_H
