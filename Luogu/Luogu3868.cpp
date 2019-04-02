#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 10 + 5 ;

ll M ;
int n , a[MAX_N] , b[MAX_N] ;

inline ll times(ll a , ll t) {
	ll tmp = a , sum = 0 ;
	for (; t ; t >>= 1 , (tmp <<= 1) %= M)
		if (t & 1) (sum += tmp) %= M ;

	return sum ;
}

void exgcd(ll a , ll b , ll &x , ll &y) {
	if (!b) {x = 1 ; y = 0 ; return ;}

	ll x1 , y1 ;
	exgcd(b , a % b , x1 , y1) ;
	x = y1 ; y = x1 - (a / b) * y1 ;
}

int main() {
	scanf("%d" , &n) ; M = 1 ;
	for (int i = 0 ; i < n ; ++i) scanf("%d" , &a[i]) ;
	for (int i = 0 ; i < n ; ++i) {
		scanf("%d" , &b[i]) ;
		M *= b[i] ; a[i] = ((a[i] % b[i]) + b[i]) % b[i] ;
	}

	///

	ll ans = 0 ;
	for (int i = 0 ; i < n ; ++i) {
		ll x , y , Mi = M / b[i] ;
		exgcd(Mi , b[i] , x , y) ; x = ((x % b[i]) + b[i]) % b[i] ;

		ans = (ans + times(times(a[i] , Mi) , x)) % M ;
	}

	printf("%lld\n" , ans) ;

	return 0 ;
}