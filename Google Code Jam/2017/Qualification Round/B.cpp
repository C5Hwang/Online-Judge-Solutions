#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAX_L = 18 + 10 ;

int len ;
char st[MAX_L] , s[MAX_L] ;

void fill(int l) {
	for (int i = l ; i < len ; ++i) s[i] = '9' ;
}

bool check(int l , int num) {
	if (l >= len) return 1 ;
	if (l > 0 && s[l - 1] > num) return 0 ;

	s[l] = num ;
	if (st[l] < num) return 0 ;
	else if (st[l] > num) {fill(l + 1) ; return 1 ;}

	for (int i = '9' ; i >= '0' ; --i)
		if (check(l + 1 , i)) return 1 ;

	return 0 ;
}

int main() {
	freopen("input.txt" , "r" , stdin) ;
	freopen("output.txt" , "w" , stdout) ;

	int T , caseNUM = 1 ; scanf("%d" , &T) ;
	for (; T-- ; ++caseNUM) {
		scanf("%s" , st) ;
		len = strlen(st) ;

		///

		bool getans = 0 ;
		for (int i = '9' ; i >= '1' && !getans ; --i)
			if (check(0 , i)) getans = 1 ;
		if (!getans) --len , fill(0) ;

		///

		printf("Case #%d: " , caseNUM) ;
		for (int i = 0 ; i < len ; ++i)
			printf("%c" , s[i]) ;
		printf("\n") ;
	}

	return 0 ;
}
