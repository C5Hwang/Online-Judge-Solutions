#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int lim = 1e6 , MAX_N = 1e6 + 10 ;

ll n , m ;
bool vis[MAX_N] ;
int tot , mu[MAX_N] , pri[MAX_N] ;

void init() {
	int n = std::min(m , (ll)lim) ;

	mu[1] = 1 ;
	for (int i = 2 ; i <= n ; ++i) {
		if (!vis[i]) {mu[i] = -1 ; pri[tot++] = i ;}

		for (int j = 0 ; j < tot ; ++j) {
			int tmp = i * pri[j] ;
			if (tmp > n) break ;
			vis[tmp] = 1 ;

			if (i % pri[j]) mu[tmp] = -mu[i] ;
			else {mu[tmp] = 0 ; break ;}
		}
	}
}

ll calc(ll n) {
	ll sum = 0 ;
	for (ll x = 1 ; x * x * x <= n ; ++x) {
		for (ll y = x + 1 ; x * y * y <= n ; ++y)
			sum += (n / (x * y) - y) * 6 + 3 ;
		sum += (n / (x * x) - x) * 3 + 1 ;
	}

	return sum ;
}

ll count(ll n) {
	ll res = 0 ;
	for (ll i = 1 ; i * i <= n ; ++i)
		if (mu[i]) res += mu[i] * calc(n / (i * i)) ;

	return (res + n) >> 1 ;
}

int main() {
	scanf("%lld %lld" , &n , &m) ;
	init() ;
	printf("%lld\n" , count(m) - count(n - 1)) ;

	return 0 ;
}