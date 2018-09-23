#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long

const int MAX_N = 32e3 + 10 , mod = 1004535809 , G = 3 ;

int f[MAX_N] , base[MAX_N] , rev[MAX_N] ;
int T , P , q , n , inv , a[MAX_N] , ind[MAX_N] ;

///

int qpow(int a , int t , int P) {
	if (t == 1) return a ;

	int s = qpow(a , t >> 1 , P) ;
	s = (ll)s * s % P ;
	if (t & 1) s = (ll)s * a % P ;

	return s ;
}

int findG() {
	int tmp[30] , cnt = 0 , m = P - 1 ;

	for (int i = 2 ; i * i <= m ; ++i) {
		bool ok = 0 ;
		for (; !(m % i) ; m /= i , ok = 1) ;

		if (ok) tmp[cnt++] = i ;
	}
	if (m > 1) tmp[cnt++] = m ;

	for (int i = 2 ; ; ++i) {
		bool ok = 1 ;
		for (int j = 0 ; j < cnt && ok ; ++j) {
			int t = qpow(i , (P - 1) / tmp[j] , P) ;
			if (t == 1) ok = 0 ;
		}

		if (ok) return i ;
	}
}

///

void fnt(int *a , int ty) {
	for (int i = 0 ; i < n ; ++i) if (i < rev[i]) std::swap(a[i] , a[rev[i]]) ;

	for (int L = 2 ; L <= n ; L <<= 1) {
		int hf = L >> 1 , gn ;
		if (ty) gn = qpow(G , mod - 1 - (mod - 1) / L , mod) ;
		else gn = qpow(G , (mod - 1) / L , mod) ;

		for (int i = 0 ; i < n ; i += L) {
			int g = 1 ;
			for (int j = 0 ; j < hf ; ++j , g = (ll)g * gn % mod) {
				int t = (ll)g * a[i + j + hf] % mod ;
				a[i + j + hf] = (a[i + j] - t + mod) % mod ;
				(a[i + j] += t) %= mod ;
			}
		}
	}
}

void times(int ty) {
	fnt(f , 1) ;
	int *g = ty ? base : f ;
	for (int i = 0 ; i < n ; ++i) f[i] = (ll)f[i] * g[i] % mod ;
	fnt(f , 0) ;

	for (int i = 0 ; i < n ; ++i) f[i] = (ll)f[i] * inv % mod ;
	for (int i = P - 1 ; i < n ; ++i) {(f[i - P + 1] += f[i]) %= mod ; f[i] = 0 ;}
}

void qfnt(int t) {
	if (t == 1) return ;

	qfnt(t >> 1) ; times(0) ;
	if (t & 1) times(1) ;
}

///

int main() {
	scanf("%d %d %d %d" , &T , &P , &q , &n) ;
	for (int i = 0 ; i < n ; ++i) scanf("%d" , &a[i]) ;

	///

	ind[1] = 0 ;
	int g = findG() ;
	for (int i = 1 , t = g ; i < P - 1 ; ++i , (t *= g) %= P) ind[t] = i ;

	q = ind[q] ;
	for (int i = 0 ; i < n ; ++i) if (a[i]) ++f[ind[a[i]]] ;

	///

	int L = 0 , m = (P - 2) << 1 ;
	for (n = 1 ; n <= m ; n <<= 1 , ++L) ;

	for (int i = 1 ; i < n ; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1)) ;
	for (int i = 0 ; i < n ; ++i) base[i] = f[i] ;
	inv = qpow(n , mod - 2 , mod) ;

	///

	fnt(base , 1) ;
	qfnt(T) ;

	printf("%d\n" , f[q]) ;

	return 0 ;
}