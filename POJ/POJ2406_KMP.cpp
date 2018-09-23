#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAX_N = 1000000 + 10 ;

char st[MAX_N] ;
int n , next[MAX_N] ;

int main() {
	scanf("%s" , st) ;
	while (st[0] != '.') {
		n = strlen(st) ;
		
		///

		int k = 0 ; next[0] = 0 ;
		for (int i = 1 ; i < n ; ++i) {
			while (k > 0 && st[i] != st[k]) k = next[k] ;

			next[i] = k ;
			if (st[i] == st[k]) ++k ;
		}

		int len = n - 1 - next[n - 1] ;
		if (n % len == 0) printf("%d\n" , n / len) ;
		else printf("1\n") ;

		scanf("%s" , st) ;
	}
}
