#include <stdio.h>
#include <string.h>
#include <math.h>

long long convert_to_decimal(long long number, int source_ns) {
    long long decimal = 0;
    int base = 1;
    int remainder = 0;

    while (number > 0) { 
        remainder = number % 10;
        decimal = decimal + remainder * base;
        base = base * source_ns;
        number = number / 10;
    }

    return decimal;
}

long long convert_from_decimal(long long number, int target_ns) {
    long long result = 0;
    for (int i = 0; number > 0; i++) {
        result = result + (number % target_ns) * pow((double) 10, (double) i);
        number = number / target_ns;
    }
    return result;
}

long long convert(long long number, int source_ns, int target_ns) {
    long long decimal = convert_to_decimal(number, source_ns);
    long long result = convert_from_decimal(decimal, target_ns);
    return result;
}

int check_input(char num_str[256], int source_ns, int target_ns) {
    if (source_ns < 2 || source_ns > 10 || target_ns < 2 || target_ns > 10) return 0;

    char source_ns_str = (source_ns - 1) + '0';
    for (int i = 0; i < strlen(num_str); i++) {
        if (num_str[i] < '0' || num_str[i] > source_ns_str) return 0;
    }

    return 1;
}

int main(void) {
    long long number;
    char num_str[256];
    int source_ns;
    int target_ns;
    scanf("%s %d %d", num_str, &source_ns, &target_ns);
    if (check_input(num_str, source_ns, target_ns) == 0) {
        printf("cannot convert!");
        return 0;
    }


    sscanf(num_str, "%ld", &number);
    printf("%d", convert(number, source_ns, target_ns));
    return 0;
}