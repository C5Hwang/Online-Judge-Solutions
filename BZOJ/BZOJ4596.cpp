#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 17 + 5 , mod = 1e9 + 7 ;

int n , m , mat[MAX_N][MAX_N][MAX_N] , a[MAX_N][MAX_N] ;

inline void init() {
	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= n ; ++j) a[i][j] = 0 ;
}

inline void add(int t) {
	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= n ; ++j) (a[i][j] += mat[t][i][j]) %= mod ;
}

inline int gauss(int f) {
	int s = 1 ;
	for (int i = 1 ; i < n ; ++i) {
		for (int j = i + 1 ; j < n ; ++j)
			for (; a[j][i] ;) {
				int t = a[i][i] / a[j][i] ;
				for (int k = i ; k < n ; ++k)
					a[i][k] = (a[i][k] - (ll)t * a[j][k] % mod + mod) % mod ;
				for (int k = i ; k < n ; ++k) std::swap(a[i][k] , a[j][k]) ;
				f = -f ;
			}

		if (!a[i][i]) return 0 ;
		s = (ll)s * a[i][i] % mod ;
	}

	if (f == -1) s = (mod - s) % mod ;
	return s ;
}

int main() {
	scanf("%d" , &n) ; m = n - 1 ;
	for (int i = 0 ; i < m ; ++i) {
		int t ; scanf("%d" , &t) ;

		for (int j = 0 ; j < t ; ++j) {
			int x , y ; scanf("%d %d" , &x , &y) ;

			(++mat[i][x][x]) %= mod ; (++mat[i][y][y]) %= mod ;
			mat[i][x][y] = (mat[i][x][y] - 1 + mod) % mod ; mat[i][y][x] = (mat[i][y][x] - 1 + mod) % mod ;
		}
	}

	///

	int ans = 0 ;
	for (int S = 0 ; S < (1 << m) ; ++S) {
		init() ; int cnt = 0 ;
		for (int i = 0 ; i < m ; ++i) if ((1 << i) & S) add(i) , ++cnt ;

		(ans += gauss((m - cnt) & 1 ? -1 : 1)) %= mod ;
	}

	printf("%d\n" , ans) ;

	return 0 ;
}