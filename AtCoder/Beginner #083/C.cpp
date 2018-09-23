#include <stdio.h>
#include <stdlib.h>

#define ll long long

ll x , y , ans ;

int main() {
	scanf("%lld %lld" , &x , &y) ;

	ll num = x ; ans = 0 ;
	for (; num <= y ; num <<= 1 , ++ans) ;

	printf("%lld\n" , ans) ;

	return 0 ;
}