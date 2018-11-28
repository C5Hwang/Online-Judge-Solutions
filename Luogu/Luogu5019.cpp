#include <stdio.h>
#include <stdlib.h>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 ;

int n , a[MAX_N] ;

int main() {
	scanf("%d" , &n) ;

	int ans = 0 ;
	for (int i = 1 ; i <= n ; ++i) {
		scanf("%d" , &a[i]) ;

		int tmp = a[i] - a[i - 1] ;
		if (tmp > 0) ans += tmp ;
	}

	printf("%d\n" , ans) ;

	return 0 ;
}