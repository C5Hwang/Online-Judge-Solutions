#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define ldb long double
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const ll lim = 1LL << 31 ;
const int MAX_N = 50 + 5 , pri[3] = {2 , 7 , 61} ;

int tot ;
ll n , ans , num[MAX_N] ;

bool cmp(ll a , ll b) {return a > b ;}

ll times(ll a , ll b , ll mod) {
	ll tmp = (ll)((ldb)a * b / mod + 0.5) ;

	return ((a * b - tmp * mod) % mod + mod) % mod ;
}

ll qpow(ll a , ll t , ll mod) {
	ll sum = 1 , tmp = a ;
	for (; t ; t >>= 1 , tmp = times(tmp , tmp , mod))
		if (t & 1) sum = times(sum , tmp , mod) ;

	return sum ;
}

bool check(ll x) {
	if (x == 2 || x == 7 || x == 61) return 1 ;

	ll u = x - 1 , t = 0 ;
	for (; !(u & 1) ; u >>= 1 , ++t) ;

	for (int k = 0 ; k < 3 ; ++k) {
		ll a = qpow(pri[k] , u , x) ;

		for (int i = 0 ; i < t ; ++i) {
			ll b = times(a , a , x) ;
			if (b == 1 && a != 1 && a != x - 1) return 0 ;
			a = b ;
		}
		if (a != 1) return 0 ;
	}

	return 1 ;
}

void find(int p , ll lef , ll res) {
	if (res > lim) return ;
	if (lef == 1) {ans = ans ? std::min(ans , res) : res ; return ;}
	if (p == tot) return ;

	find(p + 1 , lef , res) ;

	ll a = num[p] ;
	if (lef % (a - 1)) return ;

	lef /= (a - 1) ;
	for (; !(lef % a) ; lef /= a) ;
	find(p + 1 , lef , res / (a - 1) * a) ;
}

int main() {
	scanf("%lld" , &n) ;
	for (ll i = 1 ; i * i <= n ; ++i) {
		if (n % i) continue ;

		ll j = n / i ;
		if (check(i + 1)) num[tot++] = i + 1 ;
		if (i != j && check(j + 1)) num[tot++] = j + 1 ;
	}

	///

	std::sort(num + 0 , num + tot , cmp) ;
	find(0 , n , n) ;

	if (!ans) printf("-1\n") ;
	else printf("%lld\n" , ans) ;

	return 0 ;
}