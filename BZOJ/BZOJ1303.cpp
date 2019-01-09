#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define cnt(x) cnt[x + offset]
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 , offset = 1e5 ;

int n , b , p , a[MAX_N] , s[MAX_N] , cnt[MAX_N << 1] ;

int main() {
	scanf("%d %d" , &n , &b) ;
	for (int i = 1 ; i <= n ; ++i) {
		scanf("%d" , &a[i]) ;
		if (a[i] < b) a[i] = -1 ;
		else if (a[i] > b) a[i] = 1 ;
		else a[i] = 0 , p = i ;
	}

	///

	s[0] = 0 ;
	for (int i = 1 ; i <= n ; ++i) s[i] = s[i - 1] + a[i] ;

	ll ans = 0 ;
	for (int i = p ; i <= n ; ++i) ++cnt(s[i]) ;
	for (int i = 1 ; i <= p ; ++i) ans += cnt(s[i - 1]) ;

	printf("%lld\n" , ans) ;

	return 0 ;
}