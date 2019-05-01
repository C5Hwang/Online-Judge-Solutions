#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 3e6 + 10 ;

int n , mod , jc[MAX_N] , inv[MAX_N] ;

inline int qpow(int a , int t) {
	int s = 1 , tmp = a ;
	for (; t ; t >>= 1 , tmp = (ll)tmp * tmp % mod)
		if (t & 1) s = (ll)s * tmp % mod ;

	return s ;
}

int main() {
	scanf("%d %d" , &n , &mod) ;

	jc[0] = inv[0] = 1 ;
	for (int i = 1 ; i <= n ; ++i) jc[i] = (ll)jc[i - 1] * i % mod ;
	inv[n] = qpow(jc[n] , mod - 2) ;
	for (int i = n - 1 ; i ; --i) inv[i] = (ll)inv[i + 1] * (i + 1) % mod ;

	///

	for (int i = 1 ; i <= n ; ++i) printf("%d\n" , (ll)inv[i] * jc[i - 1] % mod) ;

	return 0 ;
}