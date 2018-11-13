#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int N = 100 , MAX_N = 100 + 10 , mod = 20090126 ;

int T , n ;
int S[MAX_N][MAX_N] , ans[MAX_N] ;

int main() {
	S[0][0] = 1 ;
	for (int i = 1 ; i <= N ; ++i)
		for (int j = 1 , t = 1 ; j <= N ; ++j , t = (ll)t * j % mod) {
			S[i][j] = (S[i - 1][j - 1] + (ll)j * S[i - 1][j]) % mod ;

			int tmp = (ll)S[i][j] * t % mod ;
			(ans[i] += tmp) %= mod ;
		}

	///

	scanf("%d" , &T) ;
	for (; T-- ;) {
		scanf("%d" , &n) ;
		printf("%d\n" , ans[n]) ;
	}

	return 0 ;
}