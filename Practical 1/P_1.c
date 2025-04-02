#include<stdio.h>
#include<string.h>

int main(){
    char buf[1024];
    int i=0;

    printf("Enter a string: ");
    scanf("%s", buf);

    while (buf[i]=='a')
    {
        i++;
    }
    if (buf[i]=='b' && buf[i+1]=='b' && buf[i+2]=='\0'){
        printf("Valid String\n");
    }
    else{
        printf("Invalid String\n");
    }
    return 0;
}
