#include <stdio.h>
#include <stdlib.h>

const long long MOD = 1e5 + 3 ;

long long n , m , s1 , s2 ;

long long pow(long long x , long long k) {
	if (!k) return 1 ;

	long long temp = pow(x , k >> 1) , s = temp * temp % MOD ;
	if (k & 1) s = s * x % MOD ;

	return s ;
}

int main() {
	scanf("%lld %lld" , &m , &n) ;

	s1 = pow(m , n) ;
	s2 = m * pow(m - 1 , n - 1) % MOD ;

	printf("%lld\n" , (s1 + MOD - s2) % MOD) ;

	return 0 ;
}
