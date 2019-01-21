#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 5e4 + 10 , mod = 1000000123 ;

int n , ans , f[MAX_N] , inv[MAX_N] , jc[MAX_N] ;

inline int check(int x) {return x & 1 ? -1 : 1 ;}

int qpow(int x , int t) {
	int tmp = x , s = 1 ;
	for (; t ; t >>= 1 , tmp = (ll)tmp * tmp % mod)
		if (t & 1) s = (ll)s * tmp % mod ;

	return s ;
}

int dp(int k) {
	int tot = n / k , b = n % k ;

	f[0] = qpow(jc[n] , n) ;
	for (int i = 1 ; i <= tot ; ++i) f[i] = 0 ;
	for (int i = 1 ; i <= tot ; ++i)
		for (int j = 1 ; j <= i ; ++j) (f[i] += (ll)f[i - j] * inv[j * k] % mod) %= mod ;

	if (!b) return (mod + check(tot) * f[tot]) % mod ;

	int res = 0 ;
	for (int i = 0 ; i <= tot ; ++i) (res += (ll)f[i] * inv[(tot - i) * k + b] % mod) %= mod ;

	return (mod + check(tot + 1) * res) % mod ;
}

int main() {
	n = 50000 ;
	jc[0] = inv[0] = 1 ;
	for (int i = 1 ; i <= n ; ++i) {
		jc[i] = (ll)jc[i - 1] * i % mod ;
		inv[i] = qpow(jc[i] , mod - 2) ; inv[i] = mod - qpow(inv[i] , n) ;
	}

	///

	for (int k = 1 ; k <= n ; ++k) (ans += dp(k)) %= mod ;
	printf("%d\n" , ans) ;

	return 0 ;
}