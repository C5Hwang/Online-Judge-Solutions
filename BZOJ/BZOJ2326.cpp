#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ull unsigned long long 

const int MAX_N = 5 ;

ull L , R , n , m ;
ull f[MAX_N][MAX_N] , A[MAX_N][MAX_N] , C[MAX_N][MAX_N] , temp[MAX_N][MAX_N] ;

void times(ull (*A)[MAX_N] , ull (*B)[MAX_N] , int x , int y , int r) {
	for (int i = 0 ; i < x ; ++i)
		for (int j = 0 ; j < y ; ++j) {
			temp[i][j] = 0 ;
			for (int k = 0 ; k < r ; ++k)
				temp[i][j] = (temp[i][j] + (A[i][k] * B[k][j]) % m) % m ; 
		}

	for (int i = 0 ; i < x ; ++i)
		for (int j = 0 ; j < y ; ++j)
			A[i][j] = temp[i][j] ;
}

void power(ull n , int x , int y , int r) {
	if (n == 1) return ;

	power(n >> 1 , x , y , 3) ;
	times(A , A , x , y , 3) ;
	if (n % 2) times(A , C , x , y , 3) ;
}	

int main() {
	scanf("%llu %llu" , &n , &m) ;

	///

	for (int i = 0 ; i < 3 ; ++i)
		for (int j = 0 ; j < 3 ; ++j)
			if (i >= j) C[i][j] = 1 ;
			else C[i][j] = 0 ;
	f[0][0] = 0 ; f[0][1] = 0 ; f[0][2] = 1 ;

	///

	L = 1 ; R = 9 ;
	for (; L <= n ; L *= 10 , R = L * 10 - 1) {
		C[0][0] = (R + 1) % m ;
		ull len = std::min(n , R) - L + 1 ;

		for (int i = 0 ; i < 3 ; ++i)
			for (int j = 0 ; j < 3 ; ++j)
				A[i][j] = C[i][j] ;
		power(len , 3 , 3 , 3) ;
		times(f , A , 1 , 3 , 3) ;
	}
	printf("%llu\n" , f[0][0]) ;

	return 0 ;
}
