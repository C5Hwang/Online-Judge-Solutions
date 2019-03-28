#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e6 + 10 ;

bool vis[MAX_N] ;
ll f[MAX_N] , res[MAX_N] ;
int T , n , tot , pri[MAX_N] , mu[MAX_N] ;

void init() {
	n = 1e6 ;

	mu[1] = 1 ;
	for (int i = 2 ; i <= n ; ++i) {
		if (!vis[i]) {pri[tot++] = i ; mu[i] = -1 ;}

		for (int j = 0 ; j < tot ; ++j) {
			int tmp = i * pri[j] ;
			if (tmp > n) break ;

			vis[tmp] = 1 ;
			if (!(i % pri[j])) {mu[tmp] = 0 ; break ;}
			else mu[tmp] = -mu[i] ;
		}
	}

	for (int i = 1 ; i <= n ; ++i) {
		for (int j = i ; j <= n ; j += i) {
			ll sum = ((ll)j * (j / i + 1)) >> 1 ;
			f[j] += mu[i] * sum ;
		}
		for (int j = i ; j <= n ; j += i) res[j] += f[i] ;
	}
}

int main() {
	init() ;

	scanf("%d" , &T) ;
	for (; T-- ;) {
		scanf("%d" , &n) ;
		printf("%lld\n" , n * res[n]) ;
	}

	return 0 ;
}
