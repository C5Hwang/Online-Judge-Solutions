#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int mod = 1e9 + 7 ;

int T ;
ll n , m , k , ans ;

inline int qpow(int a , int t) {
	int s = 1 , tmp = a ;
	for (; t ; t >>= 1 , tmp = (ll)tmp * tmp % mod)
		if (t & 1) s = (ll)s * tmp % mod ;

	return s ;
}

int main() {
	scanf("%d" , &T) ;
	int ny = qpow(2 , mod - 2) ;

	for (; T-- ;) {
		scanf("%lld %lld" , &k , &n) ;
		--n ; --k ; m = n / k ;

		///

		n %= mod ; m %= mod ; k %= mod ;
		ans = (n + m * n - ((m * m + m) % mod * ny % mod) * k) % mod ;
		(ans += mod) %= mod ;

		printf("%lld\n" , ans) ;
	}

	return 0 ;
}