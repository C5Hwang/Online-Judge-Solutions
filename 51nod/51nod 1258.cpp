#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int N = 5e4 + 2 , MAX_N = 5e4 + 10 , mod = 1e9 + 7 ;

ll n ;
int k , jc[MAX_N] , inv[MAX_N] , y[MAX_N] , sl[MAX_N] , sr[MAX_N] ;

inline int qpow(int a , int t) {
	int s = 1 , tmp = a ;
	for (; t ; t >>= 1 , tmp = (ll)tmp * tmp % mod)
		if (t & 1) s = (ll)s * tmp % mod ;

	return s ;
}

void init() {
	jc[0] = 1 ;
	for (int i = 1 ; i <= N ; ++i) jc[i] = (ll)jc[i - 1] * i % mod ;
	inv[N] = qpow(jc[N] , mod - 2) ;
	for (int i = N - 1 ; i ; --i) inv[i] = (ll)inv[i + 1] * (i + 1) % mod ;
}

int calc(int x) {
	if (!x) return 1 ;

	int f = 1 ;
	if (x < 0) x = -x , f = x & 1 ? -1 : 1 ;

	return (mod + inv[x] * f) % mod ;
}

int getans() {
	if (n <= k + 2) return y[n] ;

	sl[0] = sr[k + 3] = 1 ;
	for (int i = 1 ; i <= k + 2 ; ++i) sl[i] = (n - i) % mod * sl[i - 1] % mod ;
	for (int i = k + 2 ; i ; --i) sr[i] = (n - i) % mod * sr[i + 1] % mod ;

	int res = 0 ;
	for (int i = 1 ; i <= k + 2 ; ++i) {
		int tmp = (ll)sl[i - 1] * sr[i + 1] % mod * y[i] % mod ;
		tmp = (ll)tmp * calc(i - 1) % mod * calc(i - k - 2) % mod ;

		(res += tmp) %= mod ;
	}

	return res ;
}

int main() {
	init() ;

	int T ; scanf("%d" , &T) ;
	for (; T-- ;) {
		scanf("%lld %d" , &n , &k) ;

		y[0] = 0 ;
		for (int i = 1 ; i <= k + 2 ; ++i) y[i] = (y[i - 1] + qpow(i , k)) % mod ;

		printf("%d\n" , getans()) ;
	}

	return 0 ;
}