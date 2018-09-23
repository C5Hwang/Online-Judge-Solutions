#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 53 + 5 ;

int n , m , p , tot , list[MAX_N] , c[MAX_N] ;
int ans , inv[MAX_N] , ny[MAX_N] , g[MAX_N][MAX_N] ;

int gcd(int x , int y) {return y ? gcd(y , x % y) : x ;}

int qpow(int a , int t) {
	if (!t) return 1 ;

	int s = qpow(a , t >> 1) ;
	s = (ll)s * s % p ;
	if (t & 1) s = (ll)s * a % p ;

	return s ;
}

void init() {
	inv[0] = 1 ; ans = 0 ;
	for (int i = 1 ; i <= n ; ++i) {
		ny[i] = qpow(i , p - 2) ;
		inv[i] = (ll)inv[i - 1] * ny[i] % p ;
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

	return qpow(m , x) ;
}

void divi(int use , int last) {
	if (use == n) {
		int d = 1 ;
		for (int i = 1 ; i <= n ; ++i) {
			d = (ll)d * i % p ;
			d = (ll)d * inv[c[i]] % p ;
			d = (ll)d * qpow(ny[i] , c[i]) % p ;
		}
		d = (ll)d * cal() % p ;
		(ans += d) %= p ;

		return ;
	}

	for (int i = last ; i <= n - use ; ++i) {
		list[tot++] = i ; ++c[i] ;
		divi(use + i , i) ;
		list[--tot] = 0 ; --c[i] ;
	}
}

int main() {
	scanf("%d %d %d" , &n , &m , &p) ;

	///

	init() ;
	divi(0 , 1) ;

	ans = (ll)ans * inv[n] % p ;
	printf("%d\n" , ans) ;

	return 0 ;
}