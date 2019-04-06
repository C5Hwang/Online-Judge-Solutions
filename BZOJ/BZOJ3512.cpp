#include <map>
#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int lim = 1e6 , MAX_N = 1e5 + 10 , MAX_M = 1e6 + 10 , mod = 1e9 + 7 ;

std::map<int , int> S[MAX_N] ;

int n , m , tot , pri[MAX_M] ;
int phi[MAX_M] , sum[MAX_M] , ans[MAX_M] ;

void init() {
	int T = std::min(lim , std::max(n , m)) ;

	phi[1] = sum[1] = 1 ;
	for (int i = 2 ; i <= T ; ++i) {
		if (!phi[i]) {phi[i] = i - 1 ; pri[tot++] = i ;}

		for (int j = 0 ; j < tot ; ++j) {
			int tmp = i * pri[j] ;
			if (tmp > T) break ;

			if (i % pri[j]) phi[tmp] = (ll)phi[i] * (pri[j] - 1) % mod ;
			else {phi[tmp] = (ll)phi[i] * pri[j] % mod ; break ;}
		}

		sum[i] = (sum[i - 1] + phi[i]) % mod ;
	}
}

int getsum(int T) {
	if (T <= lim) return sum[T] ;
	if (ans[m / T]) return ans[m / T] ;

	int res = (((ll)T * (T + 1)) >> 1) % mod ;
	for (int L = 2 ; L <= T ;) {
		int t = T / L , R = T / t ;

		res = (res + mod - (ll)getsum(t) * (R - L + 1) % mod) % mod ; L = R + 1 ;
	}

	return (ans[m / T] = res) ;
}

int calc(int x , int y) {
	if (!y) return 0 ;
	if (x == 1) return getsum(y) ;
	if (S[x].count(y)) return S[x][y] ;

	int res = 0 ;
	for (int i = 1 ; i * i <= x ; ++i) {
		if (x % i) continue ;

		int j = x / i ;
		res = (res + (ll)phi[x / i] * calc(i , y / i)) % mod ;
		res = (res + (ll)phi[x / j] * calc(j , y / j)) % mod ;
	}

	return (S[x][y] = res) ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	init() ; getsum(m) ;

	///

	int ans = 0 ;
	for (int i = 1 ; i <= n ; ++i) {
		int p = 1 , tmp = i ;
		for (int j = 0 ; j < tot ; ++j) {
			if (pri[j] * pri[j] > tmp) break ;
			if (tmp % pri[j]) continue ;

			for (; !(tmp % pri[j]) ; tmp /= pri[j]) ;
			p *= pri[j] ;
		}
		if (tmp > 1) p *= tmp ;

		///

		int q = i / p ;
		ans = (ans + (ll)q * calc(p , m)) % mod ;
	}

	printf("%d\n" , ans) ;

	return 0 ;
}