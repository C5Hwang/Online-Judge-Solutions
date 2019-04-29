#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int mod = (119 << 23) + 1 , G = 3 ;

ll n ;
int s , ny , gn , a[4] , sig[4] , g[4] ;

inline int qpow(int a , ll t) {
	int s = 1 , tmp = a ;
	for (; t ; t >>= 1 , tmp = (ll)tmp * tmp % mod)
		if (t & 1) s = (ll)s * tmp % mod ;

	return s ;
}

int main() {
	int T ; scanf("%d" , &T) ;

	ny = qpow(4 , mod - 2) ;
	gn = qpow(G , (mod - 1) >> 2) ;

	g[0] = 1 ;
	for (int i = 1 ; i < 4 ; ++i) g[i] = (ll)g[i - 1] * gn % mod ;

	///

	for (; T-- ;) {
		scanf("%lld %d %d %d %d %d" , &n , &s , &a[0] , &a[1] , &a[2] , &a[3]) ;

		int ans = 0 ;
		for (int i = 0 ; i < 4 ; ++i) sig[i] = qpow(((ll)s * g[i] + 1) % mod , n) ;
		for (int k = 0 ; k < 4 ; ++k) {
			int sum = 0 ;
			for (int p = 0 ; p < 4 ; ++p) {
				int ng = g[k * p % 4] ;
				(sum += (ll)ng * sig[p] % mod) %= mod ;
			}

			int xs = (4 - k) % 4 ;
			(ans += (ll)sum * a[xs] % mod) %= mod ;
		}

		ans = (ll)ans * ny % mod ;
		printf("%d\n" , ans) ;
	}

	return 0 ;
}