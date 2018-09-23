#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 2e5 + 10 ;

ll ans ;
int n , cur , tot , num[MAX_N] , tmp[50] ;

int getphi(int n) {
	int x = n ; tot = 0 ;

	for (ll i = 2 ; i * i <= x ; ++i) {
		if (x % i) continue ;
		tmp[tot++] = i ;

		for (; !(x % i) ; x /= i) ;
	}

	if (x > 1) tmp[tot++] = x ;

	///

	int p = n ;
	for (int i = 0 ; i < tot ; ++i)
		p = p / tmp[i] * (tmp[i] - 1) ;

	return p ;
}

int main() {
	scanf("%d" , &n) ;

	///

	for (ll i = 1 ; i * i <= n ; ++i) {
		if (n % i) continue ;
		num[cur++] = i ; num[cur++] = n / i ;
	}

	for (int i = 0 ; i < cur ; ++i) {
		int tmp = getphi(n / num[i]) ;
		ans += (ll)tmp * num[i] ;
	}

	printf("%lld\n" , ans) ;

	return 0 ;
}