#include <stdio.h>
#include <stdlib.h>

const int MAX_N = 1e3 + 10 ;

int n , m ;
long long res ;

long long C(long long n , long long m) {
	if (n > m) return 0 ;

	long long sum = 1 ;
	for (int i = 0 ; i < n ; ++i) sum *= (m - i) ;
	for (int i = 1 ; i <= n ; ++i) sum /= i ;

	return sum ;
}

int gcd(int x , int y) {
	return y ? gcd(y , x % y) : x ;
}

int main() {
	scanf("%d %d" , &n , &m) ; ++n ; ++m ;

	///

	res = C(3 , n * m) - n * C(3 , m) - m * C(3 , n) ;
	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= m ; ++j) {
			long long s = (long long)(n - i) * (m - j) , d = gcd(i , j) - 1 ;
			res -= 2 * s * d ;
		}
	
	printf("%lld\n" , res) ;

	return 0 ;
}
