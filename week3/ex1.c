#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int foo(int age){
	return 2022 - age;
}

int main(){
	const int x = 10;
	const int * q = &x;
	int * const p = malloc(sizeof(int) * 5);

	for (int i=0; i<5; i++) {
		*(p+i) = x;
		printf("%p\n", p+i);
	}

	for (int i=0; i<5; i++) {
		scanf("%d", p + i);
	}

	for (int i=0; i<5; i++) {
		*(p+i) = foo(*(p+i));
	}

	return EXIT_SUCCESS;
}