#include <stdio.h>
#include <stdlib.h>

const int MAX_N = 1e7 + 10 ;

int n , tot , phi[MAX_N] , prime[MAX_N] ;

int sep(int p , int &t) {
	while (!(p % 2)) p /= 2 , ++t ;

	return p ;
}

long long powMOD(int x , int p) {
	if (!x) return 1 % p ;

	long long temp = powMOD(x / 2 , p) , np = temp * temp % p ;

	if (x % 2) np = (np * 2) % p ;

	return np ;
}

long long pow(int x) {
	if (!x) return 1 ;

	long long temp = pow(x / 2) , p = temp * temp ;

	if (x % 2) p *= 2 ;

	return p ;
}

long long euler(int p) {
	if (p == 1) return 0 ;

	int k = 0 , q = sep(p , k) , ph = phi[q] , temp = euler(ph) , nt = ((temp % ph) - (k % ph) + ph) % ph ;

	return powMOD(nt , q) * pow(k) ;
}

int main() {
	for (int i = 1 ; i <= 1e7 ; ++i) phi[i] = i ;
	for (int i = 2 ; i <= 1e7 ; ++i) {
		if (phi[i] == i) {
			prime[tot++] = i ;
			--phi[i] ;
		}

		for (int j = 0 ; j < tot ; ++j) {
			int temp = prime[j] * i ;

			if (temp > 1e7) break ;

			if (i % prime[j]) phi[temp] = phi[i] * phi[prime[j]] ;
			else {phi[temp] = phi[i] * prime[j] ; break ;}
		}
	}

	///

	int T ; scanf("%d" , &T) ;
	while (T--) {
		scanf("%d" , &n) ;

		long long res = euler(n) ;

		printf("%lld\n" , res) ;
	}

	return 0 ;
}
