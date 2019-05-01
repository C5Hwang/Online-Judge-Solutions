#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 100 + 10 , mod = 1e9 + 7 ;

ll k ;
int n , A[MAX_N][MAX_N] , T[MAX_N][MAX_N] , S[MAX_N][MAX_N] ;

void times(int (*A)[MAX_N] , int (*B)[MAX_N]) {
	for (int i = 0 ; i < n ; ++i)
		for (int j = 0 ; j < n ; ++j) {
			int t = 0 ;
			for (int r = 0 ; r < n ; ++r) (t += (ll)A[i][r] * B[r][j] % mod) %= mod ;
			T[i][j] = t ;
		}

	for (int i = 0 ; i < n ; ++i)
		for (int j = 0 ; j < n ; ++j)
			A[i][j] = T[i][j] ;
}

void qpow(ll t) {
	for (int i = 0 ; i < n ; ++i)
		for (int j = 0 ; j < n ; ++j)
			if (i == j) S[i][j] = 1 ;
			else S[i][j] = 0 ;

	for (; t ; t >>= 1 , times(A , A))
		if (t & 1) times(S , A) ;
}

int main() {
	scanf("%d %lld" , &n , &k) ;
	for (int i = 0 ; i < n ; ++i)
		for (int j = 0 ; j < n ; ++j) scanf("%d" , &A[i][j]) ;

	qpow(k) ;

	for (int i = 0 ; i < n ; ++i , printf("\n"))
		for (int j = 0 ; j < n ; ++j) printf("%d " , S[i][j]) ;

	return 0 ;
}