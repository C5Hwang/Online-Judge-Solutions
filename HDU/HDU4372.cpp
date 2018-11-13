#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int N = 2e3 , MAX_N = 2e3 + 10 , mod = 1e9 + 7 ;

int T , n , f , b , C[MAX_N][MAX_N] , S[MAX_N][MAX_N] ;

int main() {
	S[0][0] = C[0][0] = 1 ;
	for (int i = 1 ; i <= N ; ++i) {
		S[i][0] = 0 ; C[i][0] = 1 ;

		for (int j = 1 ; j <= i ; ++j) {
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod ;
			S[i][j] = (S[i - 1][j - 1] + (ll)(i - 1) * S[i - 1][j]) % mod ;
		}
	}

	///

	scanf("%d" , &T) ;
	for (; T-- ;) {
		scanf("%d %d %d" , &n , &f , &b) ;
		--f ; --b ;

		if (f + b + 1 > n) {printf("0\n") ; continue ;}

		int p1 = C[f + b][f] , p2 = S[n - 1][f + b] , ans = (ll)p1 * p2 % mod ;

		printf("%d\n" , ans) ;
	}

	return 0 ;
}