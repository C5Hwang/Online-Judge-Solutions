#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 20 + 10 , MAX_T = 300 + 10 , INF = 0x3f3f3f3f ;

char s[MAX_N] ;
int n , T , f[MAX_T][MAX_N] , g[MAX_T][MAX_N] ;

void getG(int n) {
	for (int i = 0 ; i <= T ; ++i)
		for (int j = 0 ; j <= n ; ++j)
			g[i][j] = INF ;

	for (int j = n ; j >= 0 ; --j) {
		for (int k = j + 1 ; k <= n ; ++k)
			g[0][j] = std::min(g[0][k] + 1 , g[0][j]) ;

		for (int i = 1 ; i <= T ; ++i) {
			int num = 0 ;

			for (int k = j ; k <= n ; ++k) {
				num = num * 10 + s[k] - '0' ;

				if (!num) {
					if (k == n) g[0][j] = 0 ;
					else g[0][j] = std::min(g[0][j] , 1) ;
					continue ;
				}
				if (num > i) break ;
				if (i % num) continue ;

				if (k < n) g[i][j] = std::min(g[i][j] , g[i / num][k + 1] + 1) ;
				else if (i == num) g[i][j] = 0 ;
			}
		}
	}
}

void init() {
	for (int i = 0 ; i <= T ; ++i)
		for (int j = 0 ; j <= n ; ++j)
			f[i][j] = INF , g[i][j] = 0 ;
}

int main() {
	freopen("puzzle.in" , "r" , stdin) ;
	freopen("puzzle.out" , "w" , stdout) ;

	scanf("%s" , s) ; scanf("%d" , &T) ;
	while (T != -1) {
		n = strlen(s) ;
		init() ;

		for (int j = 0 ; j < n ; ++j) {
			getG(j) ;

			for (int i = 0 ; i <= T ; ++i) {
				int fc = 1 , num = 0 ;

				//+ -> f
				for (int k = j ; k >= 0 ; --k , fc *= 10) {
					num += (s[k] - '0') * fc ;
					if (num > i) break ;
					if (!k) {
						if (i == num) f[i][j] = 0 ;
						break ;
					}
					f[i][j] = std::min(f[i - num][k - 1] + 1 , f[i][j]) ;
				}

				//* -> f
				for (int k = j ; k >= 0 ; --k)
					for (int tn = 0 ; tn <= i ; ++tn) {
						if (k) f[i][j] = std::min(f[i - tn][k - 1] + g[tn][k] + 1 , f[i][j]) ;
						else if (!k && tn == i) f[i][j] = std::min(f[i][j] , g[tn][k]) ;
					}
			}
		}

		if (f[T][n - 1] == INF) printf("-1\n") ;
		else printf("%d\n" , f[T][n - 1]) ;

		scanf("%s" , s) ; scanf("%d" , &T) ;
	}

	fclose(stdin) ; fclose(stdout) ;

	return 0 ;
}
