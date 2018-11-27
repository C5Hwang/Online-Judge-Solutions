#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 6e5 + 10 , mod = (479 << 21) + 1 , G = 3 ;

int ipw[MAX_N] , mp[MAX_N] ;
int n , n1 , m , rev[MAX_N] , f[MAX_N] , g[MAX_N] , h[MAX_N] , t1[MAX_N] , t2[MAX_N] , inv[MAX_N] ;

int qpow(int x , int t) {
	int s = 1 , tmp = x ;
	for (; t ; t >>= 1 , tmp = (ll)tmp * tmp % mod)
		if (t & 1) s = (ll)s * tmp % mod ;

	return s ;
}

void init(int len) {
	m = 1 ;
	int L = 0 ; for (; m <= len ; m <<= 1 , ++L) ;

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
		inv[0] = qpow(g[0] , mod - 2) ;
		return ;
	}

	work(x >> 1) ; init((x << 1) - 1) ;

	for (int i = 0 ; i < x ; ++i) t1[i] = g[i] ;
	for (int i = 0 ; i < x ; ++i) t2[i] = inv[i] ;
	for (int i = x ; i < m ; ++i) t1[i] = t2[i] = 0 ;

	fnt(t1 , 1) ; fnt(t2 , 1) ;
	for (int i = 0 ; i < m ; ++i)
		t1[i] = (ll)t2[i] * (2 + mod - ((ll)t1[i] * t2[i] % mod)) % mod ;
	fnt(t1 , -1) ;

	int ny = qpow(m , mod - 2) ;
	for (int i = 0 ; i < x ; ++i) inv[i] = (ll)t1[i] * ny % mod ;
}

int main() {
	scanf("%d" , &n) ; --n ;

	ipw[0] = mp[0] = 1 ;
	for (int i = 1 ; i <= n + 1 ; ++i) {
		ipw[i] = (ll)ipw[i - 1] * qpow(i , mod - 2) % mod ;
		mp[i] = qpow(2 , (((ll)i * (i - 1)) >> 1) % (mod - 1)) ;
	}
	for (int i = 0 ; i <= n ; ++i) {
		g[i] = (ll)mp[i] * ipw[i] % mod ;
		h[i] = (ll)mp[i + 1] * ipw[i] % mod ;
	}

	///

	init(n) ;
	int n1 = m ;

	work(n1) ;
	init(n1 << 1) ;

	fnt(inv , 1) ; fnt(h , 1) ;
	for (int i = 0 ; i < m ; ++i) h[i] = (ll)h[i] * inv[i] % mod ;
	fnt(h , -1) ;
	
	int ny = qpow(m , mod - 2) , ans = (ll)h[n] * ny % mod ;
	for (int i = 2 ; i <= n ; ++i) ans = (ll)ans * i % mod ;

	printf("%d\n" , ans) ;

	return 0 ;
}