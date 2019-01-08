#include <stdio.h>
#include <stdlib.h>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

int n ;

int main() {
	scanf("%d" , &n) ;
	if (n <= 3) printf("1\n") ;
	else printf("%d\n" , n - 2) ;

	return 0 ;
}