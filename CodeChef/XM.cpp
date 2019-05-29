#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int K = 30 , MAX_N = 1e5 + 10 , MAX_K = 30 + 5 ;

int T , n , q , a[MAX_N] , b[MAX_N] , s[MAX_K][MAX_N] , f[MAX_K][MAX_N][2] ;

int main() {
	scanf("%d" , &T) ;
	for (; T-- ;) {
		scanf("%d %d" , &n , &q) ;
		for (int i = 1 ; i <= n ; ++i) scanf("%d" , &a[i]) ;

		for (int i = 0 ; i <= K ; ++i) {
			f[i][n + 1][0] = f[i][n + 1][1] = 0 ;
			for (int j = 1 ; j <= n ; ++j) b[j] = a[j] >> i & 1 ;

			s[i][1] = b[1] ;
			for (int j = 2 ; j <= n ; ++j) s[i][j] = s[i][j - 1] + b[j] ;

			for (int j = n ; j ; --j) {
				int len = 1 << i , k = j + len ;

				if (k > n) {
					f[i][j][0] = f[i][j + 1][0] + b[j] ;
					f[i][j][1] = f[i][j + 1][1] + (b[j] ^ 1) ;
				}
				else {
					f[i][j][0] = f[i][k][1] + s[i][k - 1] - s[i][j - 1] ;
					f[i][j][1] = f[i][k][0] + len - s[i][k - 1] + s[i][j - 1] ;
				}
			}
		}

		///

		for (; q-- ;) {
			int x , y ; ll ans = 0 ;
			scanf("%d %d" , &x , &y) ;

			for (int i = 0 ; i <= K ; ++i) {
				int bk = 1 << i , len = y - x + 1 , tmp = 0 ,
					ofs = len % bk , ty = (len / bk) & 1 , nx = x + len / bk * bk ;

				tmp = f[i][x][0] - f[i][nx][ty] ;
				if (ofs) {
					if (ty) tmp += ofs - s[i][y] + s[i][nx - 1] ;
					else tmp += s[i][y] - s[i][nx - 1] ;
				}

				ans += (ll)tmp * bk ;
			}

			printf("%lld\n" , ans) ;
		} 
	}

	return 0 ;
}