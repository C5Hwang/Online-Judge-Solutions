#include <bitset>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAX_N = 2e3 + 10 ;

std::bitset<MAX_N> f[MAX_N] ;

int n ;
char s[MAX_N] ;

int main() {
	scanf("%d" , &n) ;
	for (int i = 1 ; i <= n ; ++i) {
		scanf("%s" , s) ;

		for (int j = 1 ; j <= n ; ++j)
			if (i == j) f[i][j] = 1 ;
			else if (s[j - 1] == '1') f[i][j] = 1 ;
	}

	///

	for (int j = 1 ; j <= n ; ++j)
		for (int i = 1 ; i <= n ; ++i)
			if (f[i][j]) f[i] |= f[j] ;

	int sum = 0 ;
	for (int i = 1 ; i <= n ; ++i)
		sum += f[i].count() ;

	printf("%d\n" , sum) ;

	return 0 ;
}
