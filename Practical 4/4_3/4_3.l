%option noyywrap
%{
#include <stdio.h>
int char_count = 0, word_count = 0, line_count = 0;
int in_word = 0;
%}

%%
.        { char_count++; }
\n       { char_count++; line_count++; in_word = 0; }
[ \t]+   { char_count++; in_word = 0; }
[A-Za-z0-9]+ { char_count += yyleng; if (!in_word) { word_count++; in_word = 1; } }
%%

int main() {
    yylex();
    printf("Characters : %d\n", char_count);
    printf("Words : %d\n", word_count);
    printf("Lines : %d\n", line_count);
    return 0;
}