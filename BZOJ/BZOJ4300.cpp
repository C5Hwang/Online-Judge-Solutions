#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_L = 30 + 10 ;

int n , a , f[MAX_L] ;

int main() {
	scanf("%d" , &n) ;
	for (int i = 0 ; i < n ; ++i) {
		scanf("%d" , &a) ;

		int tmp = 0 ;
		for (int i = 0 ; i <= 30 ; ++i)
			if ((1 << i) & a) tmp = std::max(tmp , f[i] + 1) ;

		for (int i = 0 ; i <= 30 ; ++i) 
			if ((1 << i) & a) f[i] = std::max(f[i] , tmp) ;
	}

	int ans = 0 ;
	for (int i = 0 ; i <= 30 ; ++i)
		ans = std::max(ans , f[i]) ;

	printf("%d\n", ans) ;

	return 0 ;
}