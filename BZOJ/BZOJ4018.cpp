#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 2e6 + 10 , mod[2] = {1e9 + 7 , 1e9 + 9} ;

int T , n , m ;
bool vis[MAX_N] ;
int tot , pri[MAX_N] , mu[MAX_N] , s[2][MAX_N] , f[2][MAX_N] ;

void init() {
	n = 2e6 ;

	mu[1] = 1 ;
	for (int i = 1 ; i <= n ; ++i) f[0][i] = f[1][i] = 1 ;
	for (int i = 2 ; i <= n ; ++i) {
		if (!vis[i]) {
			pri[tot++] = i ; mu[i] = -1 ;
			for (int j = 0 ; j < 2 ; ++j) f[j][i] = (f[j][i] - i + mod[j]) % mod[j] ;
		}

		for (int j = 0 ; j < tot ; ++j) {
			int tmp = i * pri[j] ;
			if (tmp > n) break ;
			vis[tmp] = 1 ;

			if (i % pri[j]) {
				mu[tmp] = -mu[i] ;
				for (int k = 0 ; k < 2 ; ++k) f[k][tmp] = (ll)f[k][i] * f[k][pri[j]] % mod[k] ;
			}
			else {
				mu[tmp] = 0 ;
				for (int k = 0 ; k < 2 ; ++k) f[k][tmp] = f[k][i] ;
				break ;
			}
		}
	}

	for (int i = 1 ; i <= n ; ++i)
		for (int j = 0 ; j < 2 ; ++j) {
			int tmp = (((ll)i * (i + 1)) >> 1) % mod[j] ;
			(f[j][i] += f[j][i - 1]) %= mod[j] ;
			s[j][i] = (s[j][i - 1] + tmp) % mod[j] ;
		}
}

int count(int ty , int x , int y) {
	int s1 = s[ty][x - 1] ,
		s2 = x == y ? s[ty][y - 1] : (s[ty][y - 1] - s[ty][y - x - 1] + mod[ty]) % mod[ty] ;

	return (s1 + s2) % mod[ty] ;
}

int main() {
	init() ;

	scanf("%d" , &T) ;
	for (; T-- ;) {
		scanf("%d %d" , &n , &m) ;
		if (n > m) std::swap(n , m) ;

		int L = 1 , ans[2] = {0 , 0} ;
		for (; L <= n ;) {
			int t1 = n / L , t2 = m / L , R = std::min(n / t1 , m / t2) ;

			for (int j = 0 ; j < 2 ; ++j) {
				int s1 = count(j , t1 , t2) , s2 = (f[j][R] - f[j][L - 1] + mod[j]) % mod[j] ;
				ans[j] = (ans[j] + (ll)s1 * s2) % mod[j] ;
			}
			L = R + 1 ;
		}

		printf("%d %d\n" , ans[0] , ans[1]) ;
	}

	return 0 ;
}