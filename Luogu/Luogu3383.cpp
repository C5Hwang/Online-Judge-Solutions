#include <stdio.h>
#include <stdlib.h>

#define ll long long

const int MAX_N = 1e7 + 10 ;

bool chk[MAX_N] ;
int n , m , tot , prime[MAX_N] ;

void euler() {
	chk[1] = 1 ;
	for (int i = 2 ; i <= n ; ++i) {
		if (!chk[i]) prime[tot++] = i ;
		for (int j = 0 ; j < tot ; ++j) {
			ll tmp = (ll)i * prime[j] ;
			if (tmp > n) break ;

			chk[tmp] = 1 ;
			if (!(i % prime[j])) break ;
		}
	}
}

int main() {
	scanf("%d %d" , &n , &m) ;

	euler() ;
	for (int i = 0 ; i < m ; ++i) {
		int a ; scanf("%d" , &a) ;
		if (!chk[a]) printf("Yes\n") ;
		else printf("No\n") ;
	}

	return 0 ;
}
