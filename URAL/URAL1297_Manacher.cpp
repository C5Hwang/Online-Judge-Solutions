#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_L = 1000 + 10 ;

int n , next[2 * MAX_L] ;
char s[2 * MAX_L] , st[MAX_L] ;

int main() {
	scanf("%s" , st) ; int len = strlen(st) ;
	n = 0 ; s[n++] = '$' ; s[n++] = '#' ;
	for (int i = 0 ; i < len ; ++i)
		s[n++] = st[i] , s[n++] = '#' ;
	s[n++] = '*' ;

	///
	
	int maxr = 0 , maxrp = 1 , p = 1 ;
	next[1] = 0 ;
	for (int i = 2 ; i < n - 1 ; ++i) {
		int u = p + next[p] , r = std::max(0 , std::min(next[2 * p - i] , u - i)) ;

		for (; s[i + r + 1] == s[i - r - 1] ; ++r) ;

		next[i] = r ;

		if (u < i + r) p = i ;

		if (r > maxr) maxr = r , maxrp = i ;
	}

	for (int i = maxrp - maxr ; i <= maxrp + maxr ; ++i)
		if (s[i] != '#') printf("%c" , s[i]) ;
	printf("\n") ;

	return 0 ;
}
