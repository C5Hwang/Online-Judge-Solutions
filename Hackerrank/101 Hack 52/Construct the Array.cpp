#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 , mod = 1e9 + 7 ;

int n , k , x , f[MAX_N][3] ;

int main() {
	scanf("%d %d %d" , &n , &k , &x) ;

	///

	int ans ; n -= 2 ;

	if (x == 1) {
		f[1][0] = k - 1 ; f[1][1] = 0 ;
		for (int i = 2 ; i <= n ; ++i) {
			f[i][0] = ((ll)f[i - 1][0] * (k - 2) + (ll)f[i - 1][1] * (k - 1)) % mod ;
			f[i][1] = f[i - 1][0] ;
		}

		ans = f[n][0] ;
	}
	else {
		f[1][0] = k - 2 ; f[1][1] = 0 ; f[1][2] = 1 ;
		for (int i = 2 ; i <= n ; ++i) {
			f[i][0] = ((ll)f[i - 1][0] * (k - 3) + (ll)f[i - 1][1] * (k - 2) + (ll)f[i - 1][2] * (k - 2)) % mod ;
			f[i][1] = ((ll)f[i - 1][0] + f[i - 1][2]) % mod ;
			f[i][2] = ((ll)f[i - 1][0] + f[i - 1][1]) % mod ;
		}

		ans = (f[n][0] + f[n][1]) % mod ;
	}

	printf("%d\n" , ans) ;

	return 0 ;
}