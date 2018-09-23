#include <stdio.h>
#include <stdlib.h>

const int MAX_N = 40000 + 10 ;

long long phi[MAX_N] ;
int n , tot , prime[MAX_N] ;

int main() {
	scanf("%d" , &n) ;
	for (int i = 2 ; i < n ; ++i) phi[i] = i ;

	///
	
	long long sum = 1 ;
	for (int i = 2 ; i < n ; ++i) {
		if (phi[i] == i) {
			prime[tot++] = i ;
			--phi[i] ;
		}

		for (int j = 0 ; j < tot ; ++j) {
			int temp = i * prime[j] ;
			if (temp >= n) break ;

			if (i % prime[j] == 0) {
				phi[temp] = phi[i] * prime[j] ;
				break ;
			}
			else phi[temp] = phi[i] * phi[prime[j]] ;
		}

		sum += phi[i] ;
	}

	if (n > 1) printf("%lld\n" , sum * 2 + 1) ;
	else printf("%d\n" , 0) ;

	return 0 ;
}

