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
