#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e7 + 10 ;

ll ans ;
bool vis[MAX_N] ;
int n , m , tot , g[MAX_N] , pri[MAX_N] ;
int t1[MAX_N] , t2[MAX_N] , del[MAX_N] , num[MAX_N] ;

void init() {
	n = 1e7 ;

	g[1] = 0 ;
	for (int i = 2 ; i <= n ; ++i) {
		if (!vis[i]) {
			t1[i] = t2[i] = num[i] = 1 ;
			del[i] = 0 ; pri[tot++] = i ;
		}

		for (int j = 0 ; j < tot ; ++j) {
			int tmp = (ll)i * pri[j] ;
			if (tmp > n) break ;
			vis[tmp] = 1 ;

			if (i % pri[j]) {
				t1[tmp] = 1 ; t2[tmp] = t2[i] ;
				del[tmp] = del[i] + (t2[i] - 1) ; num[tmp] = num[i] + 1 ;
			}
			else {
				t1[tmp] = t1[i] + 1 ; num[tmp] = num[i] ;
				if (t1[tmp] > t2[i]) {t2[tmp] = t1[tmp] ; del[tmp] = del[i] + (num[tmp] - 1) ;}
				else {t2[tmp] = t2[i] ; del[tmp] = del[i] - 1 ;}

				break ;
			}
		}
	}

	for (int i = 2 ; i <= n ; ++i) {
		if (!del[i]) g[i] = num[i] % 2 ? 1 : -1 ;
		else g[i] = 0 ;
		g[i] += g[i - 1] ;
	}
}

int main() {
	init() ;

	int T ; scanf("%d" , &T) ;
	for (; T-- ;) {
		scanf("%d %d" , &n , &m) ;
		if (n > m) std::swap(n , m) ;

		int L = 1 ; ans = 0 ;
		for (; L <= n ;) {
			int t1 = n / L , t2 = m / L , R = std::min(n / t1 , m / t2) ;

			ans += (ll)t1 * t2 * (g[R] - g[L - 1]) ; L = R + 1 ;
		}

		printf("%lld\n" , ans) ;
	}

	return 0 ;
}