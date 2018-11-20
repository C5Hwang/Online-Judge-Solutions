#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 8e5 + 10 , mod = (119 << 23) + 1 , G = 3 ;

int n , k , m , ipw[MAX_N] , P[MAX_N] , f[MAX_N] , g[MAX_N] , rev[MAX_N] ;

int qpow(int x , int t) {
	if (!x) return 0 ;

	int s = 1 , tmp = x ;
	for (; t ; t >>= 1 , tmp = (ll)tmp * tmp % mod)
		if (t & 1) s = (ll)s * tmp % mod ;

	return s ;
}

void fnt(int *f , int ty) {
	for (int i = 0 ; i < m ; ++i) if (i < rev[i]) std::swap(f[i] , f[rev[i]]) ;

	for (int L = 2 ; L <= m ; L <<= 1) {
		int phi = mod - 1 , hf = L >> 1 , gn ;
		if (ty > 0) gn = qpow(G , phi / L) ;
		else gn = qpow(G , phi - phi / L) ;

		for (int i = 0 ; i < m ; i += L) {
			int g = 1 ;
			for (int j = 0 ; j < hf ; ++j , g = (ll)g * gn % mod) {
				int tmp = (ll)g * f[i + j + hf] % mod ;

				f[i + j + hf] = (f[i + j] + mod - tmp) % mod ;
				(f[i + j] += tmp) %= mod ;
			}
		}
	}
}

int main() {
	scanf("%d %d" , &n , &k) ;

	ipw[0] = 1 ;
	for (int i = 1 ; i <= k ; ++i) ipw[i] = (ll)ipw[i - 1] * qpow(i , mod - 2) % mod ;

	--n ; P[0] = 1 ;
	for (int i = 1 ; i <= k ; ++i) P[i] = (ll)P[i - 1] * (n - i + 1) % mod ;

	for (int i = 0 ; i <= k ; ++i) {
		f[i] = ipw[i] ; if (i % 2) f[i] = mod - f[i] ;
		g[i] = (ll)qpow(i , k) * ipw[i] % mod ;
	}

	///

	m = 1 ;	int L = 0 ;
	for (; m <= (k << 1) ; m <<= 1 , ++L) ;
	for (int i = 1 ; i < m ; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1)) ;

	fnt(f , 1) ; fnt(g , 1) ;
	for (int i = 0 ; i < m ; ++i) f[i] = (ll)f[i] * g[i] % mod ;
	fnt(f , -1) ;

	int ans = 0 , ny = qpow(m , mod - 2) ;
	for (int i = 0 ; i <= k ; ++i) {
		f[i] = (ll)f[i] * ny % mod ;

		int tmp = (ll)f[i] * qpow(2 , n - i) % mod ;
		(ans += (ll)tmp * P[i] % mod) %= mod ;
	}

	ans = (ll)ans * (n + 1) % mod ;
	ans = (ll)ans * qpow(2 , ( ((ll)n * (n - 1)) >> 1 ) % (mod - 1)) % mod ;

	printf("%d\n" , ans) ;

	return 0 ;
}