#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_P = 9 + 5 , MAX_N = 100 + 10 , mod = 1e9 ;
const int dx[4] = {0 , 0 , 1 , -1} , dy[4] = {1 , -1 , 0 , 0} ;

char s[MAX_P][MAX_P] ;
int n , m , tot , bh[MAX_P][MAX_P] , a[MAX_N][MAX_N] ;

inline int gauss() {
	int f = 1 , s = 1 ;
	for (int i = 1 ; i < tot ; ++i) {
		for (int j = i + 1 ; j < tot ; ++j)
			for (; a[j][i] ;) {
				int t = a[i][i] / a[j][i] ;
				for (int k = i ; k <= tot ; ++k)
					a[i][k] = (a[i][k] - (ll)t * a[j][k] % mod + mod) % mod ;
				for (int k = i ; k <= tot ; ++k) std::swap(a[i][k] , a[j][k]) ;
				f = -f ;
			}
		s = (ll)s * a[i][i] % mod ;
	}

	if (f < 0) s = (mod - s) % mod ;
	return s ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 1 ; i <= n ; ++i) {
		scanf("%s" , s[i]) ;
		for (int j = m ; j ; --j) s[i][j] = s[i][j - 1] ;
		for (int j = 1 ; j <= m ; ++j) if (s[i][j] != '*') bh[i][j] = ++tot ;
	}

	///

	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= m ; ++j) {
			if (s[i][j] == '*') continue ;

			for (int k = 0 ; k < 4 ; ++k) {
				int ni = i + dx[k] , nj = j + dy[k] ;
				if (ni < 1 || nj < 1 || ni > n || nj > m || s[ni][nj] == '*') continue ;

				int x = bh[i][j] , y = bh[ni][nj] ;
				(++a[x][x]) %= mod ; a[x][y] = (a[x][y] + mod - 1) % mod ;
			}
		}

	if (!tot) printf("0\n") ;
	else printf("%d\n" , gauss()) ;

	return 0 ;
}