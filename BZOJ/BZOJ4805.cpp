#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG pritnf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int lim = 2e6 , MAX_N = 2e6 + 10 ;

ll sum[MAX_N] , ans[MAX_N] ;
int n , tot , phi[MAX_N] , pri[MAX_N] ;

void init() {
	n = lim ;

	phi[1] = 1 ;
	for (int i = 2 ; i <= n ; ++i) {
		if (!phi[i]) {phi[i] = i - 1 ; pri[tot++] = i ;}

		for (int j = 0 ; j < n ; ++j) {
			int tmp = i * pri[j] ;
			if (tmp > n) break ;

			if (i % pri[j]) phi[tmp] = phi[i] * phi[pri[j]] ;
			else {phi[tmp] = phi[i] * pri[j] ; break ;}
		}
	}

	for (int i = 1 ; i <= n ; ++i) sum[i] = sum[i - 1] + phi[i] ;
}

ll getans(int m) {
	if (m <= lim) return sum[m] ;
	if (ans[n / m]) return ans[n / m] ;

	ll res = ((ll)m * (m + 1)) >> 1 ;

	int L = 2 ;
	for (; L <= m ;) {
		int t = m / L , R = m / t ;
		res -= getans(t) * (R - L + 1) ; L = R + 1 ;
	}

	return (ans[n / m] = res) ;
}

int main() {
	init() ;
	scanf("%d" , &n) ;

	printf("%lld\n" , getans(n)) ;

	return 0 ;
}