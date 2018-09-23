#include <stdio.h>
#include <stdlib.h>

#define ll long long

const int MAX_N = 1e3 + 10 ;

bool p[MAX_N] ;
ll f[MAX_N][MAX_N] ;
int n , tot , prime[MAX_N] ;

int main() {
    scanf("%d" , &n) ;
	if (n == 1) {
		printf("1\n") ;
		return 0 ;
	}

	///

    for (int i = 2 ; i <= n ; ++i) {
        if (!p[i]) prime[tot++] = i ;

        for (int j = 0 ; j < tot ; ++j) {
            int tmp = prime[j] * i ;
            if (tmp > n) break ;

            p[tmp] = 1 ;
            if (!(i % prime[j])) break ;
        }
    }

    ///

    f[0][0] = 1 ;
    for (int i = prime[0] ; i <= n ; i *= prime[0]) f[0][i] = 1 ;
    for (int i = 1 ; i < tot ; ++i)
        for (int j = 0 ; j <= n ; ++j) {
            f[i][j] = f[i - 1][j] ;

            int k = prime[i] ;
            for (; j - k >= 0 ; k *= prime[i]) f[i][j] += f[i - 1][j - k] ;
        }

    ll ans = 0 ;
    for (int i = 0 ; i <= n ; ++i) ans += f[tot - 1][i] ;
    printf("%lld\n" , ans) ;

    return 0 ;
}
