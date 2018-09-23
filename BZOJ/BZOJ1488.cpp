#include <stdio.h>
#include <stdlib.h>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 60 + 5 , mod = 997 ;

int n , tot , ans , list[MAX_N] , c[MAX_N] ;
int g[MAX_N][MAX_N] , inv[MAX_N] , ny[MAX_N] ;

int gcd(int x , int y) {return y ? gcd(y , x % y) : x ;}

int qpow(int a , int t) {
	if (!t) return 1 ;

	int s = qpow(a , t >> 1) ;
	(s *= s) %= mod ; if (t & 1) (s *= a) %= mod ;

	return s ;
}

void init() {
	inv[0] = 1 ;
	for (int i = 1 ; i <= n ; ++i) {
		ny[i] = qpow(i , mod - 2) ;
		inv[i] = inv[i - 1] * ny[i] % mod ;
	}

	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= n ; ++j)
			g[i][j] = gcd(i , j) ;
}

int cal() {
	int x = 0 ;
	for (int i = 0 ; i < tot ; ++i) x += (list[i] >> 1) ;
	for (int i = 0 ; i < tot ; ++i)
		for (int j = i + 1 ; j < tot ; ++j)
			x += g[list[i]][list[j]] ;

	return qpow(2 , x) ;
}

void divi(int use , int last) {
	if (use == n) {
		int d = 1 ;
		for (int i = 1 ; i <= n ; ++i) {
			(d *= i) %= mod ;
			(d *= inv[c[i]]) %= mod ;
			(d *= qpow(ny[i] , c[i])) %= mod ;
		}
		(d *= cal()) %= mod ;
		(d *= inv[n]) %= mod ;
		(ans += d) %= mod ;

		return ;
	}

	for (int i = last ; i <= n - use ; ++i) {
		list[tot++] = i ; ++c[i] ;
		divi(use + i , i) ;
		list[--tot] = 0 ; --c[i] ;
	}
}

int main() {
	scanf("%d" , &n) ;

	///

	init() ;
	divi(0 , 1) ;

	printf("%d\n" , ans) ;

	return 0 ;
}