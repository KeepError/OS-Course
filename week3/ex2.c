#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct Point
{
    double x;
    double y;
};

typedef struct Point Point;

double distance(Point a, Point b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

double area(Point a, Point b, Point c) {
    return fabs(a.x * b.y - b.x * a.y + b.x*c.y - c.x*b.y + c.x*a.y - a.x*c.y) / 2;
}


int main(void) {
    Point a; a.x = 2.5; a.y = 6;
    Point b; b.x = 1; b.y = 2.2;
    Point c; c.x = 10; c.y = 6;
    printf("Distance: %f\n", distance(a, b));
    printf("Area: %f\n", area(a, b, c));
    return EXIT_SUCCESS;
}