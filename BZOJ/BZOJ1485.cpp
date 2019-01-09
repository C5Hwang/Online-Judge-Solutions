#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 2e6 + 10 ;

bool vis[MAX_N] ;
int n , P , tot , pri[MAX_N] , fir[MAX_N] , cnt[MAX_N] ;

void initpri() {
	int m = n << 1 ;
	for (int i = 2 ; i <= m ; ++i) {
		if (!vis[i]) pri[tot++] = i , fir[i] = i ;

		for (int j = 0 ; j < tot ; ++j) {
			int tmp = i * pri[j] ;
			if (tmp > m) break ;

			vis[tmp] = 1 ; fir[tmp] = pri[j] ;
			if (!(i % pri[j])) break ;
		}
	}
}

void count(int x , int a) {
	for (int i = 1 ; i <= x ; ++i) {
		int t = i ;
		for (; t > 1 ; t /= fir[t]) cnt[fir[t]] += a ;
	}
}

int qpow(int x , int t) {
	int tmp = x , s = 1 ;
	for (; t ; t >>= 1 , tmp = (ll)tmp * tmp % P)
		if (t & 1) s = (ll)s * tmp % P ;

	return s ;
}

int main() {
	scanf("%d %d" , &n , &P) ;
	initpri() ;

	///

	count(n << 1 , 1) ; count(n , -1) ; count(n + 1 , -1) ;

	int s = 1 ;
	for (int i = 0 ; i < tot ; ++i) {
		int tmp = qpow(pri[i] , cnt[pri[i]]) ;
		s = (ll)s * tmp % P ;
	}

	printf("%d\n" , s) ;

	return 0 ;
}