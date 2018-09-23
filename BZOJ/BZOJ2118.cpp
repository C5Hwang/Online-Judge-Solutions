#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long

const int MAX_N = 12 + 10 , MAX_M = 5e5 + 10 ;

bool ap[MAX_M] ;
ll ql , qr , d[MAX_M] ;
int n , m , L , R , a[MAX_N] , queue[MAX_M] ;

ll getans(ll x) {
	ll s = 0 ;
	for (int i = 0 ; i < m ; ++i)
		if (d[i] <= x) s += (x - d[i]) / m + 1 ;

	return s ;
}

int main() {
	scanf("%d %lld %lld" , &n , &ql , &qr) ; m = MAX_M ;
	for (int i = 0 ; i < n ; ++i) {
		scanf("%d" , &a[i]) ;
		if (!a[i]) {--i ; --n ; continue ;}
		m = std::min(m , a[i]) ;
	}

	///
	
	for (int i = 1 ; i < m ; ++i) d[i] = qr + 1 ;
	L = R = 0 ; queue[0] = 0 ;
	while (L <= R) {
		int x = queue[(L++) % m] ; ap[x] = 0 ;
		for (int i = 0 ; i < n ; ++i) {
			int y = (x + a[i]) % m ;
			if (d[y] > d[x] + a[i]) {
				d[y] = d[x] + a[i] ;
				if (!ap[y]) {queue[(++R) % m] = y ; ap[y] = 1 ;}
			}
		}
	}

	printf("%lld\n" , getans(qr) - getans(ql - 1)) ;

	return 0 ;
}
