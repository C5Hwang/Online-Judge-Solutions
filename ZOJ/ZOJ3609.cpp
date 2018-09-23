#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int a , b , x , y , d ;

int Egcd(int a , int b , int &x , int &y) {
	if (!b) {
		x = 1 ; y = 0 ;
		return a ;
	}
	else {
		int d = Egcd(b , a % b , x , y) , lx = x , ly = y ;
		x = ly ; y = lx - (a / b) * ly ;

		return d ;
	}
}

int main() {
	int T ; scanf("%d" , &T) ;

	while (T--) {
		scanf("%d %d" , &a , &b) ;
		d = Egcd(a , b , x , y) ;

		if (d > 1) printf("Not Exist\n") ;
		else {
			int q = floor(x * 1.0 / b) ;

			if (x - q * b) printf("%d\n" , x - q * b) ;
			else printf("%d\n" , b) ;
		}
	}

	return 0 ;
}

