#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 5e5 + 10 , mod = 19491001 , G = 7 ;

int n , k , d , jc[MAX_N] , inv[MAX_N] ;

inline int qpow(int a , int t) {
	int s = 1 , tmp = a ;
	for (; t ; t >>= 1 , tmp = (ll)tmp * tmp % mod)
		if (t & 1) s = (ll)s * tmp % mod ;

	return s ;
}

inline int count(int n , int m) {
	int p = n - m ;

	return (ll)jc[n] * inv[m] % mod * inv[p] % mod ;
}

int main() {
	scanf("%d %d %d" , &n , &k , &d) ;

	jc[0] = 1 ;
	for (int i = 1 ; i <= k ; ++i) jc[i] = (ll)jc[i - 1] * i % mod ;
	inv[k] = qpow(jc[k] , mod - 2) ;
	for (int i = k - 1 ; i >= 0 ; --i) inv[i] = (ll)inv[i + 1] * (i + 1) % mod ;

	///

	if (d == 1) printf("%d\n" , qpow(k , n)) ;
	else if (d == 2) {
		int g1 = 1 , g2 = mod - 1 , res = 0 , ny = qpow(qpow(2 , mod - 2) , k) ;

		for (int i = 0 ; i <= k ; ++i) {
			int j = k - i , s = ((ll)g1 * i + (ll)g2 * j) % mod , C = count(k , i) ;

			s = (ll)qpow(s , n) * C % mod ;
			(res += s) %= mod ;
		}
		res = (ll)res * ny % mod ;

		printf("%d\n" , res) ;
	}
	else {
		int phi = mod - 1 , g1 = 1 , g2 = qpow(G , phi / 3) , g3 = (ll)g2 * g2 % mod , ny = qpow(qpow(3 , mod - 2) , k) , res = 0 ;

		for (int i = 0 ; i <= k ; ++i)
			for (int j = 0 ; j <= k ; ++j) {
				if (i + j > k) break ;
				int l = k - i - j , s = ((ll)g1 * i + (ll)g2 * j + (ll)g3 * l) % mod , C = (ll)count(k , i) * count(k - i , j) % mod ;

				s = (ll)qpow(s , n) * C % mod ;
				(res += s) %= mod ;
			}
		res = (ll)res * ny % mod ;

		printf("%d\n" , res) ;
	}

	return 0 ;
}