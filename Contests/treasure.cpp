#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 12 + 10 , MAX_S = (1 << 12) + 10 , INF = 0x3f3f3f3f ;

int n , m , tot , dis[MAX_N][MAX_N] ;
int f[MAX_N][MAX_S] , g[MAX_N][MAX_S] , h[MAX_S][MAX_S] ;

void init() {
	for (int i = 1 ; i <= n ; ++i)
		for (int j = 0 ; j <= tot ; ++j)
			f[i][j] = INF ;
	for (int i = 0 ; i < n ; ++i)
		f[1][(1 << i)] = 0 ;
}

int main() {
	freopen("treasure.in" , "r" , stdin) ;
	freopen("treasure.out" , "w" , stdout) ;
	
	scanf("%d %d" , &n , &m) ;
	for (int i = 0 ; i < n ; ++i)
		for (int j = 0 ; j < n ; ++j)
			dis[i][j] = INF ;
	for (int i = 0 ; i < m ; ++i) {
		int x , y , v ;
		scanf("%d %d %d" , &x , &y , &v) ; --x ; --y ;
		dis[x][y] = std::min(dis[x][y] , v) ;
		dis[y][x] = std::min(dis[y][x] , v) ;
	}
	
	///

	tot = (1 << n) - 1 ;

	for (int i = 0 ; i < n ; ++i)
		for (int S = 1 ; S <= tot ; ++S) {
			g[i][S] = INF ;
			for (int j = 0 ; j < n ; ++j)
				if ((1 << j) & S) g[i][S] = std::min(g[i][S] , dis[i][j]) ;
		}

	for (int S1 = 1 ; S1 <= tot ; ++S1) {
		int lef = S1 ^ tot ;
		for (int S2 = lef ; S2 ; S2 = (S2 - 1) & lef) {
			bool ok = 1 ; int ans = 0 ;

			for (int i = 0 ; i < n && ok ; ++i)
				if ((1 << i) & S2) {
					if (g[i][S1] == INF) ok = 0 ;
					else ans += g[i][S1] ;
				}

			if (ok) h[S2][S1] = ans ;
			else h[S2][S1] = INF ;
		}
	}
	
	///
	
	init() ;
	
	for (int i = 2 ; i <= n ; ++i)
		for (int S = 0 ; S <= tot ; ++S)
			for (int ns = S ; ns ; ns = (ns - 1) & S) {
				bool ok = 1 ;
				int les = S ^ ns , cnt = h[ns][les] ;
				
				if (cnt < INF) f[i][S] = std::min(f[i][S] , f[i - 1][les] + cnt * (i - 1)) ;				
			}
	
	int ans = INF ;
	for (int i = 1 ; i <= n ; ++i)
		ans = std::min(ans , f[i][tot]) ;
	
	printf("%d\n" , ans) ;
	
	fclose(stdin) ; fclose(stdout) ;
	
	return 0 ;
}
