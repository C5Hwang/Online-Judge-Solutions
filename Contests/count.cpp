#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int lgN = 30 + 5 , MAX_M = 200 + 10 , mod = 998244353 ;

int s1 , s2 , S , sigma ;
int n , m , f[MAX_M][lgN * MAX_M] , g[MAX_M][lgN * MAX_M] ;

int dp(int w) {
	int M = m << 1 , tot = w * m ;

	for (int i = 0 ; i <= tot ; ++i) f[0][i] = 0 , g[0][i] = 1 ;
	f[0][0] = 1 ;
	
	for (int i = 1 ; i <= M ; ++i)
		for (int j = 0 ; j <= tot ; ++j) {
			int L = std::max(0 , j - w) ;

			if (!L) f[i][j] = g[i - 1][j] ;
			else f[i][j] = (g[i - 1][j] + mod - g[i - 1][L - 1]) % mod ;

			if (!j) g[i][j] = f[i][j] ;
			else g[i][j] = (g[i][j - 1] + f[i][j]) % mod ;
		}

	return f[M][tot] ;
}

int qpow(int a , int t) {
	int s = 1 , tmp = a ;

	for (; t ; t >>= 1 , tmp = (ll)tmp * tmp % mod)
		if (t & 1) s = (ll)s * tmp % mod ;

	return s ;
}

int main() {
	freopen("count.in" , "r" , stdin) ;
	freopen("count.out" , "w" , stdout) ;

	scanf("%d %d" , &n , &m) ;

	sigma = 1 ; s2 = 1 ;
	for (int i = 2 ; i * i <= n ; ++i) {
		int w = 0 ;
		for (; !(n % i) ; n /= i) ++w ;

		if (!w) continue ;

		sigma *= (w + 1) ;
		s2 = (ll)s2 * dp(w) % mod ;
	}

	if (n > 1) {
		sigma <<= 1 ;
		s2 = (ll)s2 * dp(1) % mod ;
	}

	///

	int ny = qpow(2 , mod - 2) ;
	S = qpow(sigma , m << 1) ;
	s1 = (S + mod - s2) % mod ;
	s1 = (ll)s1 * ny % mod ;

	printf("%d\n" , (s1 + s2) % mod) ;

	fclose(stdin) ; fclose(stdout) ;

	return 0 ;
}