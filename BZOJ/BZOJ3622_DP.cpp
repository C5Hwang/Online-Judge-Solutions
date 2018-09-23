#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long

const int MAX_N = 2e3 + 10 , mod = 1e9 + 9 ;

int n , k , r , a[MAX_N] , b[MAX_N] , fac[MAX_N] ;
int get[MAX_N] , f[MAX_N][MAX_N] , g[MAX_N] , c[MAX_N][MAX_N] ;

int main() {
	scanf("%d %d" , &n , &k) ;
	r = (n - k) / 2 ; if ((n - k) % 2) {printf("0\n") ; return 0 ;}
	for (int i = 1 ; i <= n ; ++i) scanf("%d" , &a[i]) ;
	for (int i = 1 ; i <= n ; ++i) scanf("%d" , &b[i]) ;

	///
	
	std::sort(a + 1 , a + 1 + n) ; std::sort(b + 1 , b + 1 + n) ;
	int j = 1 ;
	for (int i = 1 ; i <= n ; ++i) {
		for (; b[i] > a[j] && j <= n ; ++j) ;
		get[i] = j - 1 ;
	}
	c[0][0] = 1 ;
	for (int i = 1 ; i <= n ; ++i) {
		c[i][0] = c[i][i] = 1 ;
		for (int j = 1 ; j < i ; ++j) c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mod ;
	}
	fac[1] = 1 ;
	for (int i = 2 ; i <= n ; ++i) fac[i] = ((ll)fac[i - 1] * i) % mod ;

	///

	if (get[1] < n) f[1][0] = 1 ;
	f[1][1] = get[1] ;
	for (int i = 2 ; i <= n ; ++i) {
		f[i][0] = f[i - 1][0] ;
		for (int j = 1 ; j <= n ; ++j) {
			int tmp = ((ll)f[i - 1][j - 1] * std::max(get[i] - j + 1 , 0)) % mod ;
			f[i][j] = (f[i - 1][j] + tmp) % mod ;
		}
	}

	g[n] = f[n][n] ;
	for (int i = n - 1 ; i >= r ; --i) {
		g[i] = ((ll)f[n][i] * fac[n - i]) % mod ;

		int sum = 0 ;
		for (int j = i + 1 ; j <= n ; ++j) {
			int tmp = ((ll)g[j] * c[j][i]) % mod ;
			sum = (sum + tmp) % mod ;
		}

		g[i] = (g[i] - sum + mod) % mod ;
	}

	printf("%d\n" , g[r]) ;

	return 0 ;
}
