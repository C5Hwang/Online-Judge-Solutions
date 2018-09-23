#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 , N = (119 << 23) + 1 , G = 3 ;

int Q , T , n , m , f[MAX_N] , rev[MAX_N] ;

int qpow(int a , int t) {
	if (!t) return 1 ;

	int s = qpow(a , t >> 1) ;
	s = (ll)s * s % N ; if (t & 1) s = (ll)s * a % N ;

	return s ;
}

void fnt(int *f , int ty) {
	for (int i = 0 ; i < n ; ++i) if (i < rev[i]) std::swap(f[i] , f[rev[i]]) ;

	for (int L = 2 ; L <= n ; L <<= 1) {
		int phi = N - 1 , hf = L >> 1 , wn ;

		if (ty == 1) wn = qpow(G , phi / L) ;
		else wn = qpow(G , phi - phi / L) ;

		for (int i = 0 ; i < n ; i += L)
			for (int j = 0 , w = 1 ; j < hf ; ++j , w = (ll)w * wn % N) {
				int tmp = (ll)f[i + j + hf] * w % N ;
				f[i + j + hf] = (f[i + j] - tmp + N) % N ;
				(f[i + j] += tmp) %= N ;
			}
	}

	if (ty == -1) {
		int ny = qpow(n , N - 2) ;
		for (int i = 0 ; i < n ; ++i) f[i] = (ll)f[i] * ny % N ;
	}
}

void times() {
	m = n << 1 ; n = 1 ;
	int L = 0 ;	for (; n <= m ; n <<= 1 , ++L) ;
	for (int i = 1 ; i < n ; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1)) ;

	fnt(f , 1) ;
	for (int i = 0 ; i < n ; ++i) f[i] = (ll)f[i] * f[i] % N ;
	fnt(f , -1) ;

	for (int i = 0 ; i <= m ; ++i)
		if (f[i] >= 10) {f[i + 1] += f[i] / 10 ; f[i] %= 10 ;}

	for (++m ; f[m] ; ++m) if (f[m] >= 10) {f[m + 1] += f[m] / 10 ; f[m] %= 10 ;}

	n = m - 1 ;
}

void red(int *f , int a) {
	f[0] -= a ;

	for (int i = 0 ; i <= n ; ++i) if (f[i] < 0) f[i] += 10 , --f[i + 1] ;
	if (!f[n]) --n ;
}

void t2() {
	for (int i = 0 ; i <= n ; ++i) f[i] = f[i] * 2 ;
	for (int i = 0 ; i <= n ; ++i) if (f[i] >= 10) {f[i + 1] += f[i] / 10 ; f[i] %= 10 ;}
	if (f[n + 1]) ++n ;
}

void d3() {
	int lf = 0 ;
	for (int i = n ; i >= 0 ; --i , lf *= 10) {
		lf += f[i] ;
		f[i] = lf / 3 ; lf %= 3 ;
	}

	if (!f[n]) --n ;
}

void find(int t) {
	if (!t) {
		memset(f , 0 , sizeof(f)) ;
		f[0] = 1 ; n = 0 ;

		return ;
	}

	find(t >> 1) ;
	times() ; if (t & 1) t2() ;
}

int main() {
	scanf("%d" , &Q) ;
	for (; Q-- ;) {
		scanf("%d" , &T) ;

		///

		find(T + 1) ;
		if (T & 1) red(f , 1) ;
		else red(f , 2) ;

		///

		d3() ;

		for (int i = n ; i >= 0 ; --i) printf("%d" , f[i]) ;
		printf("\n") ;
	}

	return 0 ;
}