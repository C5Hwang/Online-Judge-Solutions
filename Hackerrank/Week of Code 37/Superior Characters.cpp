#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int N = 26 , MAX_N = 26 + 5 ;

int Q , a[MAX_N] , b[MAX_N] , c[MAX_N] ;

bool check(ll x) {
	ll s = 0 ;

	for (int i = 0 ; i < N ; ++i) b[i] = 0 , c[i] = a[i] ;

	for (int i = 0 ; i < N ; ++i)
		if (s + a[i] < x) b[i] = a[i] , c[i] = 0 , s += a[i] ;
		else {b[i] = x - s ; c[i] -= b[i] ; break ;}

	int pl = 0 , pr = 0 ; ll ans = 0 ;
	for (;;) {
		for (; !b[pl] && pl < N ; ++pl) ;
		for (; !c[pr] && pr < N || pl >= pr ; ++pr) ;

		if (pl >= N || pr >= N) break ;

		int ud = std::min(b[pl] , c[pr]) ;
		ans += ud ; b[pl] -= ud ; c[pr] -= ud ;
	}

	return ans == x ;
}

int main() {
	scanf("%d" , &Q) ;
	for (; Q-- ;) {
		for (int i = 0 ; i < N ; ++i) scanf("%d" , &a[i]) ;
		for (int i = 0 ; i < N ; ++i) if (a[i]) {--a[i] ; break ;}

		///

		ll L = 0 , R = 1 ;
		for (int i = 0 ; i < N ; ++i) R += a[i] ;

		for(; L + 1 < R ;) {
			ll mid = (L + R) >> 1 ;
			if (check(mid)) L = mid ;
			else R = mid ;
		}

		printf("%lld\n" , L) ;
	}

	return 0 ;
}