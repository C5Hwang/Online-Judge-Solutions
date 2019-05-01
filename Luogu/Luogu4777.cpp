#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 ;

int n ;
ll a[MAX_N] , b[MAX_N] ;

ll times(ll a , ll b , ll mod) {
	a = ((a % mod) + mod) % mod ;
	if (b < 0) a = (mod - a) % mod , b = -b ;

	ll s = 0 , tmp = a ;
	for (; b ; b >>= 1 , (tmp <<= 1) %= mod)
		if (b & 1) (s += tmp) %= mod ;

	return s ;
}

ll exgcd(ll a , ll b , ll &x , ll &y) {
	if (!b) {x = 1 ; y = 0 ; return a ;}

	ll x1 , y1 , d = exgcd(b , a % b , x1 , y1) ;
	x = y1 ; y = x1 - (a / b) * y1 ;

	return d ;
}

int main() {
	scanf("%d" , &n) ;
	for (int i = 1 ; i <= n ; ++i) scanf("%lld %lld" , &b[i] , &a[i]) ;

	///

	ll M = b[1] , A = a[1] ;
	for (int i = 2 ; i <= n ; ++i) {
		ll x , y , d = exgcd(M , b[i] , x , y) , nM = M / d * b[i] ;

		x = times(x , (a[i] - A) / d , nM) ;
		A = (A + times(x , M , nM)) % nM ; M = nM ;
	}

	printf("%lld\n" , A) ;

	return 0 ;
}