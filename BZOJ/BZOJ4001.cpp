#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

ll n ;

int main() {
	scanf("%lld" , &n) ;
	printf("%0.9lf\n" , n * (n + 1) * 1.0 / ((n << 2) - 2)) ;

	return 0 ;
}