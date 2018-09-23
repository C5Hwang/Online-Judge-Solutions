#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAX_N = 100000 + 10 ;

bool ap[MAX_N] ;
int n , k , tot , mu[MAX_N] , prime[MAX_N] ;

bool check(int x) {
	int sqx = (int)sqrt(x) , sum = 0 ;

	for (int i = 2 ; i <= sqx ; ++i) sum += (x / (i * i)) * mu[i] ;

	x += sum ;

	return x < k ;
}

int main() {
	int T ; scanf("%d" , &T) ;
	while (T--) {
		scanf("%d" , &k) ; n = (int)sqrt(2 * k) ;

		///

		mu[1] = 1 ; ap[1] = 1 ;
		for (int i = 2 ; i <= n ; ++i) {
			if (!ap[i]) {
				mu[i] = -1 ; ap[i] = 1 ;
				prime[tot++] = i ;
			}

			for (int j = 0 ; j < tot ; ++j) {
				int temp = i * prime[j] ;
				if (temp > n) break ;

				if (i % prime[j]) mu[temp] = mu[i] * mu[prime[j]] , ap[temp] = 1 ;
				else {mu[temp] = 0 ; ap[temp] = 1 ; break ;}
			}
		}

		///

		int L = 0 , R = 2 * k ;
		while (L + 1 < R) {
			int mid = (int)(((long long)L + R) >> 1) ;
			if (check(mid)) L = mid ;
			else R = mid ;
		}

		printf("%d\n" , R) ;
	}

	return 0 ;
}
