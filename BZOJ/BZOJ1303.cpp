#include <stdio.h>
#include <stdlib.h>

#define cnt(i) cnt[i + offset]
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 , offset = 1e5 ;

int n , m , p , ans , a[MAX_N] , cnt[MAX_N << 1] ;

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 0 ; i < n ; ++i) {
		scanf("%d" , &a[i]) ;
		if (a[i] == m) p = i ;
	}

	///

	int s = 0 ; ++cnt(0) ;
	for (int i = p + 1 ; i < n ; ++i) {
		s += a[i] > m ? 1 : -1 ;
		++cnt(s) ;
	}

	s = 0 ; ans = cnt(0) ;
	for (int i = p - 1 ; i >= 0 ; --i) {
		s += a[i] > m ? 1 : -1 ;
		ans += cnt(-s) ;
	}

	printf("%d\n" , ans) ;

	return 0 ;
}