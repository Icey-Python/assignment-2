#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

char *input;
int pos = 0;

// Function prototypes to resolve implicit declaration warnings
void error(void);
int expr(void);
int expr_prime(int left);
int term(void);
int term_prime(int left);
int factor(void);
int number(void);

void error() {
    printf("Syntax error at position %d\n", pos);
    exit(1);
}

int number() {
    int val = 0;
    if (!isdigit(input[pos])) error();
    while (isdigit(input[pos])) {
        val = val * 10 + (input[pos] - '0');
        pos++;
    }
    return val;
}

int factor() {
    int val;
    if (input[pos] == '(') {
        pos++;
        val = expr();
        if (input[pos] != ')') error();
        pos++;
    } else {
        val = number();
    }
    return val;
}

int term_prime(int left) {
    if (input[pos] == '*') {
        pos++;
        int right = factor();
        return term_prime(left * right);
    }
    return left;
}

int term() {
    int left = factor();
    return term_prime(left);
}

int expr_prime(int left) {
    if (input[pos] == '+') {
        pos++;
        int right = term();
        return expr_prime(left + right);
    }
    return left;
}

int expr() {
    int left = term();
    return expr_prime(left);
}

int main() {
    char buffer[100];
    printf("Enter expression (e.g., 3+4*2): ");
    fgets(buffer, 100, stdin);
    input = buffer;
    pos = 0;
    int result = expr();
    if (input[pos] != '\n' && input[pos] != '\0') error();
    printf("Result: %d\n", result);
    return 0;
}
