#include <queue>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 4e3 + 10 , MAX_M = 6e4 + 10 , INF = 0x3f3f3f3f ;

struct Edge {int x , y ;}eg[MAX_M] ;
struct Link {
	int num , cap , idx ;
	Link *next , *reg ;
}list[MAX_M << 1] ;

std::queue<int> que ;
std::stack<int> sta ;

bool ful[MAX_M] ;
Link *head[MAX_N] ;
int n , m , S , T , ti , cur , ap[MAX_N] , dep[MAX_N] ;
int tot , state[MAX_N] , low[MAX_N] , dfn[MAX_N] , id[MAX_N] ;

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

void ins(int x , int y , int v , int p) {
	list[cur].num = y ;
	list[cur].cap = v ;
	list[cur].idx = p ;
	list[cur].next = head[x] ;
	list[cur].reg = &list[cur^1] ;
	head[x] = &list[cur++] ;

	list[cur].num = x ;
	list[cur].cap = 0 ;
	list[cur].idx = m ;
	list[cur].next = head[y] ;
	list[cur].reg = &list[cur^1] ;
	head[y] = &list[cur++] ;
}

int dfs(int x , int f) {
	if (!f || x == T) return f ;

	int s = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (dep[nx] != dep[x] + 1) continue ;

		int nf = dfs(nx , std::min(f , h->cap)) ;
		s += nf ; h->reg->cap += nf ;
		f -= nf ; h->cap -= nf ; 
	}
	if (f) dep[x] = -1 ;

	return s ;
}

bool bfs() {
	que.push(S) ;
	ap[S] = ++ti ; dep[S] = 1 ;

	for (; !que.empty() ;) {
		int x = que.front() ; que.pop() ;

		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (!h->cap || ap[nx] == ti) continue ;

			que.push(nx) ;
			dep[nx] = dep[x] + 1 ; ap[nx] = ti ;
		}
	}

	return ap[T] == ti ;
}

void tarjan(int x) {
	sta.push(x) ;
	dfn[x] = low[x] = ++ti ; state[x] = 1 ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (!h->cap) {ful[h->idx] = 1 ; continue ;}

		if (!state[nx]) tarjan(nx) , low[x] = std::min(low[x] , low[nx]) ;
		else if (state[nx] == 1) low[x] = std::min(low[x] , dfn[nx]) ;
	}

	if (dfn[x] <= low[x]) {
		++tot ;
		for (; sta.top() != x ;) {
			int t = sta.top() ; sta.pop() ;
			id[t] = tot ; state[t] = 2 ;
		}

		id[x] = tot ; state[x] = 2 ; sta.pop() ;
	}
}

int main() {
	n = read() ; m = read() ; S = read() ; T = read() ;
	for (int i = 0 ; i < m ; ++i) {
		int x , y , v ;
		x = read() ; y = read() ; v = read() ;

		ins(x , y , v , i) ; eg[i] = (Edge){x , y} ;
	}

	for (; bfs() ; dfs(S , INF)) ;

	///

	ti = tot = 0 ;
	for (int i = 1 ; i <= n ; ++i)
		if (!state[i]) tarjan(i) ;
	for (int i = 0 ; i < m ; ++i) {
		Edge *p = &eg[i] ;
		if (!ful[i]) {printf("0 0\n") ; continue ;}

		int a1 , a2 ; a1 = a2 = 0 ;
		if (id[p->x] != id[p->y]) a1 = 1 ;
		if (id[p->x] == id[S] && id[p->y] == id[T]) a2 = 1 ;

		printf("%d %d\n" , a1 , a2) ;
	}

	return 0 ;
}