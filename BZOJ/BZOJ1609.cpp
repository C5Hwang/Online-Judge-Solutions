#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 3e4 + 10 ;

int n , a[MAX_N] , f[MAX_N] , g[MAX_N] , MIN[5] ;

int main() {
	scanf("%d" , &n) ;
	for (int i = 0 ; i < n ; ++i)
		scanf("%d" , &a[i]) ;

	///
	
	int res1 , res2 ;

	res1 = res2 = 0 ;
	MIN[1] = MIN[2] = MIN[3] = 0 ;
	for (int i = 0 ; i < n ; ++i) {
		int r = 0 ;
		for (int j = 1 ; j <= a[i] ; ++j) r = std::max(r , MIN[j]) ;

		f[i] = r + 1 ;
		MIN[a[i]] = std::max(MIN[a[i]] , f[i]) ;
		res1 = std::max(res1 , f[i]) ;
	}

	MIN[1] = MIN[2] = MIN[3] = 0 ;
	for (int i = 0 ; i < n ; ++i) {
		int r = 0 ;
		for (int j = a[i] ; j <= 3 ; ++j) r = std::max(r , MIN[j]) ;

		g[i] = r + 1 ;
		MIN[a[i]] = std::max(MIN[a[i]] , g[i]) ;
		res2 = std::max(res2 , g[i]) ;
	}

	printf("%d\n" , n - std::max(res1 , res2)) ;

	return 0 ;
}
