#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e7 + 10 ;

bool vis[MAX_N] ;
int tot , pri[MAX_N] , phi[MAX_N] ;
int T , P , n , m , jc[MAX_N] , inv[MAX_N] ;

int qpow(int x , int t) {
	int sum = 1 , tmp = x ;
	for (; t ; t >>= 1 , tmp = (ll)tmp * tmp % P)
		if (t & 1) sum = (ll)sum * tmp % P ;

	return sum ;
}

void init() {
	n = std::min(P - 1 , (int)1e7) ;

	jc[1] = 1 ;
	for (int i = 2 ; i <= n ; ++i) jc[i] = jc[i - 1] * (ll)i % P ;
	inv[n] = qpow(jc[n] , P - 2) ;
	for (int i = n - 1 ; i ; --i) inv[i] = inv[i + 1] * (ll)(i + 1) % P ;
	for (int i = n ; i > 1 ; --i) inv[i] = inv[i] * (ll)jc[i - 1] % P ;

	for (int i = 1 ; i <= n ; ++i) phi[i] = 1 ;
	for (int i = 2 ; i <= n ; ++i) {
		if (!vis[i]) pri[tot++] = i , phi[i] = (ll)(i - 1) * inv[i] % P ;

		for (int j = 0 ; j < tot ; ++j) {
			int tmp = i * pri[j] ;
			if (tmp > n) break ;

			vis[tmp] = 1 ;
			if (!(i % pri[j])) break ;
		}
	}

	for (int i = 2 ; i <= n ; ++i) phi[i] = (ll)phi[i] * phi[i - 1] % P ;
}

int main() {
	scanf("%d %d" , &T , &P) ;
	init() ;

	for (; T-- ;) {
		scanf("%d %d" , &n , &m) ;

		int res = (ll)jc[n] * phi[m] % P ;
		printf("%d\n" , res) ;
	}

	return 0 ;
}