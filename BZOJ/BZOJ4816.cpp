#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e6 + 10 , mod = 1e9 + 7 ;

bool vis[MAX_N] ;
int tot , pri[MAX_N] ;
int T , n , m , f[MAX_N] , f1[MAX_N] , g[MAX_N] , g1[MAX_N] , mu[MAX_N] ;

inline int qpow(int x , int t) {
	int s = 1 , tmp = x ;
	for (; t ; t >>= 1 , tmp = (ll)tmp * tmp % mod)
		if (t & 1) s = (ll)s * tmp % mod ;

	return s ;
}

void init() {
	n = MAX_N - 10 ;

	mu[1] = f[1] = 1 ;
	for (int i = 2 ; i <= n ; ++i) f[i] = (f[i - 1] + f[i - 2]) % mod ;
	for (int i = 1 ; i <= n ; ++i) f1[i] = qpow(f[i] , mod - 2) ;

	for (int i = 2 ; i <= n ; ++i) {
		if (!vis[i]) {pri[tot++] = i ; mu[i] = -1 ;}

		for (int j = 0 ; j < tot ; ++j) {
			int tmp = i * pri[j] ;
			if (tmp > n) break ;
			vis[tmp] = 1 ;

			if (i % pri[j]) mu[tmp] = -mu[i] ;
			else {mu[tmp] = 0 ; break ;}
		}
	}

	///

	for (int i = 1 ; i <= n ; ++i) g[i] = 1 ;
	for (int i = 1 ; i <= n ; ++i)
		for (int j = i ; j <= n ; j += i)
			if (mu[j / i] == 1) g[j] = (ll)g[j] * f[i] % mod ;
			else if (mu[j / i] == -1) g[j] = (ll)g[j] * f1[i] % mod ;

	g[0] = g1[0] = 1 ;
	for (int i = 1 ; i <= n ; ++i)
		g[i] = (ll)g[i - 1] * g[i] % mod , g1[i] = qpow(g[i] , mod - 2) ;
}

int main() {
	init() ;
	scanf("%d" , &T) ;
	for (; T-- ;) {
		scanf("%d %d" , &n , &m) ;
		if (n > m) std::swap(n , m) ;

		int ans = 1 ;
		for (int L = 1 ; L <= n ;) {
			int t1 = n / L , t2 = m / L , R = std::min(n / t1 , m / t2) ;
			int s1 = (ll)g[R] * g1[L - 1] % mod , s2 = (ll)t1 * t2 % (mod - 1) ;

			ans = (ll)ans * qpow(s1 , s2) % mod ; L = R + 1 ;
		}

		printf("%d\n" , ans) ;
	}

	return 0 ;
}