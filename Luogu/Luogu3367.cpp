#include <stdio.h>
#include <stdlib.h>

const int MAX_N = 1e4 + 10 ;

int n , m , fa[MAX_N] ;

int findset(int x) {return fa[x] == x ? x : (fa[x] = findset(fa[x])) ;}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 1 ; i <= n ; ++i) fa[i] = i ;

	for (int i = 0 ; i < m ; ++i) {
		int op , x , y ; scanf("%d %d %d" , &op , &x , &y) ;

		int fx = findset(x) , fy = findset(y) ;

		if (op == 1) fa[fx] = fy ;
		else {
			if (fx == fy) printf("Y\n") ;
			else printf("N\n") ;
		}
	}

	return 0 ;
}
