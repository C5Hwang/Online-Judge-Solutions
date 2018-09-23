#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long 
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 2e3 + 10 ;

struct Link {
	int num , val ;
	Link *next ;
}list[MAX_N << 1] ;

Link *head[MAX_N] ;
int n , m , cur , siz[MAX_N] ;
ll f[MAX_N][MAX_N] , g[MAX_N] ;

void ins(int x , int y , int v) {
	list[cur].num = y ;
	list[cur].val = v ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

void dp(int x , int nx , int v) {
	for (int i = 0 ; i <= siz[x] + siz[nx] ; ++i) g[i] = 0 ;

	for (int i = 0 ; i <= siz[x] ; ++i)
		for (int j = 0 ; j <= siz[nx] ; ++j) {
			ll tot = j * (m - j) + (siz[nx] - j) * (n - siz[nx] - m + j) ;
			g[i + j] = std::max(g[i + j] , f[nx][j] + f[x][i] + tot * v) ;
		}

	for (int i = 0 ; i <= siz[x] + siz[nx] ; ++i) f[x][i] = g[i] ;
}

void dfs(int x , int fa) {
	siz[x] = 1 ;
	f[x][0] = 0 ; f[x][1] = 0 ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa) continue ;

		dfs(nx , x) ;
		dp(x , nx , h->val) ;

		siz[x] += siz[nx] ;
	}
}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 1 ; i < n ; ++i) {
		int x , y , v ;
		scanf("%d %d %d" , &x , &y , &v) ;
		ins(x , y , v) ; ins(y , x , v) ;
	}

	///

	dfs(1 , -1) ;

	printf("%lld\n" , f[1][m]) ;

	return 0 ;
}