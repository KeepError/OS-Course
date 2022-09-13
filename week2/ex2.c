#include <stdio.h>
#include <string.h>

int main(void) {
    char text[256] = {'\n'};
    char c;
    c = getchar();
    while (c != '.' && c != '\n') {
        strncat(text, &c, 1);
        c = getchar();
    }

    for (int i = strlen(text) - 1; i >= 0; i--)
    {
        putchar(text[i]);
    }
    
    return 0;
}