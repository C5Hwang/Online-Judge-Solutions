#include <stdio.h>
#include <stdlib.h>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

int n , a0 , a1 , b0 , b1 , ans ;

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

int gcd(int x , int y) {return y ? gcd(y , x % y) : x ;}

void check(int x) {
	int d1 = gcd(b0 , b1 / x) , d2 = gcd(x / a1 , a0) ;
	if (d1 == 1 && d2 == 1) ++ans ;
}

int main() {
	n = read() ;
	for (; n-- ;) {
		a0 = read() ; a1 = read() ; b0 = read() ; b1 = read() ;
		b0 = b1 / b0 ; a0 = a0 / a1 ;

		///

		ans = 0 ;
		for (int i = 1 ; i * i <= b1 ; ++i) {
			if (b1 % i) continue ;

			int j = b1 / i ;
			if (!(i % a1)) check(i) ;
			if (i != j && !(j % a1)) check(j) ;
		}

		printf("%d\n" , ans) ;
	}

	return 0 ;
}