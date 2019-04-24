#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int N = 5e4 , MAX_N = 5e4 + 10 , MAX_M = 1e5 + 10 , mod = 1e9 + 7 ;

bool vis[MAX_N] ;
int n , m , T , tot , pri[MAX_N] , f[MAX_M] , g[MAX_M] ;

void initpri() {
	for (int i = 2 ; i <= N ; ++i) {
		if (!vis[i]) pri[tot++] = i ;

		for (int j = 0 ; j < tot ; ++j) {
			int tmp = i * pri[j] ;
			if (tmp > N) break ;

			vis[tmp] = 1 ;
			if (!(i % pri[j])) break ;
		}
	}
}

void init(int n) {
	for (T = 1 ; T <= n ; T <<= 1) ;
	for (int i = 0 ; i < T ; ++i) f[i] = g[i] = 0 ;
	f[0] = 1 ;
}

inline int qpow(int a , int t) {
	int s = 1 , tmp = a ;
	for (; t ; t >>= 1 , tmp = (ll)tmp * tmp % mod)
		if (t & 1) s = (ll)s * tmp % mod ;

	return s ;
}
void fwt(int *f , int ty) {
	int ny = ty < 0 ? qpow(2 , mod - 2) : 1 ;

	for (int L = 2 ; L <= T ; L <<= 1)
		for (int i = 0 , hf = L >> 1 ; i < T ; i += L)
			for (int j = 0 ; j < hf ; ++j) {
				int x = f[i + j] , y = f[i + j + hf] ;
				f[i + j] = (x + y) % mod ;
				f[i + j + hf] = (x - y + mod) % mod ;

				f[i + j] = (ll)f[i + j] * ny % mod ;
				f[i + j + hf] = (ll)f[i + j + hf] * ny % mod ;
			}
}

void work(int t) {
	fwt(f , 1) ; fwt(g , 1) ;

	for (; t ; t >>= 1) {
		if (t & 1) for (int i = 0 ; i < T ; ++i) f[i] = (ll)f[i] * g[i] % mod ;
		for (int i = 0 ; i < T ; ++i) g[i] = (ll)g[i] * g[i] % mod ;
	}

	fwt(f , -1) ;
}


int main() {
	initpri() ;
	for (; scanf("%d %d" , &n , &m) != EOF ;) {
		init(m) ;
		for (int i = 0 ; i < tot ; ++i)
			if (pri[i] <= m) g[pri[i]] = 1 ; else break ;

		///

		work(n) ;

		printf("%d\n" , f[0]) ;
	}

	return 0 ;
}