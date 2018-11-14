#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int N = 1e3 , MAX_N = 1e3 + 10 , mod = 1e9 + 7 ;

int n , r , k , m , S[MAX_N][MAX_N] , f[MAX_N][MAX_N] , sum[MAX_N][MAX_N] ;

int main() {
	S[0][0] = 1 ;
	for (int i = 1 ; i <= N ; ++i)
		for (int j = 1 ; j <= N ; ++j) {
			S[i][j] = (S[i - 1][j - 1] + (ll)j * S[i - 1][j]) % mod ;
			sum[i][j] = (sum[i][j - 1] + S[i][j]) % mod ;
		}

	///

	for (; scanf("%d %d %d %d" , &n , &r , &k , &m) != EOF ;) {
		for (int i = 0 ; i <= n ; ++i) f[i][1] = i ;

		for (int j = 2 ; j <= r ; ++j)
			for (int i = 1 ; i <= n ; ++i) {
				if (i > k) f[i][j] = (f[i - k][j - 1] + f[i - 1][j]) % mod ;
				else f[i][j] = f[i - 1][j] ;
			}

		int ans = (ll)f[n][r] * sum[r][m] % mod ;
		printf("%d\n" , ans) ;
	}

	return 0 ;
}