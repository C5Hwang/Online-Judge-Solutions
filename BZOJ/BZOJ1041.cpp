#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 ;

ll n , tot , num[MAX_N] ;

ll gcd(ll a , ll b) {return a % b ? gcd(b , a % b) : b ;}

int count(ll x) {
	int p = tot , res = 0 ;

	for (int i = 1 ; i <= p ; ++i) {
		for (; num[i] + num[p] > x ; --p) ;

		if (i > p) break ;
		if (num[i] + num[p] != x) continue ;

		if (gcd(num[i] , x) == 1) ++res ;
	}

	return res ;
}

int main() {
	scanf("%lld" , &n) ; n *= 2 ;
	for (ll i = 1 ; i * i <= n ; ++i) num[++tot] = i * i ;

	///

	int sum = 0 ;
	for (ll d = 1 ; d * d <= n ; ++d) {
		if (n % d) continue ;

		ll tmp = n / d ;
		sum += count(d) ; if (d != tmp) sum += count(tmp) ;
	}

	printf("%d\n" , sum << 2) ;

	return 0 ;
}