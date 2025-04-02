%option noyywrap
%{
#include <stdio.h>
#include <string.h>

int has_upper = 0, has_lower = 0, has_digit = 0, has_symbol = 0, length = 0;
%}

DIGIT      [0-9]
LOWER      [a-z]
UPPER      [A-Z]
SYMBOL     [*;#$@]
OTHER      .

%%
{UPPER}    { has_upper = 1; length++; }
{LOWER}    { has_lower = 1; length++; }
{DIGIT}    { has_digit = 1; length++; }
{SYMBOL}   { has_symbol = 1; length++; }
{OTHER}    { length++; }
\n         { 
             if (length >= 9 && length <= 15 && has_upper && has_lower && has_digit && has_symbol) 
                 printf("Valid password\n"); 
             else 
                 printf("Invalid password\n"); 
             has_upper = has_lower = has_digit = has_symbol = length = 0;
         }
%%

int main() {
    yylex();
    return 0;
}
