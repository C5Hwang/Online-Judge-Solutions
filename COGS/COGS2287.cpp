#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 4e5 + 10 , mod = (119 << 23) + 1 , G = 3 ;

int n , m , inv[MAX_N] , pw[MAX_N] , ipw[MAX_N] , rev[MAX_N] , f[MAX_N] ;

int qpow(int x , int t) {
	int s = 1 , tmp = x ;

	for (; t ; t >>= 1 , tmp = (ll)tmp * tmp % mod)
		if (t & 1) s = (ll)s * tmp % mod ;

	return s ;
}

void fnt(int *f , int ty) {
	for (int i = 0 ; i < n ; ++i) if (i < rev[i]) std::swap(f[i] , f[rev[i]]) ;

	for (int L = 2 ; L <= n ; L <<= 1) {
		int hf = L >> 1 , phi = mod - 1 , gn ;
		if (ty > 0) gn = qpow(G , phi / L) ;
		else gn = qpow(G , phi - phi / L) ;

		for (int i = 0 ; i < n ; i += L) {
			int g = 1 ;
			for (int j = 0 ; j < hf ; ++j , g = (ll)g * gn % mod) {
				int tmp = (ll)f[i + j + hf] * g % mod ;

				f[i + j + hf] = (f[i + j] + mod - tmp) % mod ;
				(f[i + j] += tmp) %= mod ;
			}
		}
	}
}

int main() {
	freopen("crazy_robot.in" , "r" , stdin) ;
	freopen("crazy_robot.out" , "w" , stdout) ;

	scanf("%d" , &n) ;

	for (int i = 1 ; i <= n ; ++i) inv[i] = qpow(i , mod - 2) ;
	pw[0] = ipw[0] = 1 ;
	for (int i = 1 ; i <= n ; ++i) pw[i] = (ll)pw[i - 1] * i % mod ;
	for (int i = 1 ; i <= n ; ++i) ipw[i] = (ll)ipw[i - 1] * inv[i] % mod ;

	///

	f[0] = 1 ;
	for (int i = 2 ; i <= n ; i += 2) {
		int j = i >> 1 , C1 = (ll)pw[i] * ipw[j] % mod , C2 = (ll)pw[i] * ipw[j - 1] % mod ;
		C1 = (ll)C1 * ipw[i - j] % mod ; C2 = (ll)C2 * ipw[i - j + 1] % mod ;

		f[i] = (C1 + mod - C2) % mod ;
		f[i] = (ll)f[i] * ipw[i] % mod ;
	}

	m = n ;
	n = 1 ; int L = 0 ;
	for (; n <= (m << 1) ; n <<= 1 , ++L) ;
	for (int i = 1 ; i < n ; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1)) ;

	fnt(f , 1) ;
	for (int i = 0 ; i < n ; ++i) f[i] = (ll)f[i] * f[i] % mod ;
	fnt(f , -1) ;

	int ans = 0 , ny = qpow(n , mod - 2) ;
	for (int i = 0 ; i <= m ; i += 2) {
		f[i] = (ll)f[i] * ny % mod ;
		f[i] = (ll)f[i] * pw[i] % mod ;

		int C = ((ll)pw[m] * ipw[i] % mod) * ipw[m - i] % mod , tmp = (ll)C * f[i] % mod ;
		(ans += tmp) %= mod ;
	}

	printf("%d\n" , ans) ;

	fclose(stdin) ; fclose(stdout) ;

	return 0 ;
}