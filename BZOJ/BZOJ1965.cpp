#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

ll n , m , L ;

ll qtime(ll a , ll t , ll P) {
	int s = 0 ;

	for (; t ; t >>= 1 , (a <<= 1) %= P)
		if (t & 1) (s += a) %= P ;

	return s ;
}

ll qpow(ll a , ll t , ll P) {
	int s = 1 ;

	for (; t ; t >>= 1 , a = qtime(a , a , P))
		if (t & 1) s = qtime(s , a , P) ;

	return s ;
}

int main() {
	scanf("%lld %lld %lld" , &n , &m , &L) ;
	ll a = (n + 2) >> 1 ;

	printf("%lld\n" , qtime(qpow(a , m , n + 1) , L , n + 1)) ;

	return 0 ;
}