#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 20 + 5 , MAX_S = (1 << 20) + 10 , mod = 1e8 + 7 ;

int n , x[MAX_N] , y[MAX_N] ;
int f[MAX_N][MAX_S] , le[MAX_N][MAX_N] ;

int main() {
	scanf("%d" , &n) ;
	for (int i = 0 ; i < n ; ++i) scanf("%d %d" , &x[i] , &y[i]) ;

	///

	for (int i = 0 ; i < n ; ++i)
		for (int j = 0 ; j < n ; ++j) {
			if (i == j) {le[i][j] = (1 << i) ; continue ;}

			int y1 = std::min(y[i] , y[j]) , y2 = std::max(y[i] , y[j]) ;
			int mi = std::min(x[i] , x[j]) , ma = std::max(x[i] , x[j]) ;

			for (int p = 0 ; p < n ; ++p) {
				if (p == i || p == j) continue ;
				if (x[p] < mi || ma < x[p] || y[p] < y1 || y2 < y[p]) continue ;

				if ((x[i] - x[p]) * (y[j] - y[p]) == (x[j] - x[p]) * (y[i] - y[p])) le[i][j] |= (1 << p) ;
			}
		}

	///

	int ans = 0 ;

	for (int i = 0 ; i < n ; ++i) f[i][1 << i] = 1 ;
	for (int S = 0 ; S < (1 << n) ; ++S)
		for (int i = 0 ; i < n ; ++i) {
			if (!((1 << i) & S)) continue ;

			int cnt = 0 ;
			for (int j = 0 ; j < n ; ++j) {
				if ((1 << j) & S) {++cnt ; continue ;}
				if ((le[i][j] & S) != le[i][j]) continue ;

				int nS = S | (1 << j) ;
				(f[j][nS] += f[i][S]) %= mod ;
			}

			if (cnt >= 4) (ans += f[i][S]) %= mod ;
		}

	printf("%d\n" , ans) ;

	return 0 ;
}