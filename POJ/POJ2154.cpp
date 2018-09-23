#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

int Q , n , p ;

int qpow(int a , int t) {
	if (!t) return 1 ;

	int s = qpow(a , t >> 1) ;
	s = (ll)s * s % p ;
	if (t & 1) s = (ll)s * a % p ;

	return s ;
}

int phi(int x) {
	int res = x ;
	for (int i = 2 ; i * i <= x ; ++i) {
		if (x % i) continue ;

		res = res / i * (i - 1) ;
		for (; !(x % i) ; x /= i) ;
	}
	if (x > 1) res = res / x * (x - 1) ;

	return res ;
}

int getans(int d) {
	int a = qpow(n , d - 1) , b = phi(n / d) ;

	return (ll)a * b % p ;
}

int main() {
	scanf("%d" , &Q) ;
	for (; Q-- ;) {
		scanf("%d %d" , &n , &p) ;

		if (n == 1) {printf("%d\n" , 1 % p) ; continue ;}

		int ans = 0 ;
		for (int i = 1 ; i * i <= n ; ++i) {
			if (n % i) continue ;
			int a = i , b = n / i ;

			(ans += getans(a)) %= p ;
			if (a != b) (ans += getans(b)) %= p ;
		}

		printf("%d\n" , ans) ;
	}

	return 0 ;
}