#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* count(char* string, char symbol) {
    int result = 0;
    for (int i = 0; i < strlen(string); i++) {
        if (tolower(string[i]) == tolower(symbol)) result += 1;
    }

    static char buffer[256];
    sprintf(buffer, "%c:%d", symbol, result);
    return buffer;
}

char* countAll(char* string) {
    static char result[1024];
    for (int i = 0; i < strlen(string); i++) {
        if (i == 0) {
            sprintf(result, "%s", count(string, tolower(string[i])));
        } else {
            sprintf(result, "%s, %s", result, count(string, tolower(string[i])));
        }
    }
    return result;
}

int main(void) {
    char buffer[256];
    scanf("%s", buffer);
    printf("%s", countAll(buffer));
    return 0;
}