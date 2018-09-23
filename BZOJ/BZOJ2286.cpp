#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const ll INF = 1e15 ;
const int MAX_N = 25e4 + 10 , lgN = 20 + 5 , K = 20 ;

struct Link {
	int num ; ll val ;
	Link *next ;
}list[MAX_N << 1] ;

bool kv[MAX_N] ;
Link *head[MAX_N] ;
ll c[MAX_N] , g[MAX_N][lgN] ;
int f[MAX_N][lgN] , dfn[MAX_N] , dep[MAX_N] ;
int n , m , tot , cur , cnt , tp , ver[MAX_N] , sta[MAX_N] ;

///

void ins(int x , int y , ll v) {
	list[cur].num = y ;
	list[cur].val = v ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

void dfs(int x) {
	dfn[x] = ++cnt ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == f[x][0]) continue ;

		dep[nx] = dep[x] + 1 ; f[nx][0] = x ; g[nx][0] = h->val ;
		dfs(nx) ;
	}
}

///

ll find(int x , int y) {
	if (dep[x] < dep[y]) std::swap(x , y) ;

	ll s = INF ;
	for (int i = K ; i >= 0 ; --i) {
		int tmp = f[x][i] ;
		if (dep[tmp] >= dep[y]) {
			s = std::min(s , g[x][i]) ; x = tmp ;
		}
	}

	return s ;
}

int lca(int x , int y) {
	if (dep[x] < dep[y]) std::swap(x , y) ;

	for (int i = K ; i >= 0 ; --i) {
		int tmp = f[x][i] ;
		if (dep[tmp] >= dep[y]) x = tmp ;
	}

	if (x == y) return x ;

	for (int i = K ; i >= 0 ; --i) {
		int tx = f[x][i] , ty = f[y][i] ;
		if (tx != ty) x = tx , y = ty ;
	}

	return f[x][0] ;
}

///

bool cmp(int x , int y) {return dfn[x] < dfn[y] ;}

void build(int k) {
	std::sort(ver + 0 , ver + k , cmp) ;
	sta[tp++] = ver[0] ;

	for (int i = 1 ; i < k ; ++i) {
		int u = ver[i] , v = sta[tp - 1] , d = lca(u , v) ;
		kv[u] = 1 ;

		if (v == d) sta[tp++] = u ;
		else {
			for (; tp - 2 >= 0 && dep[sta[tp - 2]] >= dep[d] ;) {
				ins(sta[tp - 2] , sta[tp - 1] , find(sta[tp - 2] , sta[tp - 1])) ;
				--tp ;
			}

			if (sta[tp - 1] != d) {
				ins(d , sta[tp - 1] , find(d , sta[tp - 1])) ;
				sta[tp - 1] = d ; ver[tot++] = d ;
			}

			sta[tp++] = u ;
		}
	}

	for (; tp ;) {
		int u = sta[--tp] ;

		if (tp) ins(sta[tp - 1] , u , find(sta[tp - 1] , u)) ;
	}
}

int dp(int x , ll v) {
	c[x] = v ;

	ll s = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		dp(nx , h->val) ; s += c[nx] ;
	}

	if (!kv[x]) c[x] = std::min(c[x] , s) ;
}

void init() {
	cur = 0 ;
	for (int i = 0 ; i < tot ; ++i) {
		int u = ver[i] ;
		kv[u] = 0 ; head[u] = NULL ;
	}
}

///

int main() {
	scanf("%d" , &n) ; ver[tot++] = 0 ;
	for (int i = 1 ; i < n ; ++i) {
		int x , y , v ; ver[tot++] = i ;
		scanf("%d %d %d" , &x , &y , &v) ;
		ins(x , y , v) ; ins(y , x , v) ;
	}
	ver[tot++] = n ;

	///

	ins(0 , 1 , INF) ;
	f[0][0] = 0 ; g[0][0] = INF ; dep[0] = 1 ;
	dfs(0) ;

	for (int j = 1 ; j <= K ; ++j)
		for (int i = 0 ; i <= n ; ++i)
			f[i][j] = f[f[i][j - 1]][j - 1] ;
	for (int j = 1 ; j <= K ; ++j)
		for (int i = 0 ; i <= n ; ++i)
			g[i][j] = std::min(g[f[i][j - 1]][j - 1] , g[i][j - 1]) ;

	///

	scanf("%d" , &m) ;
	for (int i = 0 ; i < m ; ++i) {
		init() ;

		scanf("%d" , &tot) ;
		for (int i = 0 ; i < tot ; ++i) scanf("%d" , &ver[i]) ;
		ver[tot++] = 0 ;

		build(tot) ;
		dp(0 , INF) ;

		printf("%lld\n" , c[0]) ;
	}

	return 0 ;
}