#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 3e5 + 10 , mod = (479 << 21) + 1 , G = 3 ;

int pw[MAX_N] , ipw[MAX_N] ;
int n , m , phi , rev[MAX_N] , f[MAX_N] , g[MAX_N] , h1[MAX_N] , h2[MAX_N] ;

int qpow(int a , int t) {
	int s = 1 , tmp = a ;
	for (; t ; t >>= 1 , tmp = (ll)tmp * tmp % mod)
		if (t & 1) s = (ll)s * tmp % mod ;

	return s ;
}

void init(int len) {
	m = 1 ;
	int L = 0 ; for (; m <= len ; m <<= 1 , ++L) ;

	for (int i = 0 ; i < m ; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1)) ;
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

void cdq(int x , int y) {
	if (x == y) {
		f[x] = (ll)pw[x - 1] * f[x] % mod ;
		f[x] = (g[x] + mod - f[x]) % mod ;

		return ;
	}

	int mid = (x + y) >> 1 ;
	cdq(x , mid) ;

	int len = y - x ; init(len << 1) ;
	for (int i = 0 ; i < m ; ++i) h1[i] = h2[i] = 0 ;
	for (int i = x ; i <= mid ; ++i) h1[i - x] = (ll)f[i] * ipw[i - 1] % mod ;
	for (int i = 0 ; i <= len ; ++i) h2[i] = (ll)g[i + 1] * ipw[i + 1] % mod ;

	
	fnt(h1 , 1) ; fnt(h2 , 1) ;
	for (int i = 0 ; i < m ; ++i) h1[i] = (ll)h1[i] * h2[i] % mod ;
	fnt(h1 , -1) ;

	int ny = qpow(m , mod - 2) ;
	for (int i = mid + 1 ; i <= y ; ++i) {
		int p = i - x - 1 ;
		h1[p] = (ll)h1[p] * ny % mod ;
		(f[i] += h1[p]) %= mod ;
	}

	cdq(mid + 1 , y) ;
}

int main() {
	scanf("%d" , &n) ; phi = mod - 1 ;

	for (int i = 0 ; i <= n ; ++i) {
		int j = (((ll)i * (i - 1)) >> 1) % phi ;
		g[i] = qpow(2 , j) ;
	}

	pw[0] = ipw[0] = 1 ;
	for (int i = 1 ; i <= n ; ++i) {
		int tmp = qpow(i , mod - 2) ;
		pw[i] = (ll)pw[i - 1] * i % mod ;
		ipw[i] = (ll)ipw[i - 1] * tmp % mod ;
	}

	///

	cdq(1 , n) ;

	printf("%d\n" , f[n]) ;

	return 0 ;
}