#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 ;

int T , n , s1 , s2 , a[MAX_N] , od[MAX_N] , ev[MAX_N] ;

int main() {
	scanf("%d" , &T) ;
	for (int CASE = 1 ; T-- ; ++CASE) {
		scanf("%d" , &n) ; s1 = s2 = 0 ;

		for (int i = 0 ; i < n ; ++i) {
			int t ; scanf("%d" , &t) ;
			if (i % 2) od[s1++] = t ;
			else ev[s2++] = t ;
		}

		///

		std::sort(od + 0 , od + s1) ; std::sort(ev + 0 , ev + s2) ;
		for (int i = 0 ; i < n ; ++i)
			if (i % 2) a[i] = od[i >> 1] ;
			else a[i] = ev[i >> 1] ;

		int p ;
		for (p = 0 ; p < n - 1 ; ++p) if (a[p] > a[p + 1]) break ;

		printf("Case #%d: " , CASE) ;
		if (p == n - 1) printf("OK\n") ;
		else printf("%d\n" , p) ;
	}

	return 0 ;
}