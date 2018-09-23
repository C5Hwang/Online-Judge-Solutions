#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 5e5 + 10 ;

char st[MAX_N] ;
int cur , f[MAX_N][2] , g[MAX_N][2] ;

void dfs(int x) {
	int sta = st[x] - '0' ;
	if (sta == 0) {
		f[x][0] = g[x][0] = 0 ;
		f[x][1] = g[x][1] = 1 ;
	}
	else if (sta == 1) {
		int son = ++cur ; dfs(son) ;

		f[x][1] = f[son][0] + 1 ; g[x][1] = g[son][0] + 1 ;
		f[x][0] = std::max(f[son][0] , f[son][1]) ;
		g[x][0] = std::min(g[son][0] , g[son][1]) ;
	}
	else {
		int L , R ;
		L = ++cur ; dfs(L) ;
	   	R = ++cur ; dfs(R) ;

		f[x][1] = f[L][0] + f[R][0] + 1 ;
		g[x][1] = g[L][0] + g[R][0] + 1 ;
		f[x][0] = std::max(f[L][0] + f[R][1] , f[L][1] + f[R][0]) ;
		g[x][0] = std::min(g[L][0] + g[R][1] , g[L][1] + g[R][0]) ;
	}
}

int main() {
	scanf("%s" , st) ;
	dfs(0) ;
	printf("%d %d\n" , std::max(f[0][1] , f[0][0]) , std::min(g[0][0] , g[0][1])) ;

	return 0 ;
}
