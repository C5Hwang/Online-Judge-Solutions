#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 2e3 + 10 ;

int n , P , f[MAX_N] , g[MAX_N] , ans[MAX_N] , C[MAX_N][MAX_N] ;

inline int qpow(int a , int t) {
	int s = 1 , tmp = a ;
	for (; t ; t >>= 1 , tmp = (ll)tmp * tmp % P)
		if (t & 1) s = (ll)s * tmp % P ;

	return s ;
}

int main() {
	freopen("path.in" , "r" , stdin) ;
	freopen("path.out" , "w" , stdout) ;

	scanf("%d %d" , &n , &P) ;

	///

	C[0][0] = 1 ;
	for (int i = 1 ; i <= n ; ++i) {
		C[i][0] = 1 ;
		for (int j = 1 ; j <= n ; ++j)
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % P ;
	}

	f[0] = 1 ;
	for (int i = 1 ; i <= n ; ++i) {
		int s = (i * (i - 1)) >> 1 ;
		f[i] = qpow(2 , s) ;
	}

	g[1] = 1 ;
	for (int i = 2 ; i <= n ; ++i) {
		int sum = 0 ;
		for (int j = 1 ; j < i ; ++j) {
			int tmp = (ll)g[j] * f[i - j] % P * C[i][j] % P ;
			(sum += tmp) %= P ;
		}

		g[i] = (f[i] - sum + P) % P ;
	}

	///

	for (int i = 1 ; i <= n ; ++i)
		for (int j = 0 ; j <= n ; ++j) {
			if (i + j > n) break ;
			int t1 = (ll)g[i] * C[n - 1][i - 1] % P , t2 = (ll)f[j] * C[n - i][j] % P ;
			t1 = (ll)t1 * t2 % P * f[n - i - j] % P ;

			(ans[i + j] += t1) %= P ;
		}

	for (int i = 1 ; i <= n ; ++i) printf("%d\n" , ans[i]) ;

	return 0 ;
}