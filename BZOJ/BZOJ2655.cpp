#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 500 + 10 , MAX_M = 1e3 + 10 ;

int n , m , A , mod , f[MAX_N][MAX_M] , y[MAX_M] , ny[MAX_M] ;

inline int qpow(int a , int t) {
	int s = 1 , tmp = a ;
	for (; t ; t >>= 1 , tmp = (ll)tmp * tmp % mod)
		if (t & 1) s = (ll)s * tmp % mod ;

	return s ;
}

inline int work(int x) {
	for (int i = 1 ; i <= m ; ++i) ny[i] = qpow(i , mod - 2) ;

	int res = 0 ;
	for (int i = 1 ; i <= m ; ++i) {
		int sum = y[i] ;
		for (int j = 1 ; j <= m ; ++j) 
			if (i != j) {
				int t = ny[abs(i - j)] ;
				if (i != j) sum = ((ll)sum * (x - j) % mod + mod) % mod ;
				sum = (ll)sum * t % mod ;

				if (i < j) sum = (mod - sum) % mod ;
			}

		(res += sum) %= mod ;
	}

	return res ;
}

int main() {
	scanf("%d %d %d" , &A , &n , &mod) ;

	///

	m = (n << 1) + 1 ;
	for (int i = 0 ; i <= m ; ++i) f[0][i] = 1 ;
	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= m ; ++j)
			f[i][j] = ((ll)j * f[i - 1][j - 1] + f[i][j - 1]) % mod ;

	for (int i = 1 ; i <= m ; ++i) y[i] = f[n][i] ;

	int res = work(A) ;
	for (int i = 1 ; i <= n ; ++i) res = (ll)res * i % mod ;
	printf("%d\n" , res) ;

	return 0 ;
}