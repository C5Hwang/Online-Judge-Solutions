#include <stdio.h>
#include <stdlib.h>

#define ll long long

const int MAX_N = 2e7 + 10 , MAX_P = 100 + 10 , MOD = 20170408 ;

bool vis[MAX_N] ;
int n , m , p , cur , prime[MAX_N] , cnt[MAX_P] ;
int A[MAX_P][MAX_P] , B[MAX_P][MAX_P] , C[MAX_P][MAX_P] , f[MAX_P][MAX_P] , g[MAX_P][MAX_P] ;

void euler() {
	cur = 0 ; vis[1] = 1 ;

	for (int i = 2 ; i <= m ; ++i) {
		if (!vis[i]) prime[cur++] = i ;

		for (int j = 0 ; j < cur ; ++j) {
			int tmp = i * prime[j] ;
			if (tmp > m) break ;

			vis[tmp] = 1 ;
			if (!(i % prime[j])) break ;
		}
	}
}

void times(int (*A)[MAX_P] , int (*B)[MAX_P] , int n , int m) {
	for (int i = 0 ; i < n ; ++i)
		for (int j = 0 ; j < m ; ++j) {
			C[i][j] = 0 ;
			for (int r = 0 ; r < p ; ++r) (C[i][j] += ((ll)A[i][r] * B[r][j]) % MOD) %= MOD ;
		}

	for (int i = 0 ; i < n ; ++i)
		for (int j = 0 ; j < m ; ++j)
			B[i][j] = C[i][j] ;
}

void qpow(int x) {
	if (x == 1) return ;
	qpow(x >> 1) ;

	times(B , B , p , p) ;
	if (x & 1) times(A , B , p , p) ;
}

void work() {
	for (int i = 0 ; i < p ; ++i) g[i][0] = cnt[i] ;
	for (int i = 0 ; i < p ; ++i)
		for (int j = 0 ; j < p ; ++j) {
			int k = i >= j ? i - j : i - j + p ;
			A[i][j] = B[i][j] = cnt[k] ;
		}

	qpow(n - 1) ;
	times(B , g , p , 1) ;
}

int main() {
	scanf("%d %d %d" , &n , &m , &p) ;

	///

	euler() ;

	///

	for (int i = 1 ; i <= m ; ++i) ++cnt[i % p] ;
	work() ;

	for (int i = 0 ; i < p ; ++i) f[i][0] = g[i][0] ;

	for (int i = 0 ; i < cur ; ++i) --cnt[prime[i] % p] ;
	work() ;

	printf("%d\n" , (f[0][0] - g[0][0] + MOD) % MOD) ;

	return 0 ;
}