#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 3e4 + 10 , MAX_M = 1e5 + 10 , MAX_Q = 4e4 + 10 ;

struct Link {
	int num ;
	bool flag ;
	Link *next , *reg ;
}list[MAX_M << 1] ;
struct Edge {
	int ty , x , y ;
}eg[MAX_M] , qry[MAX_Q] ;
struct Node {
	int sum , lazy ;
}tre[MAX_N << 2] ;

std::set<int> ct[MAX_N] ;

Link *head[MAX_N] ;
int ti , dfn[MAX_N] , low[MAX_N] , dcc[MAX_N] ;
int n , m , q , cnt , cur , tans , ans[MAX_Q] ;
int fa[MAX_N] , lfa[MAX_N] , siz[MAX_N] , dep[MAX_N] ;

///

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	list[cur].reg = &list[cur^1] ;
	head[x] = &list[cur++] ;

	list[cur].num = x ;
	list[cur].next = head[y] ;
	list[cur].reg = &list[cur^1] ;
	head[y] = &list[cur++] ;
}

///

void tarjan(int x) {
	dfn[x] = low[x] = ++ti ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (h->flag) continue ;

		if (!dfn[nx]) {
			h->reg->flag = 1 ;
			tarjan(nx) ;

			low[x] = std::min(low[x] , low[nx]) ;
			if (low[nx] > dfn[x]) h->flag = 1 ;
			else h->reg->flag = 0 ;
		}
		else low[x] = std::min(low[x] , dfn[nx]) ;
	}
}

void color(int x) {
	dcc[x] = cnt ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (h->flag || dcc[nx]) continue ;

		color(nx) ;
	}
}

void dfs1(int x) {
	siz[x] = 1 ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa[x]) continue ;

		dep[nx] = dep[x] + 1 ; fa[nx] = x ;
		dfs1(nx) ;
		siz[x] += siz[nx] ;
	}
}

void dfs2(int x , int f) {
	lfa[x] = f ; dfn[x] = ++ti ;

	int hson = -1 , s = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa[x]) continue ;

		if (siz[nx] > s) hson = nx , s = siz[nx] ;
	}

	if (hson != -1) dfs2(hson , f) ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == hson || nx == fa[x]) continue ;

		dfs2(nx , nx) ;
	}
}

///

void build(int t , int x , int y) {
	if (x == y) {
		tre[t].sum = 1 ;
		tre[t].lazy = -1 ;

		return ;
	}

	int mid = (x + y) >> 1 ;
	build(t << 1 , x , mid) ; build(t << 1 | 1 , mid + 1 , y) ;

	tre[t].lazy = -1 ;
	tre[t].sum = tre[t << 1].sum + tre[t << 1 | 1].sum ;
}

void down(int t , int x , int y) {
	if (tre[t].lazy == -1) return ;

	int L = t << 1 , R = t << 1 | 1 , mid = (x + y) >> 1 , a = tre[t].lazy ;

	tre[L].sum = (mid - x + 1) * a ; tre[R].sum = (y - mid) * a ;
	tre[L].lazy = tre[R].lazy = a ;
	tre[t].lazy = -1 ;
}

void modify(int t , int x , int y , int fx , int fy , int a) {
	if (y < fx || fy < x) return ;
	if (fx <= x && y <= fy) {
		tre[t].sum = a * (y - x + 1) ;
		tre[t].lazy = a ;

		return ;
	}

	down(t , x , y) ;
	int mid = (x + y) >> 1 ;
	modify(t << 1 , x , mid , fx , fy , a) ;
	modify(t << 1 | 1 , mid + 1 , y , fx , fy , a) ;

	tre[t].sum = tre[t << 1].sum + tre[t << 1 | 1].sum ;
}

int query(int t , int x , int y , int fx , int fy) {
	if (y < fx || fy < x) return 0 ;
	if (fx <= x && y <= fy) return tre[t].sum ;

	down(t , x , y) ;
	int mid = (x + y) >> 1 ,
		s1 = query(t << 1 , x , mid , fx , fy) ,
		s2 = query(t << 1 | 1 , mid + 1 , y , fx , fy) ;

	return s1 + s2 ;
}

///

int lca(int x , int y) {
	for (; lfa[x] != lfa[y] ;) {
		int fx = lfa[x] , fy = lfa[y] ;
		if (dep[fx] > dep[fy]) x = fa[fx] ;
		else y = fa[fy] ;
	}

	if (dep[x] > dep[y]) return y ;
	else return x ;
}

void cover(int x , int y) {
	int d = lca(x , y) , t = query(1 , 1 , cnt , dfn[d] , dfn[d]) ;

	for (; lfa[x] != lfa[y] ;) {
		if (dep[lfa[x]] < dep[lfa[y]]) std::swap(x , y) ;

		modify(1 , 1 , cnt , dfn[lfa[x]] , dfn[x] , 0) ;
		x = fa[lfa[x]] ;
	}

	if (dep[x] > dep[y]) std::swap(x , y) ;
	modify(1 , 1 , cnt , dfn[x] , dfn[y] , 0) ;

	modify(1 , 1 , cnt , dfn[d] , dfn[d] , t) ;
}

int find(int x , int y) {
	int d = lca(x , y) , res = -query(1 , 1 , cnt , dfn[d] , dfn[d]) ;

	for (; lfa[x] != lfa[y] ;) {
		if (dep[lfa[x]] < dep[lfa[y]]) std::swap(x , y) ;

		res += query(1 , 1 , cnt , dfn[lfa[x]] , dfn[x]) ;
		x = fa[lfa[x]] ;
	}

	if (dep[x] > dep[y]) std::swap(x , y) ;
	res += query(1 , 1 , cnt , dfn[x] , dfn[y]) ;

	return res ;
}

///

int main() {
	n = read() ; m = read() ;
	for (int i = 0 ; i < m ; ++i) {
		Edge *p = &eg[i] ;
		p->x = read() ; p->y = read() ;
	}

	int ty = read() ;
	for (; ty != -1 ; ty = read()) {
		int x , y ; x = read() ; y = read() ;

		if (!ty) ct[x].insert(y) , ct[y].insert(x) ;
		qry[q++] = (Edge){ty , x , y} ;
	}
 
	///

	for (int i = 0 ; i < m ; ++i){
		Edge *p = &eg[i] ;
		if (ct[p->x].find(p->y) == ct[p->x].end())
			ins(p->x , p->y) ;
	}

	tarjan(1) ;
	for (int i = 1 ; i <= n ; ++i)
		if (!dcc[i]) {++cnt ; color(i) ;}

	///

	cur = ti = 0 ;
	for (int i = 1 ; i <= cnt ; ++i) {head[i] = NULL ; dfn[i] = 0 ;}

	for (int i = 0 ; i < m ; ++i) {
		Edge *p = &eg[i] ;
		if (ct[p->x].find(p->y) == ct[p->x].end()) {
			p->x = dcc[p->x] ; p->y = dcc[p->y] ;

			if (p->x != p->y) ins(p->x , p->y) ;
		}
	}

	fa[1] = 1 ; dep[1] = 1 ;
	dfs1(1) ; dfs2(1 , 1) ;

	build(1 , 1 , cnt) ;

	///

	for (; q-- ;) {
		Edge *p = &qry[q] ;
		p->x = dcc[p->x] ; p->y = dcc[p->y] ;

		if (!p->ty) cover(p->x , p->y) ;
		else ans[tans++] = find(p->x , p->y) ;
	}

	for (; tans-- ;) printf("%d\n" , ans[tans]) ;

	return 0 ;
}