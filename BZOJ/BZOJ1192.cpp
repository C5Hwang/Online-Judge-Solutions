#include <stdio.h>
#include <stdlib.h>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

int n , cnt ;

int main() {
	scanf("%d" , &n) ;

	cnt = 0 ;
	for (int a = 1 ; n > 0 ; n -= a , a <<= 1 , ++cnt) ;

	printf("%d\n" , cnt) ;

	return 0 ;
}