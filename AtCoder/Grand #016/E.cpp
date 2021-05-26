#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 400 + 10 , MAX_M = 1e5 + 10 ;

int n , m , u[MAX_M] , v[MAX_M] ;
bool ali[MAX_N] , ap[MAX_N] , st[MAX_N][MAX_N] ;

void check(int x) {
	ali[x] = 1 ;
	for (int i = 1 ; i <= n ; ++i) ap[i] = 0 ;

	ap[x] = 1 ;
	for (int i = m ; i ; --i) {
		int p = u[i] , q = v[i] ;
		if (ap[q]) std::swap(p , q) ;
		if (ap[q]) {ali[x] = 0 ; return ;}
		if (ap[p]) ap[q] = 1 ;
	}

	for (int i = 1 ; i <= n ; ++i) st[x][i] = ap[i] ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 1 ; i <= m ; ++i) scanf("%d %d" , &u[i] , &v[i]) ;

	///

	for (int i = 1 ; i <= n ; ++i) check(i) ;

	int ans = 0 ;
	for (int i = 1 ; i <= n ; ++i)
		for (int j = i + 1 ; j <= n ; ++j) {
			if (!ali[i] || !ali[j]) continue ;

			bool ok = 1 ;
			for (int k = 1 ; k <= n && ok ; ++k) if (st[i][k] && st[j][k]) ok = 0 ;

			if (ok) ++ans ;
		}
	printf("%d\n" , ans) ;

	return 0 ;
}