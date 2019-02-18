#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1500 + 10 , mod = 1e9 + 7 ;

int T , n , p , m , k , P1 , P2 , C[MAX_N] , f[MAX_N] , A[MAX_N][MAX_N] ;

inline int MOD(int x) {return x >= mod ? x - mod : x ;}

int qpow(int x , int t) {
	int s = 1 , tmp = x ;
	for (; t ; t >>= 1 , tmp = (ll)tmp * tmp % mod)
		if (t & 1) s = (ll)s * tmp % mod ;

	return s ;
}

inline int att(int x) {
	if (x < 0 || x > k) return 0 ;
	else return f[x] ;
}

int work() {
	if (!k) {return -1 ;}
	if (!m) {
		if (k == 1) return -1 ;

		int res = 0 ;
		for (; p > 0 ; p -= k) p = std::min(p + 1 , n) , ++res ;
		return res ;
	}

	P1 = qpow(m + 1 , mod - 2) ; P2 = (ll)m * P1 % mod ;

	int mat = std::min(n , k) ; C[0] = 1 ;
	for (int i = 1 ; i <= mat ; ++i) C[i] = ((ll)C[i - 1] * qpow(i , mod - 2) % mod) * (k - i + 1) % mod ;
	for (int i = 0 ; i <= mat ; ++i) f[i] = ((ll)qpow(P1 , i) * qpow(P2 , k - i) % mod) * C[i] % mod ;

	///

	for (int i = 1 ; i <= n ; ++i) {
		for (int j = std::min(i + 1 , n) ; j ; --j)
			if (i < n) A[i][j] = ((ll)P1 * att(i + 1 - j) + (ll)P2 * att(i - j)) % mod ;
			else A[i][j] = att(i - j) ;

		A[i][n + 1] = mod - 1 ; A[i][i] = MOD(A[i][i] + mod - 1) ;
	}

	for (int i = n ; i > 1 ; --i) {
		if (!A[i][i]) return -1 ;

		int c = (ll)A[i - 1][i] * qpow(A[i][i] , mod - 2) % mod ;
		for (int j = 1 ; j <= n + 1 ; ++j)
			A[i - 1][j] = MOD(A[i - 1][j] - ((ll)c * A[i][j] % mod) + mod) ;
	}

	if (!A[1][1]) return -1 ;

	for (int i = 1 ; i <= n ; ++i) {
		for (int j = 1 ; j < i ; ++j)
			A[i][n + 1] = MOD(A[i][n + 1] - ((ll)A[i][j] * A[j][n + 1] % mod) + mod) ;
		A[i][n + 1] = (ll)A[i][n + 1] * qpow(A[i][i] , mod - 2) % mod ;
	}

	return A[p][n + 1] ;
}

int main() {
	scanf("%d" , &T) ;
	for (; T-- ;) {
		scanf("%d %d %d %d" , &n , &p , &m , &k) ;
		printf("%d\n" , work()) ;
	}

	return 0 ;
}