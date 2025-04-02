#include <stdio.h>
#include <string.h>
#define MAXLINE 100

char line[MAXLINE];
char longest[MAXLINE];

void copy(char from[], char to[]);
void myNamePrint();

int main()
{
    int len;
    int max = 0;
    
    while (fgets(line, MAXLINE, stdin) != NULL) {
        len = strlen(line);
        if (len > 0 && line[len-1] == '\n') {
            line[len-1] = '\0';
            len--;
        }
        
        if (len > max) {
            max = len;
            copy(line, longest);
        }
    }
    
    if (max > 0)
        printf("\n%s", longest);
        
    myNamePrint();
    return 0;
}