#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 100 + 10 , MAX_M = 1e4 + 10 , INF = 0x3f3f3f3f ;

int m , map[MAX_M] ;
int n , dis[MAX_N][MAX_N] ;

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 0 ; i < m ; ++i) scanf("%d" , &map[i]) ;
	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= n ; ++j)
			scanf("%d" , &dis[i][j]) ;

	///
	
	for (int k = 1 ; k <= n ; ++k)
		for (int i = 1 ; i <= n ; ++i)
			for (int j = 1 ; j <= n ; ++j)
				dis[i][j] = std::min(dis[i][j] , dis[i][k] + dis[k][j]) ;

	int res = 0 ;
	for (int i = 0 ; i < m - 1 ; ++i)
		res += dis[map[i]][map[i + 1]] ;
	printf("%d\n" , res) ;

	return 0 ;
}
