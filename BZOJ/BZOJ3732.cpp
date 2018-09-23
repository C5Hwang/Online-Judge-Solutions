#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 15e3 + 10 , MAX_M = 3e4 + 10 , lgN = 20 + 5 ;

struct Edge {
	int x , y , v ;
}eg[MAX_M] ;
struct Link {
	int num , val ;
	Link *next ;
}list[MAX_N << 1] ;

Link *head[MAX_N] ;
int n , m , k , cur , lim ;
int fa[MAX_N] , dep[MAX_N] , f[MAX_N][lgN] , g[MAX_N][lgN] ;

bool cmp(Edge a , Edge b) {return a.v < b.v ;}

int findset(int x) {return fa[x] == x ? x : (fa[x] = findset(fa[x])) ;}

void ins(int x , int y , int v) {
	list[cur].num = y ;
	list[cur].val = v ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

void dfs(int x) {
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == f[x][0]) continue ;

		f[nx][0] = x ; g[nx][0] = h->val ; dep[nx] = dep[x] + 1 ;
		dfs(nx) ;
	}
}

void dp() {
	for (int j = 1 ; j < lim ; ++j)
		for (int i = 1 ; i <= n ; ++i)
			f[i][j] = f[f[i][j - 1]][j - 1] ;

	for (int j = 1 ; j < lim ; ++j)
		for (int i = 1 ; i <= n ; ++i)
			g[i][j] = std::max(g[i][j - 1] , g[f[i][j - 1]][j - 1]) ;
}

int lca(int x , int y) {
	if (dep[x] < dep[y]) std::swap(x , y) ;

	for (int i = lim ; i >= 0 ; --i) {
		int tmp = f[x][i] ;
		if (dep[tmp] >= dep[y]) x = tmp ;
	}
	if (x == y) return y ;

	for (int i = lim ; i >= 0 ; --i) {
		int tx = f[x][i] , ty = f[y][i] ;
		if (tx != ty) x = tx , y = ty ;
	}
	return f[x][0] ;
}

int jump(int x , int d) {
	int ans = 0 ;
	for (int i = lim ; i >= 0 ; --i) {
		int tmp = f[x][i] ;
		if (dep[tmp] >= dep[d]) ans = std::max(ans , g[x][i]) , x = tmp ;
	}
	return ans ;
}

int main() {
	scanf("%d %d %d" , &n , &m , &k) ;
	for (lim = 0 ; (1 << lim) <= n ; ++lim) ;
	for (int i = 0 ; i < m ; ++i) {
		Edge *p = &eg[i] ;
		scanf("%d %d %d" , &p->x , &p->y , &p->v) ;
	}

	///

	std::sort(eg + 0 , eg + m , cmp) ;
	for (int i = 1 ; i <= n ; ++i) fa[i] = i ;
	for (int i = 0 ; i < m ; ++i) {
		Edge *p = &eg[i] ;
		int fx = findset(p->x) , fy = findset(p->y) ;

		if (fx != fy) {fa[fx] = fy ; ins(p->x , p->y , p->v) ; ins(p->y , p->x , p->v) ;}
	}

	///

	f[1][0] = 1 ; dep[1] = 1 ;
	dfs(1) ;
	dp() ;

	for (int i = 0 ; i < k ; ++i) {
		int x , y , d ;
		scanf("%d %d" , &x , &y) ;
		d = lca(x , y) ;
		
		printf("%d\n" , std::max(jump(x , d) , jump(y , d))) ;
	}

	return 0 ;
}
