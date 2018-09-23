#include <queue>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 20000 + 10 , MAX_E = 200000 + 10 , INF = 0x7FFFFFFF ;

struct Link {
	int num , f ;
	Link *next , *reg ;
}list[4 * MAX_E + 4 * MAX_N] ;

std::queue<int> q ;

Link *head[MAX_N] ;
int n , m , S , T , cur , time , bft[MAX_N] , dep[MAX_N] ;

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
	if (!flow || x == T) return flow ;

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

///

void ins(int x , int y , int v) {
	list[cur].f = v ;
	list[cur].num = y ;
	list[cur].next = head[x] ;
	list[cur].reg = &list[cur + 1] ;
	head[x] = &list[cur++] ;

	list[cur].f = 0 ;
	list[cur].num = x ;
	list[cur].next = head[y] ;
	list[cur].reg = &list[cur - 1] ;
	head[y] = &list[cur++] ;
}

void init() {
	cur = 0 ;
	memset(head , 0 , sizeof(head)) ;
}

int main() {
	while (scanf("%d %d" , &n , &m) != EOF) {
		init() ;

		S = 0 ; T = n + 1 ;
		for (int i = 1 ; i <= n ; ++i) {
			int c1 , c2 ;

			scanf("%d %d" , &c1 , &c2) ;
			ins(S , i , c1) ; ins(i , T , c2) ;
		}

		///
		
		for (int i = 0 ; i < m ; ++i) {
			int a , b , c ;
			scanf("%d %d %d" , &a , &b , &c) ;

			ins(a , b , c) ; ins(b , a , c) ;
		}

		///

		int res = dinic() ;

		printf("%d\n" , res) ;
	}

	return 0 ;
}
