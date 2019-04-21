#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 2e5 + 10 , MAX_M = 8e5 + 10 , mod = (119 << 23) + 1 , G = 3 ;

int n , m , a[MAX_N] , b[MAX_M] , c[MAX_M] , f[MAX_M] , g[MAX_M] , rev[MAX_M] ;

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

inline int qpow(int a , int t) {
	int s = 1 , tmp = a ;
	for (; t ; t >>= 1 , tmp = (ll)tmp * tmp % mod)
		if (t & 1) s = (ll)s * tmp % mod ;

	return s ;
}

inline void fnt(int *f , int ty) {
	for (int i = 0 ; i < m ; ++i) if (i < rev[i]) std::swap(f[i] , f[rev[i]]) ;

	for (int L = 2 ; L <= m ; L <<= 1) {
		int hf = L >> 1 , phi = mod - 1 , gn ;
		if (ty > 0) gn = qpow(G , phi / L) ;
		else gn = qpow(G , phi - phi / L) ;

		for (int i = 0 ; i < m ; i += L) {
			int g = 1 ;
			for (int j = 0 ; j < hf ; ++j , g = (ll)g * gn % mod) {
				int tmp = (ll)f[i + j + hf] * g % mod ;
				f[i + j + hf] = (f[i + j] - tmp + mod) % mod ;
				(f[i + j] += tmp) %= mod ;
			}
		}
	}
}

inline void init(int n) {
	int L = 0 ;
	for (m = 1 ; m <= n ; m <<= 1 , ++L) ;

	for (int i = 0 ; i < m ; ++i)
		f[i] = g[i] = 0 , rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1)) ;
}

void getinv(int *a , int n) {
	if (!n) {c[0] = qpow(a[0] , mod - 2) ; return ;}
	getinv(a , n >> 1) ;

	init(n << 1) ;
	for (int i = 0 ; i <= n ; ++i) f[i] = c[i] , g[i] = a[i] ;

	fnt(f , 1) ; fnt(g , 1) ;
	for (int i = 0 ; i < m ; ++i) f[i] = ((f[i] << 1) - (ll)f[i] * f[i] % mod * g[i] % mod + mod) % mod ;
	fnt(f , -1) ;

	int ny = qpow(m , mod - 2) ;
	for (int i = 0 ; i <= n ; ++i) c[i] = (ll)f[i] * ny % mod ;
}

inline void getds(int *f , int n) {
	for (int i = 0 ; i < n ; ++i) f[i] = (ll)f[i + 1] * (i + 1) % mod ;
	f[n] = 0 ;
}

inline void getjf(int *f , int n) {
	for (int i = n ; i ; --i) f[i] = (ll)f[i - 1] * qpow(i , mod - 2) % mod ;
	f[0] = 0 ;
}

int main() {
	n = read() - 1 ;
	for (int i = 0 ; i <= n ; ++i) a[i] = b[i] = read() ;

	///

	getds(b , n) ;
	init(n) ; int o = m ;
	getinv(a , m) ; for (int i = n + 1 ; i <= o ; ++i) c[i] = 0 ;

	init(n << 1) ; fnt(b , 1) ; fnt(c , 1) ;
	for (int i = 0 ; i < m ; ++i) b[i] = (ll)b[i] * c[i] % mod ;
	fnt(b , -1) ;

	int ny = qpow(m , mod - 2) ;
	for (int i = 0 ; i < m ; ++i) b[i] = (ll)b[i] * ny % mod ;

	///

	getjf(b , n) ;
	for (int i = 0 ; i <= n ; ++i) printf("%d " , b[i]) ;
	printf("\n") ;

	return 0 ;
}