#include <stack>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 5e5 + 10 ;

struct Link {
	int num ;
	Link *next ;
}list[MAX_N] ;

std::stack<int> sta ;
std::vector<int> scc[MAX_N] ;

Link *head[MAX_N] ;
int dep[MAX_N] , fa[MAX_N] , lfa[MAX_N] , siz[MAX_N] , bk[MAX_N] ;
int n , q , cnt , cur , ti , dfn[MAX_N] , low[MAX_N] , state[MAX_N] , iscc[MAX_N] , bh[MAX_N] ;

///

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
} 

void tarjan(int x) {
	sta.push(x) ;
	state[x] = 1 ; dfn[x] = low[x] = ++ti ;

	bool itself = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;

		if (state[nx] == 2) continue ;
		if (nx == x) itself = 1 ;

		if (!state[nx]) {
			tarjan(nx) ;
			low[x] = std::min(low[x] , low[nx]) ;
		}
		else low[x] = std::min(low[x] , dfn[nx]) ;
	}

	if (low[x] == dfn[x]) {
		if (sta.top() == x && !itself) {state[x] = 2 ; sta.pop() ; return ;}

		++cnt ;
		for (; sta.top() != x ; sta.pop()) {
			int a = sta.top() ;

			state[a] = 2 ; iscc[a] = cnt ;
			scc[cnt].push_back(a) ; bh[a] = scc[cnt].size() ;
		}

		sta.pop() ; state[x] = 2 ; iscc[x] = cnt ;
		iscc[x] = cnt ; scc[cnt].push_back(x) ; bh[x] = scc[cnt].size() ;
	}
}

void dfs1(int x , int S) {
	siz[x] = 1 ; bk[x] = S ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (iscc[nx]) continue ;

		dep[nx] = dep[x] + 1 ; fa[nx] = x ;
		dfs1(nx , S) ;
		siz[x] += siz[nx] ;
	}
}

void dfs2(int x , int f) {
	lfa[x] = f ;

	int hson = -1 , s = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (iscc[nx]) continue ;

		if (siz[nx] > s) s = siz[nx] , hson = nx ;
	}

	if (hson != -1) dfs2(hson , f) ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (iscc[nx] || nx == hson) continue ;

		dfs2(nx , nx) ;
	}
}

///

void cal(int sx , int sy , int a , int b) {
	int len = scc[iscc[a]].size() ;
	int ab = bh[a] > bh[b] ? (len - bh[a] + bh[b]) : (bh[b] - bh[a]) ,
		ba = bh[b] > bh[a] ? (len - bh[b] + bh[a]) : (bh[a] - bh[b]) ;

	int sx1 = sx + ab , sy1 = sy + ba ;  //(sx1 , sy)  (sx , sy1)
	int ma1 = std::max(sx1 , sy) , mi1 = std::min(sx1 , sy) ,
		ma2 = std::max(sx , sy1) , mi2 = std::min(sx , sy1) ;

	if (ma1 > ma2) printf("%d %d\n" , sx , sy1) ;
	else if (ma1 < ma2) printf("%d %d\n" , sx1 , sy) ;
	else if (mi1 > mi2) printf("%d %d\n" , sx , sy1) ;
	else if (mi1 < mi2) printf("%d %d\n" , sx1 , sy) ;
	else if (sx1 >= sy) printf("%d %d\n" , sx1 , sy) ;
	else printf("%d %d\n" , sx , sy1) ;
}

int lca(int x , int y) {
	for (; lfa[x] != lfa[y] ;) {
		int fx = lfa[x] , fy = lfa[y] ;
		if (dep[fx] > dep[fy]) x = fa[fx] ;
		else y = fa[fy] ;
	}

	if (dep[x] >= dep[y]) return y ;
	else return x ;
}

///

int main() {
	scanf("%d %d" , &n , &q) ;
	for (int i = 1 ; i <= n ; ++i) {
		int a ; scanf("%d" , &a) ;
		ins(a , i) ;
	}

	///

	for (int i = 1 ; i <= n ; ++i)
		if (!state[i]) tarjan(i) ;

	for (int i = 1 ; i <= cnt ; ++i) {
		int len = scc[i].size() ;
		for (int j = 0 ; j < len ; ++j) {
			int a = scc[i][j] ;

			dep[a] = 0 ; fa[a] = a ;
			dfs1(a , a) ; dfs2(a , a) ;
		}
	}

	///

	for (; q-- ;) {
		int a , b ;
		scanf("%d %d" , &a , &b) ;

		int ba = bk[a] , bb = bk[b] ;
		if (ba == bb) {
			int d = lca(a , b) ;
			printf("%d %d\n" , dep[a] - dep[d] , dep[b] - dep[d]) ;
		}
		else {
			if (iscc[ba] != iscc[bb]) printf("-1 -1\n") ;
			else cal(dep[a] , dep[b] , ba , bb) ;
		}
	}

	return 0 ;
}