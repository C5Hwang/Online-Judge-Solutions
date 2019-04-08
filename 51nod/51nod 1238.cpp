#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int lim = 5e6 , MAX_N = 5e6 + 10 , mod = 1e9 + 7 ;

ll n ;
bool vis[MAX_N] ;
int tot , f[MAX_N] , sum[MAX_N] , ans[MAX_N] , pri[MAX_N] ;

void init() {
	int m = std::min((ll)lim , n) ;

	f[1] = 1 ;
	for (int i = 2 ; i <= m ; ++i) {
		if (!vis[i]) {f[i] = (1 + mod - i) % mod ; pri[tot++] = i ;}

		for (int j = 0 ; j < tot ; ++j) {
			int tmp = i * pri[j] ;
			if (tmp > m) break ;
			vis[tmp] = 1 ;

			if (i % pri[j]) f[tmp] = (f[i] + mod - (ll)f[i] * pri[j] % mod) % mod ;
			else {f[tmp] = f[i] ; break ;}
		}
	}
	for (int i = 1 ; i <= m ; ++i) f[i] = (ll)f[i] * i % mod ;

	sum[1] = f[1] ;
	for (int i = 2 ; i <= m ; ++i) sum[i] = (sum[i - 1] + f[i]) % mod ;
}

inline int cal1(ll x) {
	int ny = (mod + 1) >> 1 ; x %= mod ;
	return x * (x + 1) % mod * ny % mod ;
}

inline int cal2(ll x) {
	int ny = (mod + 1) / 6 ; x %= mod ;
	return x * (x + 1) % mod * ((x << 1) + 1) % mod * ny % mod ;
}

int getsum(ll m) {
	if (m <= lim) return sum[m] ;
	if (ans[n / m] != -1) return ans[n / m] ;

	int sum = cal1(m) ;
	for (ll L = 2 ; L <= m ;) {
		ll t = m / L , R = m / t ;

		int s1 = (cal2(R) + mod - cal2(L - 1)) % mod , s2 = getsum(t) ;
		sum = (sum + mod - (ll)s1 * s2 % mod) % mod ; L = R + 1 ;
	}

	return (ans[n / m] = sum) ;
}

int main() {
	scanf("%lld" , &n) ;

	init() ;
	memset(ans , -1 , sizeof(ans)) ;
	getsum(n) ;

	int res = 0 ;
	for (ll L = 1 ; L <= n ;) {
		ll t = n / L , R = n / t ;

		int s1 = (getsum(R) + mod - getsum(L - 1)) % mod , s2 = (ll)cal1(t) * cal1(t) % mod ;
		s1 = (ll)s1 * s2 % mod ; (res += s1) %= mod ; L = R + 1 ;
	}

	printf("%d\n" , res) ;

	return 0 ;
}