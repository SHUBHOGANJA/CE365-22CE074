%{
#include <stdio.h>
#include <string.h>

int d=0; 
int l=0;
int lc=0; 
int uc=0;
int sc=0;
int ec=0;
%}

%%

[0-9]	{d++; l++;}
[a-z] 	{lc++; l++;}
[A-Z]	{uc++; l++;}
[*, ; # $ @] {sc++; l++;}
\n {if(d>0 && lc>0 && uc>0 && sc>0 && l>=9 && l<=15 && ec==0)
	{printf("valid");}
      else 
	{printf("invalid \n");}
	exit(0);
		}
. {ec++; printf("invalid\n"); exit(0);}


%%
int main()
{
printf("Enter Password : ");
yylex();
return 0;
}

int yywrap() {
return 1;
}

