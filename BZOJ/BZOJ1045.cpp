#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e6 + 10 ;

ll ave , ans ;
int n , a[MAX_N] , c[MAX_N] ;

int main() {
	scanf("%d" , &n) ;
	for (int i = 1 ; i <= n ; ++i) {
		scanf("%d" , &a[i]) ;
		ave += a[i] ;
	}
	ave /= n ;
	for (int i = 1 ; i <= n ; ++i) c[i] = a[i] - ave ;

	///

	c[0] = 0 ;
	for (int i = 1 ; i < n ; ++i) c[i] += c[i - 1] ;
	std::sort(c + 0 , c + n) ;

	int x = c[n / 2] ;
	for (int i = 0 ; i < n ; ++i) ans += abs(x - c[i]) ;

	printf("%lld\n" , ans) ;

	return 0 ;
}