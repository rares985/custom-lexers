%{
	#include "token_types.h"
%}

NUMBER [1-9]+[0-9]*
POINTER "*"|"[]"
IDENTIFIER [a-zA-Z]+
WHITESPACE [ \t\n]+
SIZE ("["{NUMBER}"]")
STRUCT "struct"{WHITESPACE}+{IDENTIFIER}{WHITESPACE}+"{"
TYPENAME "int"|"float"|"char"|"double"|"void"
ENDSTRUCT "};"

%%


{STRUCT}									return STRUCT;
{ENDSTRUCT}									return END_STRUCT;
{TYPENAME}									return TYPENAME;
{IDENTIFIER}								return IDENTIFIER;
{POINTER}+									return POINTER;
{SIZE}										return SIZE;
{WHITESPACE}								;
.											;

%%

int yywrap(void) {
	return 1;
}
