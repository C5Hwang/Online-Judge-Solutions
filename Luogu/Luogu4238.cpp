#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 4e5 + 10 , mod = (119 << 23) + 1 , G = 3 ;

int n , m , f[MAX_N] , g[MAX_N] , h[MAX_N] , rev[MAX_N] ;

int qpow(int a , int t) {
	int s = 1 , tmp = a ;

	for (; t ; t >>= 1 , tmp = (ll)tmp * tmp % mod)
		if (t & 1) s = (ll)s * tmp % mod ;

	return s ;
}

void init(int x) {
	m = 1 ;
	int L = 0 ; for (; m <= x ; m <<= 1 , ++L) ;

	for (int i = 1 ; i < m ; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1)) ;
}

void fnt(int *f , int ty) {
	for (int i = 0 ; i < m ; ++i) if (i < rev[i]) std::swap(f[i] , f[rev[i]]) ;

	for (int L = 2 ; L <= m ; L <<= 1) {
		int hf = L >> 1 , phi = mod - 1 , gn ;
		if (ty > 0) gn = qpow(G , phi / L) ;
		else gn = qpow(G , phi - phi / L) ;

		for (int i = 0 ; i < m ; i += L) {
			int g = 1 ;
			for (int j = 0 ; j < hf ; ++j , g = (ll)g * gn % mod) {
				int tmp = (ll)f[i + j + hf] * g % mod ;

				f[i + j + hf] = (f[i + j] + mod - tmp) % mod ;
				(f[i + j] += tmp) %= mod ;
			}
		}
	}
}

void work(int x) {
	if (x == 1) {
		g[0] = qpow(f[0] , mod - 2) ;

		return ;
	}

	work(x >> 1) ; init((x << 1) - 1) ;
	for (int i = 0 ; i < x ; ++i) h[i] = f[i] ;
	for (int i = x ; i < m ; ++i) h[i] = 0 ;

	fnt(g , 1) ; fnt(h , 1) ;
	for (int i = 0 ; i < m ; ++i)
		g[i] = (ll)g[i] * (2 + mod - ((ll)g[i] * h[i] % mod)) % mod ;
	fnt(g , -1) ;

	int ny = qpow(m , mod - 2) ;
	for (int i = 0 ; i < x ; ++i) g[i] = (ll)g[i] * ny % mod ;
	for (int i = x ; i < m ; ++i) g[i] = 0 ;
}

int main() {
	scanf("%d" , &n) ; --n ;
	for (int i = 0 ; i <= n ; ++i) scanf("%d" , &f[i]) ;

	///

	init(n) ;
	work(m) ;

	for (int i = 0 ; i <= n ; ++i) printf("%d " , g[i]) ;
	printf("\n") ;

	return 0 ;
}