#include <stdio.h>
#include <stdlib.h>

const int MAX_N = 1e3 + 10 ;

int n , s ;
double f[MAX_N][MAX_N] ;

int main() {
	scanf("%d %d" , &n , &s) ;

	///

	for (int i = s ; i >= 0 ; --i)
		for (int j = n ; j >= 0 ; --j) {
			if (i == s && j == n) continue ;

			double c = s * n - i * j ,
				   num = s * n / c ,
				   p1 = (s - i) * (n - j) * f[i + 1][j + 1] / c ,
				   p2 = (s - i) * j * f[i + 1][j] / c ,
				   p3 = i * (n - j) * f[i][j + 1] / c ;

			f[i][j] = num + p1 + p2 + p3 ;
		}

	printf("%0.4lf\n" , f[0][0]) ;

	return 0 ;
}
