#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 3 + 5 , mod = 1e9 + 7 ;

int n , T , A[MAX_N][MAX_N] , B[MAX_N][MAX_N] , C[MAX_N][MAX_N] ;

void times(int (*A)[MAX_N] , int (*B)[MAX_N] , int n , int m) {
	int tmp[MAX_N][MAX_N] ;

	for (int i = 0 ; i < n ; ++i)
		for (int j = 0 ; j < m ; ++j) {
			int s = 0 ;
			for (int r = 0 ; r < 3 ; ++r) s = (s + (ll)A[i][r] * B[r][j]) % mod ;
			tmp[i][j] = s ;
		}

	for (int i = 0 ; i < n ; ++i)
		for (int j = 0 ; j < m ; ++j)
			B[i][j] = tmp[i][j] ;
}

void qpow(int x) {
	if (x == 1) return ;

	qpow(x >> 1) ;
	times(C , C , 3 , 3) ;
	if (x & 1) times(B , C , 3 , 3) ;
}

int main() {
	scanf("%d" , &T) ;
	for (; T-- ;) {
		scanf("%d" , &n) ;
		if (n < 4) {printf("1\n") ; continue ;}

		for (int i = 0 ; i < 3 ; ++i)
			for (int j = 0 ; j < 3 ; ++j) A[i][j] = 0 ;
		for (int i = 0 ; i < 3 ; ++i) A[i][0] = 1 ;

		for (int i = 0 ; i < 3 ; ++i)
			for (int j = 0 ; j < 3 ; ++j) B[i][j] = 0 ;
		B[0][0] = B[0][2] = B[1][0] = B[2][1] = 1 ;
		for (int i = 0 ; i < 3 ; ++i)
			for (int j = 0 ; j < 3 ; ++j) C[i][j] = B[i][j] ;

		///

		qpow(n - 3) ;

		times(C , A , 3 , 1) ;

		printf("%d\n" , A[0][0]) ;
	}

	return 0 ;
}