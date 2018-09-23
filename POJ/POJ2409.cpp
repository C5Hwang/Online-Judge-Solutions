#include <stdio.h>
#include <stdlib.h>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 32 + 5 ;

bool ap[MAX_N] ;
int n , m , eg[MAX_N] , c[MAX_N][MAX_N] ;

void dfs(int x) {
	if (ap[x]) return ;
	ap[x] = 1 ; dfs(eg[x]) ;
}

void init() {
	int K = 32 ;
	for (int i = 1 ; i <= K ; ++i)
		for (int j = 1 ; j <= i ; ++j) {
			int a = 1 ;
			for (int p = j ; p <= i ; ++p , ++(a %= i)) eg[p] = a , ap[p] = 0 ;
			for (int p = 1 ; p < j ; ++p , ++(a %= i)) eg[p] = a , ap[p] = 0 ;

			int res = 0 ;
			for (int p = 1 ; p <=i ; ++p) {
				if (ap[p]) continue ;
				dfs(p) ; ++res ;
			}
			c[i][j] = res ;
		}
}

int qpow(int a , int t) {
	if (t == 1) return a ;

	int s = qpow(a , t >> 1) ;
	s *= s ; if (t & 1) s *= a ;

	return s ;
}

int main() {
	init() ;

	///

	scanf("%d %d" , &m , &n) ;
	for (; n != 0 || m != 0 ; scanf("%d %d" , &m , &n)) {
		int ans ;
		if (n & 1) ans = n * qpow(m , (n + 1) >> 1) ;
		else {
			ans = (n >> 1) * qpow(m , ((n + 1) >> 1) + 1) ;
			ans += (n >> 1) * qpow(m , n >> 1) ;
		}

		for (int i = 1 ; i <= n ; ++i) {
			int tc = c[n][i] ;
			ans += qpow(m , tc) ;
		}

		ans /= (n << 1) ;
		printf("%d\n" , ans) ;
	}

	return 0 ;
}