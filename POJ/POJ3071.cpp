#include <stdio.h>
#include <stdlib.h>

const int MAX_N = (1 << 7) + 10 ;

int n ;
double p[MAX_N][MAX_N] , f[4 * MAX_N][MAX_N] ;

void dp(int t , int x , int y) {
	for (int i = 1 ; i <= n ; ++i) f[t][i] = 0 ;
	if (x == y) {
		f[t][x] = 1 ;
		return ;
	}

	int mid = (x + y) >> 1 , L = (t << 1) , R = (t << 1) + 1 ;
	dp(L , x , mid) ; dp(R , mid + 1 , y) ;
	for (int i = x ; i <= mid ; ++i)
		for (int j = mid + 1 ; j <= y ; ++j)
			f[t][i] += f[R][j] * f[L][i] * p[i][j] ;

	for (int i = mid + 1 ; i <= y ; ++i)
		for (int j = x ; j <= mid ; ++j)
			f[t][i] += f[L][j] * f[R][i] * p[i][j] ;
}

int main() {
	scanf("%d" , &n) ;
   	while (n != -1) {
		n = (1 << n) ;
		for (int i = 1 ; i <= n ; ++i)
			for (int j = 1 ; j <= n ; ++j)
				scanf("%lf" , &p[i][j]) ;

		///
		
		dp(1 , 1 , n) ;
		int res = 1 ; double maxP = f[1][1] ;
		for (int i = 2 ; i <= n ; ++i)
			if (f[1][i] > maxP) maxP = f[1][i] , res = i ;
		printf("%d\n" , res) ;

		scanf("%d" , &n) ;
	}

	return 0 ;
}
