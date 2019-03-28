#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e6 + 10 ;

int n , T ;
ll f[MAX_N] , res[MAX_N] ;

void init() {
	n = 1e6 ;

	for (int i = 1 ; i <= n ; ++i) f[i] = i ;
	for (int i = 2 ; i <= n ; ++i)
		if (f[i] == i) for (int j = i ; j <= n ; j += i) f[j] = f[j] / i * (i - 1) ;
	for (int i = 2 ; i <= n ; ++i) f[i] = ((ll)f[i] * i) >> 1 ;

	for (int i = 1 ; i <= n ; ++i)
		for (int j = i ; j <= n ; j += i) res[j] += f[i] ;
}

int main() {
	init() ;

	scanf("%d" , &T) ;
	for (; T-- ;) {
		scanf("%d" , &n) ;

		printf("%lld\n" , res[n] * n) ;
	}

	return 0 ;
}