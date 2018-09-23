#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_L = 500 + 10 , mod = 1e4 + 7 , np = 1668 ;

char s[MAX_L] ;
int n , len , ans ;

int main() {
	scanf("%s" , s) ;

	//

	len = strlen(s) ;
	for (int i = 0 ; i < len ; ++i) {
		(n *= 10) %= mod ;
		(n += s[i] - '0') %= mod ;
	}

	int n1 = (n + 1) % mod , n2 = (n1 + 1) % mod ;
	ans = (((n * n1) % mod * n2) % mod * np) % mod ;

	printf("%d\n" , ans) ;

	return 0 ;
}