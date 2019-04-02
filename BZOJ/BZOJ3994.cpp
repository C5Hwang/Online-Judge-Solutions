#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 5e4 + 10 ;

ll sum[MAX_N] ;
bool vis[MAX_N] ;
int tot , pri[MAX_N] ;
int T , n , m , mu[MAX_N] ;

void init() {
	n = 5e4 ;

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

	for (int i = 2 ; i <= n ; ++i) mu[i] += mu[i - 1] ;
	for (int i = 1 ; i <= n ; ++i)
		for (int L = 1 ; L <= i ;) {
			int t = i / L , R = i / t ;
			sum[i] += (ll)t * (R - L + 1) ; L = R + 1 ;
		}
}

int main() {
	init() ;

	scanf("%d" , &T) ;
	for (; T-- ;) {
		scanf("%d %d" , &n , &m) ;
		if (n > m) std::swap(n , m) ;

		ll ans = 0 ;
		for (int L = 1 ; L <= n ;) {
			int t1 = n / L , t2 = m / L , R = std::min(n / t1 , m / t2) ;

			ans += sum[t1] * sum[t2] * (mu[R] - mu[L - 1]) ; L = R + 1 ;
		}
		printf("%lld\n" , ans) ;
	}

	return 0 ;
}