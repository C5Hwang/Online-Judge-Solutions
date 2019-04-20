#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 , MAX_M = 4e5 + 10 , mod = (119 << 23) + 1 , G = 3 ;

int n , m , a[MAX_N] , b[MAX_N] , f[MAX_M] , g[MAX_M] , rev[MAX_M] ;

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

void fnt(int *f , int ty) {
	for (int i = 0 ; i < m ; ++i) if (i < rev[i]) std::swap(f[i] , f[rev[i]]) ;

	for (int L = 2 ; L <= m ; L <<= 1) {
		int hf = L >> 1 , phi = mod - 1 , gn ;
		if (ty > 0) gn = qpow(G , phi / L) ; else gn = qpow(G , phi - phi / L) ;

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

void times(int *f , int *g) {
	fnt(f , 1) ; fnt(g , 1) ;
	for (int i = 0 ; i < m ; ++i) f[i] = (ll)f[i] * g[i] % mod ;
	fnt(f , -1) ;

	int ny = qpow(m , mod - 2) ;
	for (int i = 0 ; i < m ; ++i) f[i] = (ll)f[i] * ny % mod ;
}

void init(int n) {
	int L = 0 ;
	for (m = 1 ; m <= n ; m <<= 1 , ++L) ;

	for (int i = 0 ; i < m ; ++i)
		f[i] = g[i] = 0 , rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1)) ;
}

void work(int x , int y) {
	if (x == y) return ;
	int mid = (x + y) >> 1 ;
	work(x , mid) ;

	init(y + mid - (x << 1) - 1) ;
	for (int i = x ; i <= mid ; ++i) f[i - x] = a[i] ;
	for (int i = 1 ; i <= y - x ; ++i) g[i - 1] = b[i] ;

	times(f , g) ;
	for (int i = mid + 1 ; i <= y ; ++i) (a[i] += f[i - x - 1]) %= mod ;

	work(mid + 1 , y) ;
}

int main() {
	n = read() ; -- n ; b[0] = 0 ; a[0] = 1 ;
	for (int i = 1 ; i <= n ; ++i) b[i] = read() ;

	///

	work(0 , n) ;
	for (int i = 0 ; i <= n ; ++i) printf("%d " , a[i]) ;
	printf("\n") ;

	return 0 ;
}