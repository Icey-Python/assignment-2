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
