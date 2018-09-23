#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

long long x , y , m , n , L ;
long long a , b , c , d , T , k ;

long long Egcd(long long a , long long b , long long &x , long long &y) {
	if (!b) {
		x = 1 ; y = 0 ;
		return a ;
	}
	else {
		long long d = Egcd(b , a % b , x , y) , lx = x , ly = y , p = a / b ;

		x = ly ; y = lx - p * ly ;
		return d ;
	}
}

int main() {
	scanf("%lld %lld %lld %lld %lld" , &x , &y , &m , &n , &L) ;
	a = n - m ; b = L ; c = x - y ;
	
	d = Egcd(a , b , T , k) ;

	if (c % d) printf("Impossible\n") ;
	else {
		long long c1 = c / d , b1 = b / d , q , ans ;
		T *= c1 ;

		if (b1 >= 0) q = floor(T * 1.0 / b1) ;
		else q = ceil(T * 1.0 / b1) ;

		ans = T - q * b1 ;

		printf("%lld\n" , ans) ;
	}

	return 0 ;
}
