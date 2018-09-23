#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 100 + 10 ;

bool ap[MAX_N] ;
int f[MAX_N][MAX_N] , g[MAX_N][MAX_N] ;
int Q , n , cur , tot , prime[MAX_N] , cir[MAX_N] ;

void init() {
	tot = 0 ;
	memset(f , 0 , sizeof(f)) ;
	memset(g , 0 , sizeof(g)) ;
	memset(ap , 0 , sizeof(ap)) ;

	for (int i = 2 ; i <= n ; ++i) {
		if (!ap[i]) prime[tot++] = i ;

		for (int j = 0 ; j < tot ; ++j) {
			int tmp = i * prime[j] ;
			if (tmp > n) break ;

			ap[tmp] = 1 ;
			if (!(i % prime[j])) break ;
		}
	}
}

int main() {
	scanf("%d" , &Q) ;
	for (; Q-- ;) {
		scanf("%d" , &n) ;

		///

		if (n == 1) {printf("1 1\n") ; continue ;}
		init() ;

		///

		f[0][0] = 1 ;
		for (int i = 2 ; i <= n ; i <<= 1) f[0][i] = i , g[0][i] = i ;
		for (int i = 1 ; i < tot ; ++i)
			for (int j = 0 ; j <= n ; ++j) {
				f[i][j] = f[i - 1][j] ; g[i][j] = 0 ;

				int p = prime[i] ;
				for (int k = p ; j >= k ; k *= p) {
					int tmp = f[i - 1][j - k] * k ;

					if (f[i][j] < tmp) f[i][j] = tmp , g[i][j] = k ;
				}
			}

		///

		int lcm = 0 , s = -1 ;
		for (int i = 0 ; i <= n ; ++i)
			if (lcm < f[tot - 1][i]) lcm = f[tot - 1][i] , s = i ;

		cur = 0 ;
		for (int i = 0 ; i < n - s ; ++i) cir[cur++] = 1 ;
		for (int i = tot - 1 ; s ; --i)
			if (g[i][s]) cir[cur++] = g[i][s] , s -= g[i][s] ;

		///

		std::sort(cir + 0 , cir + cur) ;

		printf("%d " , lcm) ;
		for (int p = 1 , i = 0 ; i < cur ; ++i) {
			if (cir[i] == 1) printf("%d " , p) ;
			else {
				int ed = p + cir[i] ;
				for (int j = p + 1 ; j < ed ; ++j) printf("%d " , j) ;
				printf("%d " , p) ;
			}

			p += cir[i] ;
		}
		printf("\n") ;
	}

	return 0 ;
}