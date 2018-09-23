#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 1e5 + 10 , MAX_NUM = 1e6 + 10 ;

int n , a[MAX_N] , f[MAX_NUM] ;

int main() {
	int inf = 0 ;

	scanf("%d" , &n) ;
	for (int i = 0 ; i < n ; ++i) {
		scanf("%d" , &a[i]) ;
		++f[a[i]] ; inf = std::max(inf , a[i]) ;
	}

	///
	
	for (int i = inf ; i > 0 ; --i)
		for (int j = i + i ; j <= inf ; j += i) f[j] += f[i] ;
	
	for (int i = 0 ; i < n ; ++i) printf("%d\n" , f[a[i]] - 1) ;

	return 0 ;
}
