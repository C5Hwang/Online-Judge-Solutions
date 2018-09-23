#include <queue>
#include <stdio.h>
#include <stdlib.h>

const int MAX_N = 300 + 10 , MAX_M = 45000 + 10 , INF = 0x3f3f3f3f ;

std::queue<int> q ;

struct Link {
	int num , f ;
	Link *next , *reg ;
}list[4 * MAX_M + 2 * MAX_N] ;

Link *head[MAX_N] ;
int n , m , cur , S , T , time , bft[MAX_N] , dep[MAX_N] ;

///

void ins(int x , int y) {
	list[cur].f = 1 ;
	list[cur].num = y ;
	list[cur].next = head[x] ;
	list[cur].reg = &list[cur + 1] ;
	head[x] = &list[cur++] ;

	list[cur].f = 0 ;
	list[cur].num = x ;
	list[cur].next = head[y] ;
	list[cur].reg = &list[cur + 1] ;
	head[y] = &list[cur++] ;
}

///

bool bfs() {
	q.push(S) ;
	bft[S] = ++time ; dep[S] = 1 ;

	while (!q.empty()) {
		int x = q.front() ; q.pop() ;
		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (!h->f || bft[nx] == time) continue ;

			q.push(nx) ;
			bft[nx] = time ; dep[nx] = dep[x] + 1 ;
		}
	}

	return bft[T] == time ;
}

int dfs(int x , int flow) {
	if (x == T || !flow) return flow ;

	int sum = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;

		if (dep[nx] != dep[x] + 1) continue ;

		int nf = dfs(nx , std::min(flow , h->f)) ;
		sum += nf ; flow -= nf ;
		h->f -= nf ; h->reg->f += nf ;
	}
	if (flow) dep[x] = -1 ;

	return sum ;
}

int dinic() {
	int sum = 0 ;
	while (bfs())
		sum += dfs(S , INF) ;

	return sum ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	S = 0 ; T = n + 1 ;
	for (int i = 1 ; i <= n ; ++i) {
		int a ; scanf("%d" , &a) ;
		if (a) ins(S , i) ;
		else ins(i , T) ;
	}

	///
	
	for (int i = 0 ; i < m ; ++i) {
		int x , y ; scanf("%d %d" , &x , &y) ;
		ins(x , y) ; ins(y , x) ;
	}

	///
	
	int res = dinic() ;

	printf("%d\n" , res) ;

	return 0 ;
}
