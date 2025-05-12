# Compiler Construction Assignment 2 - Solutions

## Q1: Recursive Descent Calculator

A simple calculator implemented using recursive descent parsing technique that supports integer arithmetic with '+' and '*' operators, as well as parentheses.

```c
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
```

## Q2: Counting 'a's in a String

An interpreter implemented using LEX and YACC that counts the number of 'a's in an input string according to the grammar: `S → a S | b`

### LEX file (count_a.l)

```lex
%{
#include "y.tab.h"
%}

%%
a       { return A; }
b       { return B; }
\n      { return 0; }
.       { return yytext[0]; }
%%

int yywrap() {
    return 1;
}
```

### YACC file (count_a.y)

```yacc
%{
#include <stdio.h>
int count = 0;
void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
extern int yylex(void); // Declare yylex to avoid implicit declaration
%}

%token A B

%%
start: S { printf("Number of 'a's: %d\n", count); }
     ;
S: A S { count++; }
 | B
 ;
%%

int main() {
    printf("Enter string (e.g., aaab): ");
    yyparse();
    return 0;
}
```

## Q3: Simple Calculator with LEX and YACC

A small calculator implemented using LEX and YACC that can add and subtract numbers.

### LEX file (calc.l)

```lex
%{
#include "y.tab.h"
#include <stdlib.h>
%}

%%
[0-9]+      { yylval = atoi(yytext); return NUMBER; }
"+"         { return PLUS; }
"-"         { return MINUS; }
\n          { return 0; }
[ \t]       ; /* Ignore whitespace */
.           { return yytext[0]; }
%%

int yywrap() {
    return 1;
}
```

### YACC file (calc.y)

```yacc
%{
#include <stdio.h>
void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
extern int yylex(void); // Declare yylex to avoid implicit declaration
%}

%token NUMBER PLUS MINUS
%left PLUS MINUS

%%
start: E { printf("Result: %d\n", $1); }
     ;
E: E PLUS E  { $$ = $1 + $3; }
 | E MINUS E { $$ = $1 - $3; }
 | NUMBER    { $$ = $1; }
 ;
%%

int main() {
    printf("Enter expression (e.g., 5+3-2): ");
    yyparse();
    return 0;
}
```

## How to Compile and Run

### Q1: Recursive Descent Calculator
```bash
cd Q1
gcc -o calculator calculator.c -Wall
./calculator
```

### Q2: Counting 'a's in a String
```bash
cd Q2
lex count_a.l
yacc -d count_a.y
gcc -o count_a lex.yy.c y.tab.c -ll
./count_a
```

### Q3: Simple Calculator with LEX and YACC
```bash
cd Q3
lex calc.l
yacc -d calc.y
gcc -o calc lex.yy.c y.tab.c -ll
./calc
``` 