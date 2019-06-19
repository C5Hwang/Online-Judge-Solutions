#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

int T , n , m , k ;

int gcd(int a , int b) {return b ? gcd(b , a % b) : a ;}

int main() {
	scanf("%d" , &T) ;
	for (; T-- ;) {
		scanf("%d %d %d" , &n , &m , &k) ;

		int d1 = gcd(n , k) , d2 = gcd(m , k) ;
		if (d1 > 1 || d2 > 1) printf("-1\n") ;
		else printf("%lld\n" , (ll)n * m) ;
	}

	return 0 ;
}