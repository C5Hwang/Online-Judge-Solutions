#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAX_N = 1e3 + 10 ;

int n , m ;
double p[MAX_N][MAX_N][3] , f[MAX_N][MAX_N] ;

int main() {
	while (scanf("%d %d" , &n , &m) != EOF) {
		memset(f , 0 , sizeof(f)) ;

		for (int i = 1 ; i <= n ; ++i)
			for (int j = 1 ; j <= m ; ++j)
				for (int k = 0 ; k < 3 ; ++k)
					scanf("%lf" , &p[i][j][k]) ;

		///
		
		for (int i = n ; i > 0 ; --i)
			for (int j = m ; j > 0 ; --j) {
				if (p[i][j][0] == 1) continue ;

				double c = 1 - p[i][j][0] , num = 2 / c ,
					   p1 = p[i][j][1] * f[i][j + 1] / c,
					   p2 = p[i][j][2] * f[i + 1][j] / c ;

				f[i][j] = num + p1 + p2 ;
			}
		printf("%0.3lf\n" , f[1][1]) ;
	}

	return 0 ;
}
