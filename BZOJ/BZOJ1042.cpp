#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int N = 1e5 , MAX_N = 1e5 + 10 ;

ll f[MAX_N] ;
int q , s , c[4] , d[4] ;

int main() {
	for (int i = 0 ; i < 4 ; ++i) scanf("%d" , &c[i]) ;
	f[0] = 1 ;
	for (int i = 0 ; i < 4 ; ++i)
		for (int j = c[i] ; j <= N ; ++j) f[j] += f[j - c[i]] ;

	///

	scanf("%d" , &q) ;
	for (; q-- ;) {
		for (int i = 0 ; i < 4 ; ++i) scanf("%d" , &d[i]) ;
		scanf("%d" , &s) ;

		ll ans = 0 ;
		for (int S = 0 ; S < 16 ; ++S) {
			int cnt = 0 ; ll sum = 0 ;
			for (int i = 0 ; i < 4 ; ++i)
				if ((1 << i) & S) sum += (ll)c[i] * (d[i] + 1) , ++cnt ;

			if (sum > s) continue ;

			int ty = cnt % 2 ? -1 : 1 ;
			ans += ty * f[s - sum] ;
		}

		printf("%lld\n" , ans) ;
	}

	return 0 ;
}