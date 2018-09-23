#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int N = 1e6 , MAX_N = 1e6 + 10 , mod = 1e9 + 7 ;

int T , n , m , sum[MAX_N] , fac[MAX_N] , inv[MAX_N] ;

int qpow(int a , int t) {
	if (!t) return 1 ;

	int s = qpow(a , t >> 1) ;
	s = (ll)s * s % mod ; if (t & 1) s = (ll)s * a % mod ;

	return s ;
}

void init() {
	fac[0] = inv[0] = 1 ;
	for (int i = 1 ; i <= N ; ++i) {
		fac[i] = (ll)fac[i - 1] * i % mod ;
		inv[i] = (ll)inv[i - 1] * qpow(i , mod - 2) % mod ;
	}

	sum[0] = 1 ;
	for (int i = 1 , t = -1 ; i <= N ; ++i , t = -t)
		sum[i] = ((ll)sum[i - 1] + t * inv[i] + mod) % mod ;
}

int main() {
	init() ;

	scanf("%d" , &T) ;
	for (; T-- ;) {
		scanf("%d %d" , &n , &m) ;

		int ans = (((ll)fac[n] * inv[m]) % mod * sum[n - m]) % mod ;
		printf("%d\n" , ans) ;
	}

	return 0 ;
}