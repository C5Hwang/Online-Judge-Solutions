#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e7 + 10 , mod = 1e8 + 9 ;

int T , n , m ;
bool vis[MAX_N] ;
int tot , pri[MAX_N] , s[MAX_N] , mu[MAX_N] ;

void init() {
	n = 1e7 ;

	for (int i = 1 ; i <= n ; ++i) mu[1] = 1 , s[i] = 1 ;
	for (int i = 2 ; i <= n ; ++i) {
		if (!vis[i]) {pri[tot++] = i ; mu[i] = -1 ; s[i] = (s[i] - i + mod) % mod ;}

		for (int j = 0 ; j < tot ; ++j) {
			int tmp = i * pri[j] ;
			if (tmp > n) break ;

			vis[tmp] = 1 ;
			if (i % pri[j]) {mu[tmp] = -mu[i] ; s[tmp] = (ll)s[i] * s[pri[j]] % mod ;}
			else {mu[tmp] = 0 ; s[tmp] = s[i] ; break ;}
		}
	}
	for (int i = 1 ; i <= n ; ++i)
		s[i] = (ll)s[i] * i % mod , (s[i] += s[i - 1]) %= mod ;
}

int main() {
	init() ;

	scanf("%d" , &T) ;
	for (; T-- ;) {
		scanf("%d %d" , &n , &m) ;
		if (n > m) std::swap(n , m) ;

		int L = 1 , ans = 0 ;
		for (; L <= n ;) {
			int t1 = n / L , t2 = m / L , R = std::min(n / t1 , m / t2) , res , s1 , s2 ;

			res = (s[R] - s[L - 1] + mod) % mod ;
			s1 = (((ll)t1 * (t1 + 1)) >> 1) % mod ; s2 = (((ll)t2 * (t2 + 1)) >> 1) % mod ;
			s1 = (ll)s1 * s2 % mod ; L = R + 1 ;

			ans = (ans + (ll)res * s1) % mod ;
		}

		printf("%d\n" , ans) ;
	}

	return 0 ;
}