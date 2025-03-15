%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gpp_interpreter.tab.h" 

%}


%%
        /* Keywords */
and           { return KW_AND; }
or            { return KW_OR; }
not           { return KW_NOT; }
equal         { return KW_EQUAL; }
less          { return KW_LESS; }
nil           { return KW_NIL; }
list          { return KW_LIST; }
append        { return KW_APPEND; }
concat        { return KW_CONCAT; }
set           { return KW_SET; }
deffun        { return KW_DEFFUN; }
defvar        { return KW_DEFVAR; }
for           { return KW_FOR; }
while         { return KW_WHILE; }
if            { return KW_IF; }
exit          { return KW_EXIT; }
load          { return KW_LOAD; }
print         { return KW_DISP; }
true          { return KW_TRUE; }
false         { return KW_FALSE; }

        /* Operators */
[+]           { return OP_PLUS; }
[-]           { return OP_MINUS; }
[/]           { return OP_DIV; }
[*]           { return OP_MULT; }
[']           { return OP_LIST; }
[(]           { return OP_OP; }
[)]           { return OP_CP; }
[,]           { return OP_COMMA; }

        /* Literals */
[0-9]+f[0-9]+ {
    char* part1 = strtok(yytext, "f"); // Extract the part before 'f'
    char* part2 = strtok(NULL, "f");  // Extract the part after 'f'

    // Ensure that the second part has a maximum of 5 digits
    if (strlen(part2) > 5) {
        part2[5] = '\0'; // Truncate the string to 5 digits
    }

    // Combine the parts into a floating-point representation
    char combined[256];
    snprintf(combined, sizeof(combined), "%s.%s", part1, part2);

    yylval.value = atof(combined); // Convert to float
    return VALUEF;
}

        /* Identifier */
[a-zA-Z][a-zA-Z0-9_]* { strcpy(yylval.string, yytext);  return IDENTIFIER; }

[0-9]+[a-zA-Z]+ { printf("SYNTAX_ERROR: Invalid identifier '%s'\n", yytext); return 0; }

        /* Comment  */
[;]{2}.*        { /* Ignore comments */ }  // Valid comment

        /* IgnoreCase */
[ \t\r\n]+    { /* Skip whitespace */ }

        /* GeneralErrorHandling */
. { printf("SYNTAX_ERROR: '%s' cannot be tokenized\n", yytext); return 0; }

%%


int yywrap() {
    return 1;
}

