#include <bits/stdc++.h>

#define ll long long

const int N = 1e8 , MAX_N = N + 10 , mod = 1e9 + 7 ;

bool ap[MAX_N] ;
int tot , pri[MAX_N] , mu[MAX_N] , phi[MAX_N] , f[MAX_N] ;

int qpow(int a , int t) {
	int s = 1 ;
	for (; t ; t >>= 1 , a = (ll)a * a % mod)
		if (t & 1) s = (ll)s * a % mod ;

	return s ;
}

int main() {
	mu[1] = phi[1] = 1 ;
	for (int i = 2 ; i <= N ; ++i) {
		if (!ap[i]) {mu[i] = -1 ; phi[i] = i - 1 ; pri[tot++] = i ;}

		for (int j = 0 ; j < tot ; ++j) {
			int tmp = i * pri[j] ;
			if (tmp > N) break ;

			ap[tmp] = 1 ;
			if (i % pri[j]) {mu[tmp] = -mu[i] ; phi[tmp] = phi[i] * (pri[j] - 1) ;}
			else {mu[tmp] = 0 ; phi[tmp] = phi[i] * pri[j] ; break ;}
		}
	}

	for (int d = 1 ; d <= N ; ++d)
		for (int k = d ; k <= N ; k += d) {
			int tmp = mu[d] * (N / d) ;
			f[k] += tmp ;
		}

	///

	int ans = 1 ;
	for (int i = 1 ; i <= N ; ++i) {
		int tmp = qpow(i , f[i] - phi[i]) ;
		ans = (ll)ans * tmp % mod ;
	}
	printf("%d\n" , ans) ;

	return 0 ;
}