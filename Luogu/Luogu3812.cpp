#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 50 + 5 ;

int n ;
ll a[MAX_N] , b[MAX_N] ;

int main() {
	scanf("%d" , &n) ;
	for (int i = 0 ; i < n ; ++i) scanf("%lld" , &a[i]) ;

	for (int i = 0 ; i < n ; ++i)
		for (int j = 51 ; j >= 0 ; --j) {
			if (!((a[i] >> j) & 1)) continue ;

			if (b[j]) a[i] ^= b[j] ;
			else {
				b[j] = a[i] ;
				for (int k = j - 1 ; k >= 0 ; --k) if ((b[j] >> k) & 1) b[j] ^= b[k] ;
				for (int k = 51 ; k > j ; --k) if ((b[k] >> j) & 1) b[k] ^= b[j] ;
				break ;
			}
		}

	ll ans = 0 ;
	for (int i = 0 ; i <= 51 ; ++i) ans ^= b[i] ;
	printf("%lld\n" , ans) ;

	return 0 ;
}