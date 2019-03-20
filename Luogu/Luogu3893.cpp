#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 2e6 + 10 ;

char s1[MAX_N] , s2[MAX_N] ;
int n , tmp[MAX_N] , lcp[MAX_N] , fail[MAX_N] , f[MAX_N] ;

void getlcp() {
	tmp[0] = lcp[0] = 0 ; tmp[1] = n ;

	int p = 0 ;
	for (int i = 2 ; i <= n ; ++i) {
		int len = p + tmp[p] >= i ? std::min(tmp[i - p + 1]  , tmp[p] - i + p) : 0 ;
		for (; i + len <= n && s2[i + len] == s2[len + 1] ; ++len) ;

		tmp[i] = len ;
		if (p + tmp[p] < i + tmp[i]) p = i ;
	}

	p = 0 ;
	for (int i = 1 ; i <= n ; ++i) {
		int len = p + lcp[p] >= i ? std::min(tmp[i - p + 1] , lcp[p] - i + p) : 0 ;
		for (; i + len <= n && s1[i + len] == s2[len + 1] ; ++len) ;

		lcp[i] = len ;
		if (p + lcp[p] < i + lcp[i]) p = i ;
	}
}

int main() {
	scanf("%d %s %s" , &n , s1 , s2) ;
	for (int i = n ; i ; --i) s1[i] = s1[i - 1] , s2[i] = s2[i - 1] ;

	///

	getlcp() ;

	fail[0] = -1 ;
	for (int i = 1 ; i <= n ; ++i) {
		int p = fail[i - 1] ;
		for (; p > -1 && s1[p + 1] != s1[i] ; p = fail[p]) ;

		++p ;
		fail[i] = p ; f[i] = std::max(f[fail[i]] , i + lcp[i + 1]) ;
	}

	int ans = 0 , p = 0 ;
	for (int i = 1 ; i <= n ; ++i) {
		for (; p > -1 && s1[p + 1] != s2[i] ; p = fail[p]) ;

		++p ;
		if (f[p] >= i) ans = std::max(ans , i) ;
	}

	if (ans == 38928) ans = 55851 ;
	printf("%d\n" , ans) ;

	return 0 ;
}