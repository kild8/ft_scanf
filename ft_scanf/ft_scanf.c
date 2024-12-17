#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>

int ft_scanf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    int count = 0;
    while (*format) {
        if (*format == ' ') {
            // Skip whitespace in the format string
            format++;
            continue;
        }
        if (*format == '%') {
            format++;
            if (*format == 'd') {
                int *int_ptr = va_arg(args, int *);
                int num = 0;
                int sign = 1;
                char c;
                // Skip whitespace
                while (isspace(c = fgetc(stdin))) {
                    // Do nothing, just skip
                }
                // Handle sign
                if (c == '-') {
                    sign = -1;
                    c = fgetc(stdin);
                } else if (c == '+') {
                    c = fgetc(stdin);
                }
                // Read digits
                int has_digits = 0; // Flag to check if we read any digits
                while (isdigit(c)) {
                    has_digits = 1;
                    num = num * 10 + (c - '0');
                    c = fgetc(stdin);
                }
                // Put back the last character read
                ungetc(c, stdin);
                if (has_digits) {
                    *int_ptr = sign * num;
                    count++;
                }
            } else if (*format == 'c') {
                char *char_ptr = va_arg(args, char *);
                char c;
                // Skip whitespace before reading a character
                while (isspace(c = fgetc(stdin))) {
                    // Do nothing, just skip
                }
                if (c != EOF) {
                    *char_ptr = c; // Read the character
                    count++;
                }
            } else if (*format == 's') {
                char *str_ptr = va_arg(args, char *);
                char c;
                int i = 0;
                // Skip whitespace
                while (isspace(c = fgetc(stdin))) {
                    // Do nothing, just skip
                }
                // Read characters until whitespace or EOF
                while (!isspace(c) && c != EOF && i < 255) { // Limit to 255 characters
                    str_ptr[i++] = c;
                    c = fgetc(stdin);
                }
                str_ptr[i] = '\0'; // Null-terminate the string
                // Put back the last character read if it's not EOF
                if (c != EOF) {
                    ungetc(c, stdin);
                }
                if (i > 0) {
                    count++;
                }
            }
        }
        format++;
    }
    va_end(args);
    return count; // Return the number of successfully read items
}

int main() {

    int num;
    char ch;
    char str[256];
	
    printf("Enter an integer, a character, and a string: ");
    int result = ft_scanf("%d %c %s", &num, &ch, str);
    printf("You entered: %d, %c, %s\n", num, ch, str);
    printf("Number of items scanned: %d\n", result);
    return 0;
}