%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "gpp_interpreter.tab.h"

extern FILE* yyin;  // Input file for the lexer
extern FILE* yyout; // Output file for the lexer
extern int yyparse(); // Bison's parse function

void yyerror(const char *msg) {
    fprintf(yyout, "Error: %s\n", msg);
}

void error(const char* msg) {
    fprintf(yyout, "Error: %s\n", msg);
}


// Struct for identifiers
typedef struct Identifier {
    char name[20];
    float values[20];  // Array to hold list elements (up to 20 values)
    int list_size;     // Number of elements in the list
} Identifier;

// Initialize an instance of Identifier with list_size = 0
Identifier identifierTable[200] = { { .list_size = 0 } }; // All identifiers initialized with list_size = 0
int identifier_count = 0;

// Function to find an identifier by name
int find_identifier(const char* name) {
    for (int i = 0; i < identifier_count; i++) {
        if (strcmp(identifierTable[i].name, name) == 0) {
            return i; // Found, return the index
        }
    }
    return -1; // Not found
}

void set_identifier(const char* name, float value, int is_list) {
    int index = find_identifier(name);
    if (index != -1) {
        if (is_list) {
            // If it is a list, append the value to the list
            if (identifierTable[index].list_size < 20) {
                identifierTable[index].values[identifierTable[index].list_size++] = value;
            } else {
                error("List size overflow");
            }
        } else {
            // If it's a single value, just set the first index
            identifierTable[index].values[0] = value;
        }
    } else if (identifier_count < 100) {
        // Add new identifier
        strncpy(identifierTable[identifier_count].name, name, sizeof(identifierTable[identifier_count].name) - 1);
        if (is_list) {
            // Initialize as a list
            identifierTable[identifier_count].values[0] = value;
            identifierTable[identifier_count].list_size = 1; // One element in the list
        } else {
            // Set a single value
            identifierTable[identifier_count].values[0] = value;
            identifierTable[identifier_count].list_size = 0;
        }
        identifier_count++;
    } else {
        error("Identifier table overflow");
    }
}

// Function to get the value of an identifier (handles single values and lists)
float get_identifier_value(const char* name) {
    int index = find_identifier(name);
    if (index != -1) {
        return identifierTable[index].values[0]; // Return first value for single-valued identifiers
    } else {
        error("Undefined identifier");
        return -1; // Return a default value
    }
}

// Function to concatenate two lists
void concat_lists(int idx1, int idx2) {
    if (identifierTable[idx1].list_size + identifierTable[idx2].list_size <= 20) {
        for (int i = 0; i < identifierTable[idx2].list_size; i++) {
            identifierTable[idx1].values[identifierTable[idx1].list_size++] = identifierTable[idx2].values[i];
        }
    } else {
        error("Concatenation exceeds list size limit");
    }
}

// Function to append a value to a list
void append_to_list(int idx, float value) {
    if (identifierTable[idx].list_size < 20) {
        identifierTable[idx].values[identifierTable[idx].list_size++] = value;
    } else {
        error("List size overflow");
    }
}

// Function to create a list from given values
void create_list(int idx, float values[], int count) {
    if (count <= 20) {
        for (int i = 0; i < count; i++) {
            identifierTable[idx].values[i] = values[i];
        }
        identifierTable[idx].list_size = count;
    } else {
        error("List size exceeds maximum size");
    }
}

int yylex();
int isList = 0;

%}

%union {
    float value;
    char string[20];
    int index;
}

%token <value> VALUEF
%token <string> IDENTIFIER
%token KW_AND KW_OR KW_NOT KW_EQUAL KW_LESS KW_NIL
%token KW_LIST KW_APPEND KW_CONCAT KW_SET KW_DEFFUN KW_DEFVAR
%token KW_FOR KW_WHILE KW_IF KW_EXIT KW_LOAD KW_DISP KW_TRUE KW_FALSE
%token OP_PLUS OP_MINUS OP_DIV OP_MULT OP_LIST OP_OP OP_CP OP_COMMA

%start START

%type <value> INPUT
%type <value> EXPI
%type <value> EXPILIST
%type <value> EXPB
%type <index> EXPLIST
%type <index> VALUES
%type <string> FDEF
%type <value> STATEMENT

%%

START
    : START INPUT
    | INPUT
    | START FDEF
    | START OP_OP KW_EXIT OP_CP {fprintf(yyout, "Exiting...\n"); exit(0); }
    ;

INPUT
    : EXPI { 
        if(isList == 0){
            char buffer[50];
            snprintf(buffer, sizeof(buffer), "%.5f", $$);  // Convert float to string with 5 digits precision
            for (int i = 0; buffer[i] != '\0'; i++) {
                if (buffer[i] == '.') {
                    buffer[i] = 'f';  // Replace '.' with 'f'
                }
            }
            fprintf(yyout, "Result: %s\n", buffer); 
        }else{
            int idx = $1;
            fprintf(yyout, "Result: (");
            for (int i = 0; i < identifierTable[idx].list_size; i++) {
                char buffer[50];
                snprintf(buffer, sizeof(buffer), "%.5f", identifierTable[idx].values[i]);
                for (int j = 0; buffer[j] != '\0'; j++) {
                    if (buffer[j] == '.') {
                        buffer[j] = 'f';  // Replace '.' with 'f'
                    }
                }
                fprintf(yyout, "%s ", buffer);
            }
            fprintf(yyout, ")\n");
            isList = 0;
        }
    }
    | EXPB { 
        if ($1 == 1.0f) 
            fprintf(yyout, "Result: TRUE\n"); 
        else 
            fprintf(yyout, "Result: False\n"); 
    } 
    | EXPLIST {
        int idx = $1;
        fprintf(yyout, "Result: (");
        for (int i = 0; i < identifierTable[idx].list_size; i++) {
            char buffer[50];
            snprintf(buffer, sizeof(buffer), "%.5f", identifierTable[idx].values[i]);
            for (int j = 0; buffer[j] != '\0'; j++) {
                if (buffer[j] == '.') {
                    buffer[j] = 'f';  // Replace '.' with 'f'
                }
            }
            fprintf(yyout, "%s ", buffer);
        }
        fprintf(yyout, ")\n");
    }
    ;


EXPI
    : OP_OP OP_PLUS EXPI EXPI OP_CP { $$ = $3 + $4; }
    | OP_OP OP_MINUS EXPI EXPI OP_CP { $$ = $3 - $4; }
    | OP_OP OP_MULT EXPI EXPI OP_CP { $$ = $3 * $4; }
    | OP_OP OP_DIV EXPI EXPI OP_CP {
        if ($4 == 0) {
            error("Division by zero!");
            $$ = -1;
        } else {
            $$ = $3 / $4;
        }
    }
    | IDENTIFIER { $$ = get_identifier_value($1); }
    | VALUEF { $$ = $1; }
    | OP_OP KW_DEFVAR IDENTIFIER EXPI OP_CP { set_identifier($3, $4, 0); $$ = $4; }
    | OP_OP KW_DEFVAR IDENTIFIER EXPLIST OP_CP { set_identifier($3, $4, 0); $$ = $4; isList = 1; }
    | OP_OP KW_SET IDENTIFIER EXPI OP_CP { set_identifier($3, $4, 0); $$ = $4; }
    | OP_OP KW_DISP EXPI OP_CP { $$ = $3; }
    | STATEMENT { $$ = $1; }
    ;

EXPB
    : OP_OP KW_AND EXPB EXPB OP_CP    { $$ = $3 && $4; }
    | OP_OP KW_OR EXPB EXPB OP_CP     { $$ = $3 || $4; }
    | OP_OP KW_NOT EXPB OP_CP         { $$ = ($3 == 0) ? 1.0f : 0.0f; } 
    | OP_OP KW_EQUAL EXPB EXPB OP_CP  { if ($3 == $4) $$ = 1.0f; else $$ = 0.0f; }  
    | OP_OP KW_LESS EXPB EXPB OP_CP   { if ($3 < $4) $$ = 1.0f; else $$ = 0.0f; }
    | OP_OP KW_EQUAL EXPI EXPI OP_CP  { if ($3 == $4) $$ = 1.0f; else $$ = 0.0f; }  
    | OP_OP KW_LESS EXPI EXPI OP_CP   { if ($3 < $4) $$ = 1.0f; else $$ = 0.0f; }
    | KW_TRUE { $$ = 1.0f; }
    | KW_FALSE { $$ = 0.0f; }
    | KW_NIL { $$ = 0.0f; }
    | VALUEF { $$ = ($1 != 0.0f) ? 1.0f : 0.0f; }  // Convert VALUEF to boolean (non-zero = true, zero = false)
    | IDENTIFIER { $$ = get_identifier_value($1) != 0.0f ? 1.0f : 0.0f; }  // Convert identifier value to boolean
    ;

EXPLIST
    : OP_OP KW_CONCAT EXPLIST EXPLIST OP_CP {
        int idx1 = $3;
        int idx2 = $4;
        if (idx1 < 0 || idx1 >= identifier_count || idx2 < 0 || idx2 >= identifier_count) {
            error("Invalid list index in CONCAT operation");
            $$ = -1; // Set $$ to an invalid value
        }
        concat_lists(idx1, idx2);  // Concatenate the lists
        $$ = idx1;  // Propagate the index of the resulting list
      }
    | OP_OP KW_APPEND EXPI EXPLIST OP_CP {
        int idx = $4;
        append_to_list(idx, $3);  // Append a single value to the list
        $$ = idx;  // Propagate the index of the updated list
      }
    | OP_OP KW_LIST VALUES OP_CP {
        $$ = $3;
    }
    | OP_LIST OP_OP VALUES OP_CP {
        $$ = $3;
    }
    ;

VALUES
    : VALUES OP_COMMA VALUEF {
        $$ = $1;
        append_to_list($$, $3);
    }
    | VALUEF {
        $$ = identifier_count;
        identifier_count++;
        float value = $1;
        create_list($$, &value, 1);  // Create a list with a single value
    }
    ;

STATEMENT
    : OP_OP KW_IF EXPB EXPILIST OP_CP {
        if ($3 == 1.0f) { // Condition evaluates to true
            $$ = $4; // Execute the block
        }
    }
    | OP_OP KW_IF EXPB EXPILIST EXPILIST OP_CP {
        if ($3 == 1.0f) {
            $$ = $4; // Execute the first block
        } else {
            $$ = $5; // Execute the second block
        }
    }
    ;

EXPILIST
    : EXPI { 
        $$ = $1; 
    }
    | EXPILIST EXPI { 
        $$ = $2; 
    }
    ;

FDEF
    : OP_OP KW_DEFFUN IDENTIFIER EXPILIST OP_CP {
        fprintf(yyout, "Result: %s\n", $3);
    }
    ;

%%


int main() {
    yyin = fopen("input.txt", "r");  // Open the input file
    yyout = fopen("output.txt", "w");  // Open the output file for writing
    if (yyin == NULL || yyout == NULL) {
        perror("Error opening files");
        exit(1);
    }
    yyparse();  // Start parsing

    fclose(yyin);
    fclose(yyout);
    return 0;
}

