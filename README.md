# Compiler Construction Assignment 2

This assignment contains three questions related to parsing and grammar implementation.

## Q1: Recursive Descent Calculator

A simple calculator implemented using recursive descent parsing technique that supports integer arithmetic with '+' and '*' operators, as well as parentheses.

### How to compile and run:

```bash
cd Q1
gcc -o calculator calculator.c -Wall
./calculator
```

### Example usage:
```
Enter expression (e.g., 3+4*2): 3+4*2
Result: 11
```

## Q2: Counting 'a's in a String

An interpreter implemented using LEX and YACC that counts the number of 'a's in an input string according to the grammar:
```
S → a S | b
```

### How to compile and run:

```bash
cd Q2
lex count_a.l
yacc -d count_a.y
gcc -o count_a lex.yy.c y.tab.c -ly -ll
./count_a
```

### Example usage:
```
Enter string (e.g., aaab): aaab
Number of 'a's: 3
```

## Q3: Simple Calculator with LEX and YACC

A small calculator implemented using LEX and YACC that can add and subtract numbers.

### How to compile and run:

```bash
cd Q3
lex calc.l
yacc -d calc.y
gcc -o calc lex.yy.c y.tab.c -ly -ll
./calc
```

### Example usage:
```
Enter expression (e.g., 5+3-2): 5+3-2
Result: 6
``` 