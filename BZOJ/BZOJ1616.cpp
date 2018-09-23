#include <stdio.h>
#include <stdlib.h>

const int MAX_N = 100 + 10 , MAX_T = 15 + 10 ,
	  	  dx[4] = {0 , 0 , 1 , -1} ,
		  dy[4] = {1 , -1 , 0 , 0} ;

char map[MAX_N][MAX_N] ;
int n , m , t , f[MAX_N][MAX_N][MAX_T] ;

int main() {
	scanf("%d %d %d" , &n , &m , &t) ;
	for (int i = 0 ; i < n ; ++i) {
		getchar() ;
		for (int j = 0 ; j < m ; ++j)
			scanf("%c" , &map[i][j]) ;
	}

	///
	
	int r1 , c1 , r2 , c2 ;
	scanf("%d %d %d %d" , &r1 , &c1 , &r2 , &c2) ;
	--r1 ; --c1 ; --r2 ; --c2 ;
	f[r1][c1][0] = 1 ;
	for (int k = 1 ; k <= t ; ++k) 
		for (int i = 0 ; i < n ; ++i) 
			for (int j = 0 ; j < m ; ++j) {
				int sum = 0 ;

				for (int p = 0 ; p < 4 ; ++p) {
					int x = i + dx[p] , y = j + dy[p] ;
					if (x < 0 || x >= n || y < 0 || y >= m || map[x][y] == '*') continue ;

					sum += f[x][y][k - 1] ;
				}

				f[i][j][k] = sum ;
			}

	printf("%d\n" , f[r2][c2][t]) ;

	return 0 ;
}
