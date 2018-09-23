#include <stdio.h>
#include <stdlib.h>

int n = 1e5 , L = 10 ;

int main() {
	srand(2333) ;

	printf("%d %d\n" , n , L) ;
	for (int i = 0 ; i < n ; ++i) putchar('a' + rand() % 26) ;
	printf("\n") ;

	return 0 ;
}