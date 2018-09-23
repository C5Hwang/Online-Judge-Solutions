#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 100 + 10 , MAX_K = 200 + 10 , INF = 0x3f3f3f3f ;

struct Link {
	int num ;
	Link *next ;
}list[2 * MAX_N] ;

Link *head[MAX_N] ;
int n , k , cur , v[MAX_N] , f[MAX_N][MAX_K] , g[MAX_N][MAX_K] ;

void dfs(int x , int fa) {
	f[x][0] = g[x][0] = v[x] ;
	for (int i = 1 ; i <= k ; ++i)
		f[x][i] = g[x][i] = -INF ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa) continue ;
		dfs(nx , x) ;

		///

		for (int i = k ; i > 0 ; --i)
			for (int p = 1 ; p <= i ; ++p) {
				g[x][i] = std::max(g[x][i] , g[nx][p - 1] + f[x][i - p]) ;
				if (p > 1) g[x][i] = std::max(g[x][i] , g[x][i - p] + f[nx][p - 2]) ;
			}
		for (int i = k ; i > 1 ; --i)
			for (int p = 2 ; p <= i ; ++p)
				f[x][i] = std::max(f[x][i] , f[x][i - p] + f[nx][p - 2]) ;
	}
}

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

void init() {
	cur = 0 ;
	memset(head , 0 , sizeof(head)) ;
}

int main() {
	while (scanf("%d %d" , &n , &k) != EOF)	{
		init() ;

		for (int i = 1 ; i <= n ; ++i)
			scanf("%d" , &v[i]) ;

		for (int i = 1 ; i < n ; ++i) {
			int x , y ;
			scanf("%d %d" , &x , &y) ;
			ins(x , y) ; ins(y , x) ;
		}

		///

		dfs(1 , 0) ;

		int res = 0 ;

		for (int i = 0 ; i <= k ; ++i)
			res = std::max(res , std::max(f[1][i] , g[1][i])) ;

		printf("%d\n" , res) ;
	}

	return 0 ;
}
