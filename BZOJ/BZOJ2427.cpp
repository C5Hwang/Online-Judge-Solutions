#include <stack>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAX_N = 100 + 10 , MAX_M = 500 + 10 , INF = 0x3f3f3f3f ;

struct Link {
	int num ;
   	Link *next ;
}list[MAX_N] ;
struct Edge {
	int x , y ;
}ed[MAX_N] ;

std::stack<int> sta ;

///

Link *head[MAX_N] ;
bool fa[MAX_N] ;
int n , m , cur , w[MAX_N] , v[MAX_N] , f[MAX_N][MAX_M] ;
int T , low[MAX_N] , dfn[MAX_N] , col[MAX_N] , state[MAX_N] ;

///

void dfs(int x) {
	low[x] = dfn[x] = ++T ;
	state[x] = 1 ; sta.push(x) ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;

		if (state[nx] == 2) continue ;
		if (!state[nx]) dfs(nx) ;
		low[x] = std::min(low[x] , low[nx]) ;
	}

	if (low[x] == dfn[x]) {
		int nw = w[x] , nv = v[x] ;
		col[x] = x ; state[x] = 2 ;

		while (sta.top() != x) {
			int nx = sta.top() ; sta.pop() ;
			col[nx] = x ; state[nx] = 2 ;
			nw += w[nx] ; nv += v[nx] ;
		}

		sta.pop() ; w[x] = nw ; v[x] = nv ;
	}
}

void DP(int x) {
	if (w[x] < m) f[x][w[x]] = v[x] ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		DP(nx) ;
		
		for (int i = m ; i > 0 ; --i)
			for (int j = 0 ; j <= i ; ++j)
				f[x][i] = std::max(f[x][i] , f[x][i - j] + f[nx][j]) ;
	}
}

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

///

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 0 ; i <= n ; ++i)
		for (int j = 0 ; j <= m ; ++j) f[i][j] = -INF ;

	///

	for (int i = 1 ; i <= n ; ++i) scanf("%d" , &w[i]) ;
	for (int i = 1 ; i <= n ; ++i) scanf("%d" , &v[i]) ;
	for (int i = 1 ; i <= n ; ++i) {
		int j ; scanf("%d" , &j) ;
		ins(j , i) ; ed[i] = (Edge){j , i} ;
	}

	///
	
	for (int i = 1 ; i <= n ; ++i) if (!state[i]) dfs(i) ; 

	cur = 0 ;
	memset(head , 0 , sizeof(head)) ;

	for (int i = 1 ; i <= n ; ++i) {
		int x = ed[i].x , y = ed[i].y ;
		if (!x || !y) continue ;
		if (col[x] == col[y]) continue ;

		ins(col[x] , col[y]) ; fa[y] = 1 ;
	}

	///
	
	for (int i = 1 ; i <= n ; ++i) if (!fa[i] && col[i] == i) ins(0 , i) ;
	DP(0) ;

	int res = 0 ;
	for (int i = 0 ; i <= m ; ++i) res = std::max(res , f[0][i]) ;
	printf("%d\n" , res) ;

	return 0 ;
}
