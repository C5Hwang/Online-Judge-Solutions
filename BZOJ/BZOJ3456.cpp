#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 52e4 + 10 , mod = 1004535809 , G = 3 ;

int rev[MAX_N] , A[MAX_N] , B[MAX_N] ;
int n , len , f[MAX_N] , h[MAX_N] , inv[MAX_N] , fac[MAX_N] , ifac[MAX_N] ;

int qpow(int a , ll t) {
	if (!t) return 1 ;

	int s = qpow(a , t >> 1) ;
	s = (ll)s * s % mod ;
	if (t & 1) s = (ll)s * a % mod ;

	return s ;
}

void fnt(int *f , int ty) {
	for (int i = 0 ; i < len ; ++i) if (i < rev[i]) std::swap(f[i] , f[rev[i]]) ;

	int phi = mod - 1 ;
	for (int L = 2 ; L <= len ; L <<= 1) {
		int wn , hf = L >> 1 ;
		if (ty == -1) wn = qpow(G , phi - phi / L) ;
		else wn = qpow(G , phi / L) ;

		for (int i = 0 ; i < len ; i += L) {
			int w = 1 ;
			for (int j = 0 ; j < hf ; ++j , w = (ll)w * wn % mod) {
				int t = (ll)f[i + j + hf] * w % mod ;
				f[i + j + hf] = (f[i + j] - t + mod) % mod ;
				f[i + j] = (f[i + j] + t) % mod ;
			}
		}
	}
}

void cdq(int x , int y) {
	if (x == y) {
		f[x] = (h[x] - ((ll)fac[x - 1] * f[x] % mod) + mod) % mod ;

		return ;
	}

	int mid = (x + y) >> 1 ;
	cdq(x , mid) ;

	///

	len = (mid - x) + (y - x - 1) ;
	int tmp = len , p = 0 ;
	for (len = 1 ; len <= tmp ; ++p , len <<= 1) ;

	for (int i = 0 ; i < len ; ++i) A[i] = B[i] = 0 ;
	for (int i = x ; i <= mid ; ++i) A[i - x] = (ll)f[i] * ifac[i - 1] % mod ;
	for (int i = 0 ; i < y - x ; ++i) B[i] = (ll)h[i + 1] * ifac[i + 1] % mod ;

	rev[0] = 0 ;
	for (int i = 1 ; i < len ; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (p - 1)) ;

	///

	fnt(A , 1) ; fnt(B , 1) ;
	for (int i = 0 ; i < len ; ++i) A[i] = (ll)A[i] * B[i] % mod ;
	fnt(A , -1) ;
	for (int i = 0 ; i < len ; ++i) A[i] = (ll)A[i] * inv[len] % mod ;

	for (int i = mid + 1 ; i <= y ; ++i) (f[i] += A[i - 1 - x]) %= mod ;

	///

	cdq(mid + 1 , y) ;
}

int main() {
	scanf("%d" , &n) ;

	///

	int m = n << 2 ;
	inv[0] = ifac[0] = fac[0] = 1 ;
	for (int i = 1 ; i <= m ; ++i) inv[i] = qpow(i , mod - 2) ;
	for (int i = 1 ; i <= m ; ++i) {
		fac[i] = (ll)fac[i - 1] * i % mod ;
		ifac[i] = (ll)ifac[i - 1] * inv[i] % mod ;
	}

	h[1] = 1 ;
	for (int i = 2 ; i <= n ; ++i) {
		ll tmp = (ll)i * (i - 1) >> 1 ;
		h[i] = qpow(2 , tmp) ;
	}

	///

	cdq(1 , n) ;

	printf("%d\n" , f[n]) ;

	return 0 ;
}