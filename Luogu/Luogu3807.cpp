#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 ;

int n , m , mod , jc[MAX_N] , inv[MAX_N] ;

int qpow(int a , int t) {
	int s = 1 , tmp = a ;
	for (; t ; t >>= 1 , tmp = (ll)tmp * tmp % mod)
		if (t & 1) s = (ll)s * tmp % mod ;

	return s ;
}

void init() {
	jc[0] = inv[0] = 1 ;
	for (int i = 1 ; i < mod ; ++i) jc[i] = (ll)jc[i - 1] * i % mod ;
	inv[mod - 1] = qpow(jc[mod - 1] , mod - 2) ;
	for (int i = mod - 2 ; i ; --i) inv[i] = (ll)inv[i + 1] * (i + 1) % mod ;
}

int C(int x , int y) {
	if (x < y) return 0 ;

	return (ll)jc[x] * inv[y] % mod * inv[x - y] % mod ;
}

int getC(int n , int m) {
	if (n < mod && m < mod) return C(n , m) ;
	return (ll)getC(n / mod , m / mod) * C(n % mod , m % mod) % mod ;
}

int main() {
	int T ; scanf("%d" , &T) ;
	for (; T-- ;) {
		scanf("%d %d %d" , &n , &m , &mod) ;

		init() ; n += m ;
		printf("%d\n" , getC(n , m)) ;
	}

	return 0 ;
}