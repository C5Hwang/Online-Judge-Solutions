#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 4e5 + 10 , mod = (119 << 23) + 1 , G = 3 ;

int rev[MAX_N] , A[MAX_N] , B[MAX_N] ;
int n , m , f[MAX_N] , g[MAX_N] , h[MAX_N] , g1[MAX_N] ;

int qpow(int a , int t) {
	int s = 1 , tmp = a ;
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

void inverse(int n , int *f , int *f1) {
	if (n == 1) {
		f1[0] = qpow(f[0] , mod - 2) ;
		return ;
	}

	inverse(n >> 1 , f , f1) ;

	init((n << 1) - 1) ;
	for (int i = 0 ; i < n ; ++i) A[i] = f[i] ;
	for (int i = n ; i < m ; ++i) A[i] = 0 ;

	fnt(A , 1) ; fnt(f1 , 1) ;
	for (int i = 0 ; i < m ; ++i)
		f1[i] = (ll)f1[i] * (2 + mod - (ll)A[i] * f1[i] % mod) % mod ;
	fnt(f1 , -1) ;

	int ny = qpow(m , mod - 2) ;
	for (int i = 0 ; i < n ; ++i) f1[i] = (ll)f1[i] * ny % mod ;
	for (int i = n ; i < m ; ++i) f1[i] = 0 ;
}

void sqrt(int n , int *f , int *g) {
	if (n == 1) {
		g[0] = 1 ;
		return ;
	}

	sqrt(n >> 1 , f , g) ;

	for (int i = 0 ; i < n ; ++i) B[i] = 0 , h[i] = (g[i] << 1) % mod ;
	inverse(n , h , B) ;

	init((n << 1) - 1) ;
	for (int i = 0 ; i < n ; ++i) A[i] = f[i] ;
	for (int i = n ; i < m ; ++i) A[i] = B[i] = 0 ;

	fnt(A , 1) ; fnt(B , 1) ; fnt(g , 1) ;
	for (int i = 0 ; i < m ; ++i)
		g[i] = ((ll)g[i] * g[i] % mod + A[i]) * B[i] % mod ;
	fnt(g , -1) ;

	int ny = qpow(m , mod - 2) ;
	for (int i = 0 ; i < n ; ++i) g[i] = (ll)g[i] * ny % mod ;
	for (int i = n ; i < m ; ++i) g[i] = 0 ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 0 ; i < n ; ++i) {
		int a ;
		scanf("%d" , &a) ;

		if (a <= m) f[a] = 1 ;
	}

	///

	n = m ; init(n) ;

	int n1 = m ; f[0] = 1 ;
	for (int i = 1 ; i <= n ; ++i) f[i] = (mod - (f[i] << 2)) % mod ;

	sqrt(n1 , f , g) ;

	(++g[0]) %= mod ;
	inverse(n1 , g , g1) ;

	for (int i = 1 ; i <= n ; ++i)
		printf("%d\n" , (g1[i] << 1) % mod) ;

	return 0 ;
}