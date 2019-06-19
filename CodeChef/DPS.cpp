#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e4 + 10 ;

char s[MAX_N] ;
int T , n , cnt[30] ;

int main() {
	scanf("%d" , &T) ;
	for (; T-- ;) {
		scanf("%s" , s) ; n = strlen(s) ;

		for (int i = 0 ; i < 26 ; ++i) cnt[i] = 0 ;
		for (int i = 0 ; i < n ; ++i) ++cnt[s[i] - 'a'] ;

		///

		int sum = 0 ;
		for (int i = 0 ; i < 26 ; ++i) sum += cnt[i] % 2 ;

		if (n & 1) {
			if (sum == 1 || sum == 3) printf("DPS\n") ;
			else printf("!DPS\n") ;
		}
		else if (sum == 2) printf("DPS\n") ;
		else printf("!DPS\n") ;
	}

	return 0 ;
}