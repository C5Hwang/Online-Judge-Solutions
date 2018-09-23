#include <stdio.h>
#include <stdlib.h>

const int MAX_N = 1000000 + 10 , mod = 20100403 ;

int n , m ;
long long f[MAX_N] ;

void Egcd(int a , int b , long long &x , long long &y) {
	if (!b) x = 1 , y = 0 ;
	else {
		long long lx , ly ;
		Egcd(b , a % b , lx , ly) ;

		x = ly ; y = lx - (a / b) * ly ;
	}
}

int main() {
	scanf("%d %d" , &n , &m) ;

	///

	f[0] = 0 ; f[1] = (n + m) % mod ;
	for (int i = 2 ; i <= n + 1 ; ++i) {
		long long ek , a ;
		Egcd(i , mod , ek , a) ;

		while (ek <= 0) ek += mod ;
		ek %= mod ;

		f[i] = (((f[i - 1] * (n + m - i + 1)) % mod) * ek) % mod ;
	}

	printf("%lld\n" , (f[n] - f[n + 1] + mod) % mod) ;

	return 0 ;
}
