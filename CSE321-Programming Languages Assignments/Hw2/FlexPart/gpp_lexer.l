%{
#include <stdio.h>

// Flag to indicate whether input is from a file or user input
int is_file_input = 0;
FILE *outfile;

// Declare the output_token function before using it
void output_token(const char *token);

%}


%%

        /* Special command to quit in interactive mode */
[(]quit[)]    {
                if (!is_file_input) {
                    output_token("QUIT_COMMAND. ");
                    return 0; // Stop processing and exit yylex()
                }
             }

        /* Keywords */
and           { output_token("KW_AND\n"); }
or            { output_token("KW_OR\n"); }
not           { output_token("KW_NOT\n"); }
equal         { output_token("KW_EQUAL\n"); }
less          { output_token("KW_LESS\n"); }
nil           { output_token("KW_NIL\n"); }
list          { output_token("KW_LIST\n"); }
append        { output_token("KW_APPEND\n"); }
concat        { output_token("KW_CONCAT\n"); }
set           { output_token("KW_SET\n"); }
deffun        { output_token("KW_DEFFUN\n"); }
for           { output_token("KW_FOR\n"); }
if            { output_token("KW_IF\n"); }
exit          { output_token("KW_EXIT\n"); }
load          { output_token("KW_LOAD\n"); }
print         { output_token("KW_DISP\n"); }
true          { output_token("KW_TRUE\n"); }
false         { output_token("KW_FALSE\n"); }

        /* Operators */
[+]           { output_token("OP_PLUS\n"); }
[-]           { output_token("OP_MINUS\n"); }
[/]           { output_token("OP_DIV\n"); }
[*]           { output_token("OP_MULT\n"); }
[(]           { output_token("OP_OP\n"); }
[)]           { output_token("OP_CP\n"); }
[,]           { output_token("OP_COMMA\n"); }

        /* Literals */
[0-9]+        { output_token("VALUEI\n"); }
[0-9]+f[0-9]+ { output_token("VALUEF\n"); }
[0-9]+f+[0-9]+ { output_token("VALUEF_ERROR: Multiple 'f' characters in floating point number.\n"); }

        /* Identifier */
[a-zA-Z][a-zA-Z0-9_]*    { output_token("IDENTIFIER\n"); }
[0-9]+[a-zA-Z]+          { output_token("IDENTIFIER_ERROR: Invalid identifier format, should start with a letter.\n"); }

        /* Comment  */
[;]{2}.*        { output_token("COMMENT\n"); }  // Valid comment

        /* IgnoreCase */
[ \t\r\n]+    { /* ignore whitespace, tab, and any newline format */ }
        
        /* GeneralErrorHandling */
.               { 
                  char error_msg[256];
                  snprintf(error_msg, sizeof(error_msg), "SYNTAX_ERROR: '%s' cannot be tokenized\n", yytext);
                  output_token(error_msg); 
                }

%%

void output_token(const char *token) {
    if(is_file_input){
        fprintf(outfile, "%s", token); // Write tokens to output file
    }else{
        printf("%s", token);          // Print tokens to terminal
    }
}

int yywrap() {
    return 1;
}

int main(int argc, char **argv) {
    if(argc == 1){
        // Interactive mode
        printf("Enter the string to be parsed (type '(quit)' to exit):\n");
        is_file_input = 0; // Set flag for user input
        while(1){
            if(yylex() == 0){
                break; // Exit when yylex() returns 0
            }
        }
        printf("Exiting interactive mode.\n");
    }else if(argc == 2) {
        // File input mode
        yyin = fopen(argv[1], "r");
        if(!yyin){
            fprintf(stderr, "Error: Could not open file %s\n", argv[1]);
            return 1;
        }
        outfile = fopen("output.txt", "w");
        if(!outfile){
            fprintf(stderr, "Error: Could not create output file\n");
            fclose(yyin);
            return 1;
        }
        is_file_input = 1; // Set flag for file input
        yylex();
        fclose(yyin);
        fclose(outfile);
    }else{
        printf("Too many arguments!\n");
        return 0;
    }
    return 0;
}

