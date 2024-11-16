%{
// prologue
#define YYSTYPE double /* overwrite to double precision */
#include <stdio.h>
#include <ctype.h>
#include <math.h>

// prototypes
int yylex(void);
void yyerror(char *s);
void warning(char* s, char* t);
%}

%token NUMBER
%left '+' '-'   /* left assoc. same precedence */
%left '*' '/' '%'   /* left assoc. higher precedence */
%left UNARYMINUS UNARYPLUS

%%
list:   /* empty */
        | list '\n'
        | list expr '\n' { printf("\t%.8g\n", $2); }
        ;
expr:     NUMBER    { $$ = $1; }
        | '-' expr %prec UNARYMINUS { $$ = -$2; }
        | '+' expr %prec UNARYPLUS { $$ = $2; }
        | expr '+' expr { $$ = $1 + $3; }
        | expr '-' expr { $$ = $1 - $3; }
        | expr '*' expr { $$ = $1 * $3; }
        | expr '/' expr { $$ = $1 / $3; }
        | expr '%' expr { $$ = fmod($1, $3); }
        | '(' expr ')' { $$ = $2; }
        ;
%%
/* end of grammar */

char* progname;
int lineno = 1;

int main(int argc, char* argv[]) {
    progname = argv[0];
    return yyparse();
}

int yylex(void) {
    int c;
    while ((c = getchar()) == ' ' || c == '\t')
            ;
    if (c == EOF)
            return 0;
    if (c == '.' || isdigit(c)) {
        ungetc(c, stdin);
        scanf("%lf", &yylval);
        return NUMBER;
    }
    if (c == '\n')
            lineno++;
    return c;
}

void warning(char* s, char* t) {
    fprintf(stderr, "%s: %s", progname, s);
    if (t)
            fprintf(stderr, " %s", t);
    fprintf(stderr, " near line %d\n", lineno);
}

void yyerror(char* s) {
    warning(s, (char*)0);
}
