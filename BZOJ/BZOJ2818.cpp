#include <stdio.h>
#include <stdlib.h>

const int MAX_N = 10000000 + 10 ;

int n , tot , prime[MAX_N] ;
long long res , phi[MAX_N] , sum[MAX_N] ;

int main() {
	scanf("%d" , &n) ;
	for (int i = 1 ; i <= n ; ++i) phi[i] = i ;
	for (int i = 2 ; i <= n ; ++i) {
		if (phi[i] == i) {
			--phi[i] ;
			prime[tot++] = i ;
		}

		for (int j = 0 ; j < tot ; ++j) {
			long long temp = (long long)i * prime[j] ;
			if (temp > n) break ;

			if (i % prime[j]) phi[temp] = phi[i] * phi[prime[j]] ;
			else {phi[temp] = phi[i] * prime[j] ; break ;}
		}
	}
	
	///
	
	int INF = n / 2 ;
	sum[0] = 0 ;
	for (int i = 1 ; i <= INF ; ++i) sum[i] = sum[i - 1] + phi[i] ;

	///
	
	res = 0 ;
	for (int i = 0 ; i < tot ; ++i) {
		int R = n / prime[i] ;

		res += sum[R] * 2 ;
	}

	printf("%lld\n" , res - tot) ;

	return 0 ;
}
