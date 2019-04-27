#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 5e5 + 10 , mod = 1e9 + 7 ;

int n , f[MAX_N] , g[MAX_N] ;

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

inline int qpow(int a , int t) {
	int s = 1 , tmp = a ;
	for (; t ; t >>= 1 , tmp = (ll)tmp * tmp % mod)
		if (t & 1) s = (ll)s * tmp % mod ;

	return s ;
}

int main() {
	n = read() ;
	int ny = qpow(100 , mod - 2) ;
	for (int i = 1 ; i <= n ; ++i) {
		int a , b ; a = read() ; b = read() ;
		a = (ll)a * ny % mod ; b = (ll)b * ny % mod ;

		if (i == 1) f[i] = a , g[1] = b ;
		else {
			int t = (ll)b * g[i - 1] % mod ;
			t = qpow(mod + 1 - t , mod - 2) ;
			f[i] = (ll)t * a % mod ;

			t = (ll)a * g[i - 1] % mod ;
			g[i] = ((ll)t * f[i] + b) % mod ;
		}
	}
	for (int i = n - 1 ; i ; --i) f[i] = (ll)f[i] * f[i + 1] % mod ;

	printf("%d\n" , f[1]) ;

	return 0 ;
}