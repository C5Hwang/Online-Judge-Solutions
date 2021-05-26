#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 15 + 5 , MAX_M = 250 + 10 , MAX_S = (1 << 15) + 10 , mod = 1e9 + 7 ;

int n , m , f[MAX_S] , pw[MAX_M] , lk[MAX_N][MAX_N] , lcnt[MAX_N][MAX_S] ;

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 0 ; i < m ; ++i) {
		int x , y ;
		scanf("%d %d" , &x , &y) ;
		--x ; --y ; ++lk[x][y] ;
	}

	///

	int S = 1 << n ;
	for (int i = 0 ; i < n ; ++i)
		for (int tS = 0 ; tS < S ; ++tS)
			for (int j = 0 ; j < n ; ++j)
				if ((1 << j) & tS) lcnt[i][tS] += lk[i][j] ;

	pw[0] = 1 ;
	for (int i = 1 ; i <= m ; ++i) pw[i] = (pw[i - 1] << 1) % mod ;

	f[3] = 1 ;
	for (int nS = 4 ; nS < S ; ++nS) {
		if ((nS & 3) && (nS & 3) < 3) continue ;
		else f[nS] = 1 ;

		for (int U = (nS - 1) & nS ; U ; U = (U - 1) & nS) {
			int V = nS ^ U , s = f[U] , c = 0 ;

			for (int i = 0 ; i < n ; ++i)
				if ((1 << i) & U) {
					int tmp = (pw[lcnt[i][V]] - 1 + mod) % mod ;
					s = (ll)s * tmp % mod ;
				}
				else if ((1 << i) & V) (c += lcnt[i][U]) %= mod ;

			s = (ll)s * pw[c] % mod ;
			(f[nS] += s) %= mod ;
		}
	}

	int res = (pw[m] - f[S - 1] + mod) % mod ;
	printf("%d\n" , res) ;

	return 0 ;
}