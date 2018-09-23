#include <queue>
#include <stdio.h>
#include <stdlib.h>

const int MAX_N = 1e4 + 10 , MAX_M = 2e5 + 10 , INF = 0x3f3f3f3f ;

struct Link {
	int num , cap ;
	Link *next , *reg ;
}list[MAX_M] ;

std::queue<int> que ;

Link *head[MAX_N] ;
int n , m , ti , cur , S , T , dep[MAX_N] , ap[MAX_N] ;

bool bfs() {
	que.push(S) ; ap[S] = ++ti ; dep[S] = 1 ;

	for (; !que.empty() ;) {
		int x = que.front() ; que.pop() ;

		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (ap[nx] == ti || !h->cap) continue ;

			ap[nx] = ti ; dep[nx] = dep[x] + 1 ; que.push(nx) ;
		}
	}

	return ap[T] == ti ;
}

int dfs(int x , int flow) {
	if (x == T) return flow ;

	int sum = 0 ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (dep[x] + 1 != dep[nx] || !h->cap) continue ;

		int nf = dfs(nx , std::min(flow , h->cap)) ;
		flow -= nf ; sum += nf ;
		h->cap -= nf ; h->reg->cap += nf ;
	}
	if (flow) dep[x] = -1 ;

	return sum ;
}

int dinic() {
	int sum = 0 ;
	for (; bfs() ; sum += dfs(S , INF)) ;

	return sum ;
}

void ins(int x , int y , int f) {
	list[cur].num = y ;
	list[cur].cap = f ;
	list[cur].next = head[x] ;
	list[cur].reg = &list[cur^1] ;
	head[x] = &list[cur++] ;
}

int main() {
	scanf("%d %d %d %d" , &n , &m , &S , &T) ;
	for (int i = 0 ; i < m ; ++i) {
		int x , y , f ;
		scanf("%d %d %d" , &x , &y , &f) ;
		ins(x , y , f) ; ins(y , x , 0) ;
	}

	///

	int ans = dinic() ;

	printf("%d\n" , ans) ;

	return 0 ;
}