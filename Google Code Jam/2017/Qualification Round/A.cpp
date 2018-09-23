#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAX_N = 1000 + 10 ;

int n , k ;
char s[MAX_N] ;

int main() {
	int T , caseNUM = 1 ; scanf("%d" , &T) ;
	for (; T-- ; ++caseNUM) {
		scanf("%s %d" , s , &k) ;

		int i , len = strlen(s) , res = 0 ;
		for (i = 0 ; i + k <= len ; ++i) {
			if (s[i] == '+') continue ;

			++res ;
			for (int j = i ; j < i + k ; ++j)
				s[j] = s[j] == '+' ? '-' : '+' ;
		}

		///

		bool ans = 1 ;
		for (; i < len && ans ; ++i)
			if (s[i] == '-') ans = 0 ;

		printf("Case #%d: " , caseNUM) ;
		if (!ans) printf("IMPOSSIBLE\n") ;
		else printf("%d\n" , res) ;
	}

	return 0 ;
}
