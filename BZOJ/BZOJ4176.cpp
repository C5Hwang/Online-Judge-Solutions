#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int lim = 2e6 , MAX_N = 2e6 + 10 , mod = 1e9 + 7 ;

bool vis[MAX_N] ;
int sum[MAX_N] , ans[MAX_N] ;
int n , m , tot , mu[MAX_N] , pri[MAX_N] ;

void init() {
	mu[1] = sum[1] = 1 ;
	m = std::min(n , lim) ;

	for (int i = 2 ; i <= m ; ++i) {
		if (!vis[i]) {mu[i] = -1 ; pri[tot++] = i ;}

		for (int j = 0 ; j < tot ; ++j) {
			int tmp = i * pri[j] ;
			if (tmp > m) break ;
			vis[tmp] = 1 ;

			if (i % pri[j]) mu[tmp] = -mu[i] ;
			else {mu[tmp] = 0 ; break ;}
		}
		sum[i] = (sum[i - 1] + mod + mu[i]) % mod ;
	}
}

int count(int n) {
	if (n <= lim) return sum[n] ;
	if (ans[m / n] != -1) return ans[m / n] ;

	int res = 1 ;
	for (int L = 2 ; L <= n ;) {
		int t = n / L , R = n / t ;

		res = (res + mod - (ll)count(t) * (R - L + 1) % mod) % mod ; L = R + 1 ;
	}

	return (ans[m / n] = res) ;
}

int getsum(int n) {
	int res = 0 ;

	for (int L = 1 ; L <= n ;) {
		int t = n / L , R = n / t ;

		res = (res + (ll)t * (R - L + 1)) % mod ; L = R + 1 ;
	}

	return (ll)res * res % mod ;
}

int main() {
	scanf("%d" , &n) ;
	init() ;

	int last = 0 , res = 0 ;
	for (int L = 1 ; L <= n ;) {
		int t = n / L , R = n / t ;

		m = R ; for (int i = 0 ; i <= R / lim ; ++i) ans[i] = -1 ;
		int psum = count(R) , S = getsum(t) ;

		res = (res + (ll)S * (psum + mod - last)) % mod ; L = R + 1 ; last = psum ;
	}

	printf("%d\n" , res) ;

	return 0 ;
}