#include <stack>
#include <stdio.h>
#include <stdlib.h>

const int MAX_N = 1e4 + 10 , MAX_M = 5e4 + 10 ;

struct Edge {
	int x , y ;
}eg[MAX_M] ;
struct Link {
	int num ;
	Link *next ;
}list[MAX_M] ;

std::stack<int> sta ;

bool out[MAX_N] ;
Link *head[MAX_N] ;
int n , m , cur , tot , ti ;
int pt[MAX_N] , sum[MAX_N] , low[MAX_N] , dfn[MAX_N] , state[MAX_N] ;

void tarjan(int x) {
	sta.push(x) ;
	state[x] = 1 ; low[x] = dfn[x] = ++ti ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (state[nx] == 2) continue ;
		if (!state[nx]) tarjan(nx) ;
		low[x] = std::min(low[x] , low[nx]) ;
	}

	if (low[x] == dfn[x]) {
		int s = 1 ; ++tot ;
		while (sta.top() != x) {
			int nx = sta.top() ; sta.pop() ;
			pt[nx] = tot ; state[nx] = 2 ; ++s ;
		}
		state[x] = 2 ; pt[x] = tot ; sta.pop() ;
		sum[tot] = s ;
	}
}

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 0 ; i < m ; ++i) {
		int x , y ; scanf("%d %d" , &x , &y) ;
		ins(x , y) ;
		eg[i] = (Edge){x , y} ;
	}

	///

	for (int i = 1 ; i <= n ; ++i)
		if (!state[i]) tarjan(i) ;

	///

	for (int i = 0 ; i < m ; ++i) {
		Edge *p = &eg[i] ;
		if (pt[p->x] != pt[p->y]) out[pt[p->x]] = 1 ;
	}

	int s = 0 , p = -1 ;
	for (int i = 1 ; i <= tot ; ++i)
		if (!out[i]) ++s , p = i ;

	if (s > 1) printf("0\n") ;
	else printf("%d\n" , sum[p]) ;

	return 0 ;
}
