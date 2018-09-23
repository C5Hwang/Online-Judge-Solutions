#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAX_T = 1e3 + 10 , MAX_M = 30 + 10 ;

int m , t , n ;
double p[MAX_T][MAX_M] , tp , f[MAX_T][MAX_M][MAX_M] ;

int main() {
	scanf("%d %d %d" , &m , &t , &n) ;

	while (m != 0 || t != 0 || n != 0) {
		tp = 1 ;
		memset(f , 0 , sizeof(f)) ;

		///

		for (int i = 1 ; i <= t ; ++i) {
			double temp = 1 ;
			for (int j = 1 ; j <= m ; ++j)
				scanf("%lf" , &p[i][j]) , temp *= (1 - p[i][j]) ;
			tp *= (1 - temp) ;
		}

		///
		
		double p1 = 1 ;
		for (int i = 1 ; i <= t ; ++i) {
			f[i][0][0] = 1 ;
			for (int j = 1 ; j <= m ; ++j) {
				f[i][j][0] = f[i][j - 1][0] * (1 - p[i][j]) ;

				for (int k = 1 ; k < n ; ++k)
					f[i][j][k] = f[i][j - 1][k - 1] * p[i][j] + f[i][j - 1][k] * (1 - p[i][j]) ;
			}

			double temp = 0 ;
			for (int k = 1 ; k < n ; ++k) temp += f[i][m][k] ;
			p1 *= temp ;
		}
		printf("%0.3lf\n" , tp - p1) ;

		scanf("%d %d %d" , &m , &t , &n) ;
	}
	
	return 0 ;
}
