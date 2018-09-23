#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int L = 60 , MAX_L = 60 + 5 , mod = 1e7 + 7 ;

ll n , f[MAX_L][MAX_L][2] ;

int qpow(int a , ll t) {
	if (!t) return 1 ;

	int s = qpow(a , t >> 1) ;
	s = (ll)s * s % mod ;
	if (t & 1) s = (ll)s * a % mod ;

	return s ;
}

int main() {
	scanf("%lld" , &n) ;

	///

	f[L][0][1] = 1 ;
	for (int p = L ; p ; --p)
		for (int s = 0 ; s <= L ; ++s)
			for (int sta = 0 ; sta < 2 ; ++sta)
				for (int c = 0 ; c < 2 ; ++c) {
					int q = p - 1 , nc = (n & ((ll)1 << q)) ? 1 : 0 ;

					if (c > nc && sta) continue ;
					int nsta = (c == nc) & sta ;

					f[q][s + c][nsta] += f[p][s][sta] ;
				}

	///

	int ans = 1 ;
	for (int i = 1 ; i <= L ; ++i) {
		ll sum = f[0][i][0] + f[0][i][1] ;
		int tmp = qpow(i , sum) ;

		ans = (ll)ans * tmp % mod ;
	}

	printf("%d\n" , ans) ;

	return 0 ;
}