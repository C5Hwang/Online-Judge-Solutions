#include <stdio.h>
#include <stdlib.h>

const int MAX_N = 1000000 + 10 ;

int n ;
long long f[MAX_N] , g[MAX_N] ;

int main() {
	scanf("%d" , &n) ;
	for (int i = 1 ; i <= n ; ++i)
		for (int j = i ; j <= n ; j += i) g[j] -= (long long)i ;

	///
	
	f[1] = n + g[1] ;
	for (int i = 2 ; i <= n ; ++i) f[i] = f[i - 1] + g[i] + n ;
	for (int i = 1 ; i <= n ; ++i) printf("%lld " , f[i]) ;
	printf("\n") ;

	return 0 ;
}
