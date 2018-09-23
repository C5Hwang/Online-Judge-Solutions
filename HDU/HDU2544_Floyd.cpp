#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std ;

const int MAX_N = 100 + 10 , INF = 0x3f3f3f3f ;

int n , m , f[MAX_N][MAX_N] ;

void init() {
	for (int i = 0 ; i < MAX_N ; ++i)
		for (int j = 0 ; j < MAX_N ; ++j)
			f[i][j] = INF ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 0 ; i < n ; ++i) {
		init() ;
		
		for (int i = 0 ; i < m ; ++i) {
			int x , y , v ;
			scanf("%d %d %d" , &x , &y , &v) ;
			
			f[x][y] = min(f[x][y] , v) ;
			f[y][x] = min(f[y][x] , v) ;
		}
		
		for (int k = 1 ; k <= n ; ++k)
			for (int i = 1 ; i <= n ; ++i)
				for (int j = 1 ; j <= n ; ++j)
					f[i][j] = min(f[i][j] , f[i][k] + f[k][j]) ;
		
		printf("%d\n" , f[1][n]) ;
		scanf("%d %d" , &n , &m) ;
	}
	
	return 0 ;
}
