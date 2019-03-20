#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e6 + 10 , mod = 1e9 + 7 ;

char s[MAX_N] ;
int T , n , fail[MAX_N] , dep[MAX_N] ;

int main() {
	scanf("%d" , &T) ;
	for (; T-- ;) {
		scanf("%s" , s) ; n = strlen(s) ;
		for (int i = n ; i ; --i) s[i] = s[i - 1] ;

		///

		fail[0] = -1 ; dep[0] = 0 ;
		for (int i = 1 ; i <= n ; ++i) {
			int p = fail[i - 1] ;
			for (; p >= 0 && s[p + 1] != s[i] ; p = fail[p]) ;

			if (p >= 0) fail[i] = p + 1 ;
			else fail[i] = 0 ;
			dep[i] = dep[fail[i]] + 1 ;
		}

		int p = 0 , ans = 1 ;
		for (int i = 2 ; i <= n ; ++i) {
			for (; (p >= 0 && s[p + 1] != s[i]) || (p >= 0 && ((p + 1) << 1) > i) ; p = fail[p]) ;

			if (p >= 0) ++p ;
			else p = 0 ;

			ans = (ll)ans * (dep[p] + 1) % mod ;
		}
		printf("%d\n" , ans) ;
	}

	return 0 ;
}
