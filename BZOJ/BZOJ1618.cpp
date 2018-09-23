#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 100 + 10 , MAX_H = 1e5 + 10 , INF = 0x3f3f3f3f ;

int n , h , p[MAX_N] , c[MAX_N] , f[MAX_H] ;

int main() {
	scanf("%d %d" , &n , &h) ;
	for (int i = 0 ; i < n ; ++i)
		scanf("%d %d" , &p[i] , &c[i]) ;

	///
	
	for (int i = 0 ; i <= (h << 1) ; ++i) f[i] = INF ;
	f[0] = 0 ;
	for (int i = 0 ; i < n ; ++i) 
		for (int j = p[i] ; j <= (h << 1) ; ++j)
			f[j] = std::min(f[j] , f[j - p[i]] + c[i]) ;
	
	int res = f[h] ;
	for (int i = h + 1 ; i <= (h << 1) ; ++i) res = std::min(res , f[i]) ;
	printf("%d\n" , res) ;

	return 0 ;
}
