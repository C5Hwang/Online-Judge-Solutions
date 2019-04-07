#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int lim = 5e6 , MAX_N = 5e6 + 10 , mod = 1e9 + 7 ;

ll n ;
int tot , pri[MAX_N] ;
int phi[MAX_N] , sum[MAX_N] , ans[MAX_N] ;

void init() {
	int m = std::min((ll)lim , n) ;

	phi[1] = sum[1] = 1 ;
	for (int i = 2 ; i <= m ; ++i) {
		if (!phi[i]) {phi[i] = i - 1 ; pri[tot++] = i ;}

		for (int j = 0 ; j < tot ; ++j) {
			int tmp = i * pri[j] ;
			if (tmp > m) break ;

			if (i % pri[j]) phi[tmp] = phi[i] * (pri[j] - 1) ;
			else {phi[tmp] = phi[i] * pri[j] ; break ;}
		}

		sum[i] = (sum[i - 1] + phi[i]) % mod ;
	}
}

int getsum(ll x) {
	if (x <= lim) return sum[x] ;
	if (ans[n / x]) return ans[n / x] ;

	int sum = (x % mod) * ((x + 1) % mod) % mod * ((mod + 1) >> 1) % mod ;
	for (ll L = 2 ; L <= x ;) {
		ll t = x / L , R = x / t ;

		sum = (sum + mod - (R - L + 1) % mod * getsum(t) % mod) % mod ; L = R + 1 ;
	}

	return (ans[n / x] = sum) ;
}

int main() {
	scanf("%lld" , &n) ;
	init() ;

	int res = 0 ;
	for (ll L = 1 ; L <= n ;) {
		ll t = n / L , R = n / t ;

		int tmp = (getsum(R) + mod - getsum(L - 1)) % mod ;
		res = (res + (ll)(t % mod) * (t % mod) % mod * tmp % mod) % mod ; L = R + 1 ;
	}

	printf("%d\n" , res) ;

	return 0 ;
}