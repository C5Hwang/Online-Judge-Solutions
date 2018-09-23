#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long 

const int MAX_C = 100 + 10 ;

struct data {
    int num , tot ;
}list[MAX_C] ;

int cnt ;
ll n , k ;

ll count(ll a) {
    ll sum = 0 , m = a ;
    for (; ;) {
		sum += n / a ;
		if ((double)a * m > n) break ;
		else a *= m ;
	}

    return sum ;
}

int main() {
    scanf("%lld %lld" , &n , &k) ;
	cnt = 0 ;

	for (ll i = 2 ; i * i <= k ; ++i) {
		ll t = 0 ;
		for (; !(k % i) ; ++t , k /= i) ;
		if (t) list[cnt++] = (data){i , t} ;
	}
	if (k > 1) list[cnt++] = (data){k , 1} ;

	///

	ll ans = -1 ;
	for (int i = 0 ; i < cnt ; ++i) {
		ll temp = count(list[i].num) / list[i].tot ;

		if (ans == -1) ans = temp ;
		else ans = std::min(ans , temp) ;
	}
	printf("%lld\n" , ans) ;

    return 0 ;
}
