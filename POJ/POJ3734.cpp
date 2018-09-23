#include <stdio.h>
#include <stdlib.h>

const int mod = 10007 ;

int T , n , a[4][4] , b[4][4] , temp[4][4] ;

void mul(int w1 , int w2 , int (*a)[4] , int (*b)[4]) {
	int c[w1][w2] ;
	for (int i = 0 ; i < w1 ; ++i)
		for (int j = 0 ; j < w2 ; ++j) {
			c[i][j] = 0 ;
			for (int r = 0 ; r < 4 ; ++r)
				c[i][j] = (c[i][j] + a[i][r] * b[r][j]) % mod ;
		}

	for (int i = 0 ; i < w1 ; ++i)
		for (int j = 0 ; j < w2 ; ++j)
			b[i][j] = c[i][j] ;
}

void power(int n) {
	if (n == 1) return ;

	power(n >> 1) ;
	mul(4 , 4 , temp , temp) ;
	if (n % 2) mul(4 , 4 , b , temp) ;
}

int main() {
	scanf("%d" , &T) ;
	while (T--) {
		scanf("%d" , &n) ;
		
		///

		a[0][0] = 1 ;
		for (int i = 1 ; i < 4 ; ++i) a[i][0] = 0 ;
		for (int i = 0 ; i < 4 ; ++i)
			for (int j = 0 ; j < 4 ; ++j)
				if (i == j) b[i][j] = temp[i][j] = 2 ;
				else if (i + j == 3) b[i][j] = temp[i][j] = 0 ;
				else b[i][j] = temp[i][j] = 1 ;

		///

		power(n) ;
		mul(4 , 1 , temp , a) ;

		printf("%d\n" , a[0][0]) ;
	}

	return 0 ;
}
