#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 4e5 + 10 , mod = (119 << 23) + 1 , G = 3 ;

int n , m , rev[MAX_N] , inv[MAX_N] , pw[MAX_N] , ipw[MAX_N] , f[MAX_N] , g[MAX_N] ;

int qpow(int a , int t) {
	int s = 1 , tmp = a ;
	for (; t ; t >>= 1 , tmp = (ll)tmp * tmp % mod)
		if (t & 1) s = (ll)s * tmp % mod ;

	return s ;
}

void fnt(int *f , int ty) {
	for (int i = 0 ; i < n ; ++i) if (i < rev[i]) std::swap(f[i] , f[rev[i]]) ;

	for (int L = 2 ; L <= n ; L <<= 1) {
		int hf = L >> 1 , phi = mod - 1 , gn ;
		if (ty > 0) gn = qpow(G , phi / L) ;
		else gn = qpow(G , phi - phi / L) ;

		for (int i = 0 ; i < n ; i += L) {
			int g = 1 ;
			for (int j = 0 ; j < hf ; ++j , g = (ll)g * gn % mod) {
				int tmp = (ll)f[i + j + hf] * g % mod ;

				f[i + j + hf] = (f[i + j] + mod - tmp) % mod ;
				(f[i + j] += tmp) %= mod ;
			}
		}
	}
}

int main() {
	scanf("%d" , &n) ;
	for (int i = 1 ; i <= n ; ++i) inv[i] = qpow(i , mod - 2) ;
	ipw[0] = pw[0] = 1 ;
	for (int i = 1 ; i <= n ; ++i) ipw[i] = (ll)ipw[i - 1] * inv[i] % mod ;
	for (int i = 1 ; i <= n ; ++i) pw[i] = (ll)pw[i - 1] * i % mod ;

	///

	f[0] = 1 ;
	for (int i = 1 ; i <= n ; ++i)
		if (i % 2) f[i] = mod - ipw[i] ;
		else f[i] = ipw[i] ;

	g[0] = 1 ; g[1] = n ? n + 1 : 0 ;
	for (int i = 2 ; i <= n ; ++i) {
		g[i] = qpow(i , n + 1) + mod - 1 ;
		g[i] = (ll)g[i] * inv[i - 1] % mod ;
		g[i] = (ll)g[i] * ipw[i] % mod ;
	}

	///

	m = n ; n = 1 ;
	int L = 0 ; for (; n <= (m << 1) ; n <<= 1 , ++L) ;
	for (int i = 1 ; i < n ; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1)) ;

	fnt(f , 1) ; fnt(g , 1) ;
	for (int i = 0 ; i < n ; ++i) f[i] = (ll)f[i] * g[i] % mod ;
	fnt(f , -1) ;

	int ny = qpow(n , mod - 2) , ans = 0 ;
	for (int i = 0 ; i <= m ; ++i) {
		f[i] = (ll)f[i] * ny % mod ;
		int tmp = (ll)qpow(2 , i) * pw[i] % mod ;

		(ans += (ll)tmp * f[i] % mod) %= mod ;
	}

	printf("%d\n" , ans) ;

	return 0 ;
}