#include <stdio.h>
#include <stdlib.h>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 100 + 10 ;

int n , L , f[MAX_N] ;

int main() {
	f[1] = 1 ; f[2] = 1 ;
	for (L = 2 ; ;) {
		int tmp = (f[L] + f[L - 1]) % 5 ;

		bool ok = 0 ;
		for (int i = 1 ; i < L && !ok ; ++i) if (f[i] == f[L] && f[i + 1] == tmp) ok = 1 ;

		if (ok) {--L ; break ;}
		else f[++L] = tmp ;
	}

	///

	scanf("%d" , &n) ;
	for (int i = 0 ; i < n ; ++i) {
		int a ; scanf("%d" , &a) ;
		a = (a - 1) % L + 1 ;

		printf("%d\n" , f[a]) ;
	}

	return 0 ;
}