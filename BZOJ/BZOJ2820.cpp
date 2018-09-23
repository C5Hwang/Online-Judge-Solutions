#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e7 + 10 , N = 1e7 ;

ll sum[MAX_N] ;
int T , n , m ;
bool vis[MAX_N] ;
int tot , prime[MAX_N] , mu[MAX_N] , a[MAX_N] ;

void init() {
	mu[1] = 1 ;
	for (int i = 2 ; i <= N ; ++i) {
		if (!vis[i]) {prime[tot++] = i ; mu[i] = -1 ;}

		for (int j = 0 ; j < tot ; ++j) {
			int tmp = i * prime[j] ;
			if (tmp > N) break ;

			vis[tmp] = 1 ;
			if (i % prime[j]) mu[tmp] = -mu[i] ;
			else {mu[tmp] = 0 ; break ;}
		}
	}

	for (int i = 0 ; i < tot ; ++i) {
		int p = prime[i] ;
		for (int j = p ; j <= N ; j += p) a[j] += mu[j / p] ;
	}

	for (int i = 1 ; i <= N ; ++i) sum[i] = sum[i - 1] + a[i] ;
}

ll work(int n , int m) {
	int tf = std::min(n , m) ;
	int last ; ll ans = 0 ;

	for (int i = 2 ; i <= tf ; i = last + 1) {
		int tx = n / i , ty = m / i ;
		last = std::min(n / tx , m / ty) ;

		ans += (sum[last] - sum[i - 1]) * tx * ty ;
	}

	return ans ;
}

int main() {
	init() ;

	///

	scanf("%d" , &T) ;
	for (; T-- ;) {
		scanf("%d %d" , &n , &m) ;

		ll ans = work(n , m) ;
		printf("%lld\n" , ans) ;
	}

	return 0 ;
}