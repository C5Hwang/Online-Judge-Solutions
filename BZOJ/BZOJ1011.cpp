#include <stdio.h>
#include <stdlib.h>

#define db double
#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const db eps = 1e-8 ;
const int MAX_N = 1e5 + 10 ;

db a ;
ll s[MAX_N] ;
int n , m[MAX_N] ;

int main() {
	scanf("%d %lf" , &n , &a) ;
	for (int i = 1 ; i <= n ; ++i) scanf("%d" , &m[i]) , s[i] = s[i - 1] + m[i] ;

	///

	for (int i = 1 ; i <= n ; ++i) {
		db R = (int)(a * i + eps) ;

		if (i == n) {
			n = n ;
		}

		db ans = 0 ;
		if (R < 20) for (int j = 1 ; j <= R ; ++j) ans += m[j] / (i * 1.0 - j) ;
		else {
			int len = R / 20 ;

			int le = 1 ;
			for (int t = 1 ; t <= 20 ; ++t) {
				int ri = t != 20 ? le + len - 1 : R ;
				ans += (s[ri] - s[le - 1]) / (i - (ri + le) * 0.5) ;

				le = ri + 1 ;
			}
		}

		ans *= m[i] ;
		printf("%0.6lf\n" , ans) ;
	}

	return 0 ;
}