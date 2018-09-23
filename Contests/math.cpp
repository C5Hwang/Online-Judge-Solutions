#include <stdio.h>
#include <stdlib.h>

#define ll long long

ll a , b ;

int main() {
	freopen("math.in" , "r" , stdin) ;
	freopen("math.out" , "w" , stdout) ;
	
	scanf("%lld %lld" , &a , &b) ;
	printf("%lld\n" , a * b - a - b) ;
	
	fclose(stdin) ; fclose(stdout) ;
	
	return 0 ;
}
