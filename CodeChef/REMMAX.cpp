#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e4 + 10 ;

int T , n ;
char s[MAX_N] , ans[MAX_N] ;

int main() {
	scanf("%d" , &T) ;
	for (; T-- ;) {
		scanf("%s" , s) ; n = strlen(s) ;

		///

		if (n == 1) ans[0] = s[0] ;
		else {
			bool ok = 1 ;
			for (int i = 1 ; i < n ; ++i) ok &= (s[i] == '9') ;

			if (ok) for (int i = 0 ; i < n ; ++i) ans[i] = s[i] ;
			else if (s[0] != '1') {
				ans[0] = s[0] - 1 ;
				for (int i = 1 ; i < n ; ++i) ans[i] = '9' ;
			}
			else {
				int np ;
				for (np = 1 ; np < n ; ++np) if (s[np] != '0') break ;

				if (np == n) {ans[0] = '0' ; for (int i = 1 ; i < n ; ++i) ans[i] = '9' ;}
				else if (np == n - 1) for (int i = 0 ; i < n ; ++i) ans[i] = s[i] ;
				else {
					for (int i = 0 ; i < np ; ++i) ans[i] = s[i] ;

					ok = 1 ;
					for (int i = np + 1 ; i < n ; ++i) ok &= (s[i] == '9') ;

					if (ok) for (int i = np ; i < n ; ++i) ans[i] = s[i] ;
					else {
						ans[np] = s[np] - 1 ;
						for (int i = np + 1 ; i < n ; ++i) ans[i] = '9' ;
					}
				}
			}
		}

		int st = ans[0] == '0' ;
		for (int i = st ; i < n ; ++i) printf("%c" , ans[i]) ;
		printf("\n") ;
	}

	return 0 ;
}