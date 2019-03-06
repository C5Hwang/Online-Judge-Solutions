#include <queue>
#include <stack>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 400 + 10 , MAX_P = 5e3 + 10 , MAX_M = 4e3 + 10 , INF = 0x3f3f3f3f ;

struct Edge {int x , y , val ;}qry[MAX_M] ;
struct data {int num , cap , reg ; bool r ;} ;
struct Link {
	int num , val ;
	Link *next ;
}list[MAX_M << 1] ;

std::queue<int> que ;
std::stack<int> sta ;
std::vector<data> eg[MAX_P] ;

ll dis[MAX_N] ;
bool vis[MAX_N] ;
Link *head[MAX_N] ;
int n , m , ti , cur , dep[MAX_P] , ap[MAX_P] , a[MAX_N] ;
int tot , dfn[MAX_P] , low[MAX_P] , state[MAX_P] , idx[MAX_P] ;

///

int dfs(int x , int f) {
	if (x == n || !f) return f ;

	int sum = 0 , siz = eg[x].size() ;
	for (int i = 0 ; i < siz ; ++i) {
		int nx = eg[x][i].num ;
		if (dep[nx] != dep[x] + 1) continue ;

		int nf = dfs(nx , std::min(f , eg[x][i].cap)) ;
		sum += nf ; eg[nx][eg[x][i].reg].cap += nf ;
		f -= nf ; eg[x][i].cap -= nf ;
	}
	if (f) dep[x] = -1 ;

	return sum ;
}

bool bfs() {
	que.push(1) ;
	dep[1] = 1 ; ap[1] = ++ti ;

	for (; !que.empty() ;) {
		int x = que.front() , siz = eg[x].size() ; que.pop() ;

		for (int i = 0 ; i < siz ; ++i) {
			int nx = eg[x][i].num ;
			if (!eg[x][i].cap || ap[nx] == ti) continue ;

			que.push(nx) ;
			dep[nx] = dep[x] + 1 ; ap[nx] = ti ;
		}
	}

	return ap[n] == ti ;
}

inline ll dinic() {
	ll sum = 0 ;
	for (; bfs() ; sum += dfs(1 , INF)) ;

	return sum ;
}

///

void spfa() {
	for (int i = 1 ; i <= n ; ++i) dis[i] = 1e15 ;
	dis[1] = 0 ; vis[1] = 1 ; que.push(1) ;

	for (; !que.empty() ;) {
		int x = que.front() ;
		vis[x] = 0 ; que.pop() ;

		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (dis[nx] <= dis[x] + h->val) continue ;

			dis[nx] = dis[x] + h->val ;
			if (!vis[nx]) vis[nx] = 1 , que.push(nx) ;
		}
	}
}

void tarjan(int x) {
	state[x] = 1 ; sta.push(x) ;
	dfn[x] = low[x] = ++ti ;

	int siz = eg[x].size() ;
	for (int i = 0 ; i < siz ; ++i) {
		int nx = eg[x][i].num ;
		if (!eg[x][i].cap) continue ;

		if (!state[nx]) tarjan(nx) , low[x] = std::min(low[x] , low[nx]) ;
		else if (state[nx] == 1) low[x] = std::min(low[x] , dfn[nx]) ;
	}

	if (dfn[x] <= low[x]) {
		++tot ;
		for (; sta.top() != x ;) {
			int t = sta.top() ; sta.pop() ;
			idx[t] = tot ; state[t] = 2 ;
		}
		idx[x] = tot ; state[x] = 2 ; sta.pop() ;
	}
}

///

void init() {
	cur = 0 ;
	memset(head , 0 , sizeof(head)) ;
	memset(state , 0 , sizeof(state)) ;
	for (int i = 1 ; i <= n + m ; ++i) eg[i].clear() ;
}

void add_edge(int x , int y , int v) {
	list[cur].num = y ;
	list[cur].val = v ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

void ins(int x , int y , int v) {
	int p1 = eg[x].size() , p2 = eg[y].size() ;

	eg[x].push_back((data){y , v , p2 , 0}) ;
	eg[y].push_back((data){x , 0 , p1 , 1}) ;
}

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

///

int main() {
	int CASE = read() ;
	for (; CASE-- ;) {
		init() ;
		n = read() ; m = read() ; a[n] = INF ;
		for (int i = 1 ; i < n ; ++i) a[i] = read() ;
		for (int i = 1 ; i <= m ; ++i) {
			int x , y , v ;
			x = read() ; y = read() ; v = read() ;
			qry[i] = (Edge){x , y , v} ;

			add_edge(x , y , v) ; add_edge(y , x , v) ;
		}

		///

		spfa() ;
		for (int i = 1 ; i <= m ; ++i) {
			Edge *p = &qry[i] ;
			if (dis[p->x] + p->val == dis[p->y])
				ins(p->x , n + i , a[p->x]) , ins(n + i , p->y , a[p->y]) ;
			else if (dis[p->y] + p->val == dis[p->x])
				ins(p->y , n + i , a[p->y]) , ins(n + i , p->x , a[p->x]) ;
		}

		ll ans = dinic() ;
		bool ok = 1 ; ti = tot = 0 ;

		for (int i = 1 ; i <= n + m ; ++i) if (!state[i]) tarjan(i) ;
		for (int x = 1 ; x <= n + m && ok ; ++x) {
			int siz = eg[x].size() ;

			for (int i = 0 ; i < siz ; ++i) {
				int nx = eg[x][i].num ;
				if (eg[x][i].cap || eg[x][i].r || idx[x] == idx[nx]) continue ;

				ok &= (idx[x] == idx[1] && idx[nx] == idx[n]) ;
			}
		}

		if (ok) printf("Yes ") ; else printf("No ") ;
		printf("%lld\n" , ans) ;
	}

	return 0 ;
}