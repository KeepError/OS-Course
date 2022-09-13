#include <limits.h>
#include <float.h>
#include <stdio.h>

int main(void) {
    int integer_value = INT_MAX;
    unsigned short int unsigned_short_integer_value = USHRT_MAX;
    signed long int signed_long_int_value = LONG_MAX;
    float float_value = FLT_MAX;
    double double_value = DBL_MAX;

    printf("Type: INTEGER\nSize:%d\nValue: %d\n\n", sizeof(integer_value), integer_value);
    printf("Type: UNSIGNED SHORT INTEGER\nSize: %d\nValue: %d\n\n", sizeof(unsigned_short_integer_value), unsigned_short_integer_value);
    printf("Type: SIGNED LONG INTEGER\nSize: %d\nValue: %ld\n\n", sizeof(signed_long_int_value), signed_long_int_value);
    printf("Type: FLOAT\nSize: %d\nValue: %f\n\n", sizeof(float_value), float_value);
    printf("Type: DOUBLE\nSize: %d\nValue: %f\n", sizeof(double_value), double_value);

    return 0;
}