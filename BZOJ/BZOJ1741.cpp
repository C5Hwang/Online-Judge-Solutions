#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 500 + 10 , MAX_P = 1e3 + 10 , MAX_M = 1e4 + 10 , INF = 0x3f3f3f3f ;

struct Link {
	int num , cap ;
	Link *next , *reg ;
}list[(MAX_N + MAX_M) << 1] ;

std::queue<int> que ;

Link *head[MAX_P] ;
int n , m , r[MAX_N] , l[MAX_N] ;
int tot , cur , T , ti , ap[MAX_P] , dep[MAX_P] ;

void ins(int x , int y , int f) {
	list[cur].num = y ;
	list[cur].cap = f ;
	list[cur].next = head[x] ;
	list[cur].reg = &list[cur^1] ;
	head[x] = &list[cur++] ;

	list[cur].num = x ;
	list[cur].cap = 0 ;
	list[cur].next = head[y] ;
	list[cur].reg = &list[cur^1] ;
	head[y] = &list[cur++] ;
}

int dfs(int x , int f) {
	if (x == T || !f) return f ;

	int s = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (dep[nx] != dep[x] + 1) continue ;

		int nf = dfs(nx , std::min(f , h->cap)) ;
		s += nf ; h->reg->cap += nf ;
		h->cap -= nf ; f -= nf ;
	}
	if (f) dep[x] = -1 ;

	return s ;
}

bool bfs() {
	que.push(0) ;
	ap[0] = ++ti ; dep[0] = 1 ;

	for (; !que.empty() ;) {
		int x = que.front() ; que.pop() ;

		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (!h->cap || ap[nx] == ti) continue ;

			dep[nx] = dep[x] + 1 ; ap[nx] = ti ;
			que.push(nx) ;
		}
	}

	return ap[T] == ti ;
}

int dinic() {
	int s = 0 ;
	for (; bfs() ; s += dfs(0 , INF)) ;

	return s ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 1 ; i <= n ; ++i) r[i] = ++tot ;
	for (int i = 1 ; i <= n ; ++i) l[i] = ++tot ;

	T = ++tot ;
	for (int i = 1 ; i <= n ; ++i) ins(0 , r[i] , 1) , ins(l[i] , T , 1) ;

	for (; m-- ;) {
		int x , y ;
		scanf("%d %d" , &x , &y) ;
		ins(r[x] , l[y] , INF) ;
	}

	///

	printf("%d\n" , dinic()) ;

	return 0 ;
}