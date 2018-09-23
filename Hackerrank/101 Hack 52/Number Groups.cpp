#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

ll k ;

int main() {
	scanf("%lld" , &k) ;
	k = k * k * k ;
	printf("%lld\n" , k) ;

	return 0 ;
}