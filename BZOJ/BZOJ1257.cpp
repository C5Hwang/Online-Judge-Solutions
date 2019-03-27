#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

ll ans ;
int n , k ;

inline ll count(int x , int y) {
	--x ;
	return ((ll)y * (y + 1) - (ll)x * (x + 1)) >> 1 ;
}

int main() {
	scanf("%d %d" , &n , &k) ;

	int L = 1 ; ans = 0 ;
	for (; L <= n ;) {
		int t = k / L , R = t ? std::min(k / t , n) : n ;

		ll s1 = (ll)k * (R - L + 1) , s2 = count(L , R) * t ;
		ans += s1 - s2 ; L = R + 1 ;
	}

	printf("%lld\n" , ans) ;

	return 0 ;
}