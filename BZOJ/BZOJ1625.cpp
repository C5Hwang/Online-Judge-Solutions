#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 4000 + 10 , MAX_M = 2e4 + 10 , INF = 0x3f3f3f3f ;

int n , m , f[MAX_M] ;

int main() {
	scanf("%d %d" , &n , &m) ;

	for (int i = 0 ; i <= m ; ++i) f[i] = -INF ;
	f[0] = 0 ;

	for (int i = 0 ; i < n ; ++i) {
		int w , d ;
		scanf("%d %d" , &w , &d) ;

		for (int j = m ; j >= w ; --j) f[j] = std::max(f[j] , f[j - w] + d) ;
	}

	///
	
	int res = 0 ;
	for (int i = 0 ; i <= m ; ++i) res = std::max(res , f[i]) ;
	printf("%d\n" , res) ;

	return 0 ;
}
