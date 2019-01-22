#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 , MAX_M = 4e5 + 10 , mod = (119 << 23) + 1 , G = 3 ;

int n , Q , ans , fac[MAX_N] , inv[MAX_N] ;
int f[MAX_M] , g[MAX_M] , h[MAX_M] , t[MAX_M] , rev[MAX_M] ;

void init(int m) {
	n = 1 ; int L = 0 ;
	for (; n <= m ; n <<= 1 , ++L) ;

	for (int i = 1 ; i < n ; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1)) ;
}

int qpow(int a , int t) {
	int tmp = a , s = 1 ;
	for (; t ; t >>= 1 , tmp = (ll)tmp * tmp % mod)
		if (t & 1) s = (ll)s * tmp % mod ;

	return s ;
}

void fnt(int *f , int ty) {
	for (int i = 0 ; i < n ; ++i) if (i < rev[i]) std::swap(f[i] , f[rev[i]]) ;

	for (int L = 2 ; L <= n ; L <<= 1) {
		int gn , hf = L >> 1 , phi = mod - 1 ;
		if (ty > 0) gn = qpow(G , phi / L) ;
		else gn = qpow(G , phi - phi / L) ;

		for (int i = 0 ; i < n ; i += L) {
			int g = 1 ;
			for (int j = 0 ; j < hf ; ++j , g = (ll)g * gn % mod) {
				int tmp = (ll)f[i + j + hf] * g % mod ;

				f[i + j + hf] = (f[i + j] - tmp + mod) % mod ;
				(f[i + j] += tmp) %= mod ;
			}
		}
	}
}

void work(int m) {
	if (m == 1) {
		h[0] = 1 ;
		return ;
	}

	work(m >> 1) ; init((m << 1) - 3) ; 
	for (int i = 0 ; i < m ; ++i) t[i] = f[i] ;
	for (int i = m ; i < n ; ++i) t[i] = 0 ;
	for (int i = m >> 1 ; i < n ; ++i) h[i] = 0 ;

	fnt(t , 1) ; fnt(h , 1) ;
	for (int i = 0 ; i < n ; ++i) h[i] = (ll)h[i] * (2 + mod - (ll)t[i] * h[i] % mod) % mod ;
	fnt(h , -1) ;

	int ny = qpow(n , mod - 2) ;
	for (int i = 0 ; i < m ; ++i) h[i] = (ll)h[i] * ny % mod ;
	for (int i = m ; i < n ; ++i) h[i] = 0 ;
}

int getans(int k) {
	int b = Q % k , p , res ;
	if (b) p = Q / k + 1 ; else p = Q / k ;
	res = p & 1 ? mod - qpow(fac[Q] , Q) : qpow(fac[Q] , Q) ;
	
	f[0] = 1 ; g[0] = 0 ;
	for (int i = 1 ; i <= p ; ++i) f[i] = mod - inv[i * k] ;
	for (int i = 0 ; i < p ; ++i) g[i + 1] = inv[i * k + b] ;

	init(p) ;
	for (int i = p + 1 ; i < n ; ++i) f[i] = g[i] = 0 ;

	work(n) ;
	if (!b) return (ll)res * h[p] % mod ;

	init(p) ; fnt(h , 1) ; fnt(g , 1) ;
	for (int i = 0 ; i < n ; ++i) h[i] = (ll)h[i] * g[i] % mod ;
	fnt(h , -1) ;

	h[p] = (ll)h[p] * qpow(n , mod - 2) % mod ;
	return (ll)res * h[p] % mod ;
}

int main() {
	Q = 5e4 ; fac[0] = 1 ;
	for (int i = 1 ; i <= Q ; ++i) {
		fac[i] = (ll)fac[i - 1] * i % mod ;
		inv[i] = qpow(fac[i] , mod - 2) ; inv[i] = mod - qpow(inv[i] , Q) ;
	}

	for (int k = 1 ; k <= Q ; ++k)
		(ans += getans(k)) %= mod ;
	printf("%d\n" , ans) ;

	return 0 ;
}