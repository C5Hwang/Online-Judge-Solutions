#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 5e4 + 10 , N = 5e4 ;

bool vis[MAX_N] ;
int T , a , b , c , d , k ;
int tot , prime[MAX_N] , mu[MAX_N] , sum[MAX_N] ;

void init() {
	mu[1] = 1 ;
	for (int i = 2 ; i <= N ; ++i) {
		if (!vis[i]) prime[tot++] = i , mu[i] = -1 ;

		for (int j = 0 ; j < tot ; ++j) {
			int tmp = i * prime[j] ;
			if (tmp > N) break ;

			vis[tmp] = 1 ;
			if (i % prime[j]) mu[tmp] = -mu[i] ;
			else {mu[tmp] = 0 ; break ;}
		}
	}

	for (int i = 1 ; i <= N ; ++i) sum[i] = sum[i - 1] + mu[i] ;
}

int work(int n , int m) {
	int tf = std::min(n / k , m / k) , last , ans ;

	ans = 0 ;
	for (int i = 1 ; i <= tf ; i = last + 1) {
		int tx = n / (i * k) , ty = m / (i * k) ;
		last = std::min(n / (tx * k) , m / (ty * k)) ;

		ans += (sum[last] - sum[i - 1]) * tx * ty ;
	}

	return ans ;
}

int main() {
	init() ;

	///

	scanf("%d" , &T) ;
	for (; T-- ;) {
		scanf("%d %d %d %d %d" , &a , &b , &c , &d , &k) ;

		int ans = work(b , d) - work(b , c - 1) - work(a - 1 , d) + work(a - 1 , c - 1) ;
		printf("%d\n" , ans) ;
	}

	return 0 ;
}