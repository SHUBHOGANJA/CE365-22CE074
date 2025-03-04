%{
#include <stdio.h>
int char_count = 0, word_count = 0, line_count = 0;
%}

%%
\n { line_count++; char_count++; }
[ \t]+ { char_count += yyleng; }
[^ \t\n]+ { word_count++; char_count += yyleng; }
%%

int main() {
    printf("Reading from textfile.txt\n");
    yyin = fopen("textfile.txt", "r");
    if (!yyin) {
        printf("Error opening file\n");
        return 1;
    }
    yylex();
    fclose(yyin);
    printf("Characters: %d\n", char_count);
    printf("Words: %d\n", word_count);
    printf("Lines: %d\n", line_count);
    return 0;
}

int yywrap() {
    return 1;
}