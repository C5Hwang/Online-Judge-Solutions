#include <math.h>
#include <stdio.h>
#include <stdlib.h>

long long a , b , x , y , d ;

int Egcd(long long a , long long b , long long &x , long long &y) {
	if (!b) {
		x = 1 ; y = 0 ;
		return a ;
	}
	else {
		long long d = Egcd(b , a % b , x , y) , lx = x , ly = y ;
		x = ly ; y = lx - (a / b) * ly ;

		return d ;
	}
}

int main() {
	while (scanf("%lld %lld" , &a , &b) != EOF) {
		d = Egcd(a , b , x , y) ;

		if (d > 1) printf("sorry\n") ;
		else {
			long long a1 = a / d , b1 = b / d , p ;

			if (b > 0) p = floor(x * 1.0 / b1) ;
			else p = ceil(x * 1.0 / b1) ;

			printf("%lld %lld\n" , x - p * b1 , y + p * a1) ;
		}
	}
}
