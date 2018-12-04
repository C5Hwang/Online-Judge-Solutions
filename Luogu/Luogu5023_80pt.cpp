#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 8 + 5 , MAX_S = (1 << 8) + 10 , mod = 1e9 + 7 ;

int n , m , S , p , pl[2][MAX_S][MAX_S] , f[2][MAX_S][MAX_N] , g[MAX_S][MAX_N] ;

inline int getp(int S , int p) {
	--p ;
	return (S & (1 << p)) ? 1 : 0 ;
}

void work(int S1 , int S2) {
	int le = pl[0][S1][S2] , sm = pl[1][S1][S2] ;

	if (sm <= le) (f[p][S1][sm] += g[S2][le]) %= mod ;
	else {
		(f[p][S1][le] += f[p^1][S2][le]) %= mod ;
		(f[p][S1][sm] += g[S2][sm]) %= mod ;
	}
}

int main() {
	scanf("%d %d" , &n , &m) ;
	S = 1 << n ;

	///

	for (int i = 0 ; i < S ; ++i) {
		f[0][i][n] = 1 ;
		for (int j = 1 ; j <= n ; ++j) g[i][j] = 1 ;
	}

	for (int S1 = 0 ; S1 < S ; ++S1)
		for (int S2 = 0 ; S2 < S ; ++S2) {
			int le = 1 , sm = n ;

			for (int i = n - 1 ; i ; --i) {
				int j = i + 1 , a1 = getp(S1 , i) , a2 = getp(S2 , j) ;

				if (a1 == a2) sm = std::min(m , i + 1) ;
				else le = std::max(le , i + 1) ;
			}

			pl[0][S1][S2] = le ; pl[1][S1][S2] = sm ;
		}

	///

	p = 1 ;
	for (; --m ; p ^= 1) {
		for (int nS = 0 ; nS < S ; ++nS) {
			for (int i = 1 ; i <= n ; ++i) f[p][nS][i] = 0 ;

			work(nS , 0) ; work(nS , 1) ;

			int A = (nS & ((1 << (n - 1)) - 1)) ;
			for (int subA = A ; subA ; subA = (subA - 1) & A)
				work(nS , subA << 1) , work(nS , subA << 1 | 1) ;
		}

		for (int nS = 0 ; nS < S ; ++nS) {
			g[nS][n] = f[p][nS][n] ;
			for (int i = n - 1 ; i ; --i) g[nS][i] = (g[nS][i + 1] + f[p][nS][i]) % mod ;
		}
	}

	int ans = 0 ;
	for (int i = 0 ; i < S ; ++i) (ans += g[i][1]) %= mod ;

	printf("%d\n" , ans) ;

	return 0 ;
}