#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 2e5 + 10 ;

bool ap[MAX_N] ;
int n , a[MAX_N] , fa[MAX_N] , ti[MAX_N] ;

int findset(int x) {return fa[x] == x ? x : (fa[x] = findset(fa[x])) ;}

int main() {
	scanf("%d" , &n) ;
	for (int i = 1 ; i <= n ; ++i) scanf("%d" , &a[i]) ;

	///

	int ans = n ;
	for (int i = 1 ; i <= n ; ++i) fa[i] = i ;
	for (int i = 1 ; i <= n ; ++i)
		if (!ap[i]) {
			ap[i] = 1 ; ti[i] = 1 ;

			int p = i ;
			for (; ;) {
				int q = a[p] , fp = findset(p) , fq = findset(q) ;
				if (ap[q]) {
					if (fp == fq) ans = std::min(ans , abs(ti[p] - ti[q] + 1)) ;
					break ;
				}

				ti[q] = ti[p] + 1 ; ap[q] = 1 ;
				fa[fq] = fp ; p = q ;
			}
		}

	printf("%d\n" , ans) ;

	return 0 ;
}
