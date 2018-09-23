#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_V = 3e5 + 10 , MAX_E = 2e6 + 10 , INF = 0x3f3f3f3f ;

struct Link {
	int num , cap ;
	Link *next , *reg ;
}list[MAX_E] ;

std::queue<int> que ;

Link *head[MAX_V] ;
int n , S , T , cur , ti , ap[MAX_V] , dep[MAX_V] ;

void ins(int x , int y , int v) {
	list[cur].num = y ;
	list[cur].cap = v ;
	list[cur].next = head[x] ;
	list[cur].reg = &list[cur^1] ;
	head[x] = &list[cur++] ;

	list[cur].num = x ;
	list[cur].cap = 0 ;
	list[cur].next = head[y] ;
	list[cur].reg = &list[cur^1] ;
	head[y] = &list[cur++] ;
}

bool bfs() {
	que.push(S) ;
	ap[S] = ++ti ; dep[S] = 1 ;

	for (; !que.empty() ;) {
		int x = que.front() ; que.pop() ;
		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (!h->cap || ap[nx] == ti) continue ;

			ap[nx] = ti ; dep[nx] = dep[x] + 1 ;
			que.push(nx) ;
		}
	}

	return ap[T] == ti ;
}

int dfs(int x , int flow) {
	if (x == T || !flow) return flow ;

	int sum = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (dep[nx] != dep[x] + 1) continue ;

		int nf = dfs(nx , std::min(flow , h->cap)) ;
		flow -= nf ; h->cap -= nf ;
		sum += nf ; h->reg->cap += nf ;
	}
	if (flow) dep[x] = -1 ;

	return sum ;
}

int dinic() {
	int sum = 0 ;
	for (; bfs() ; sum += dfs(S , INF)) ;

	return sum ;
}

int main() {
	scanf("%d" , &n) ;
	S = 0 ; T = n * (n + 1) + 1 ;

	///

	int p = n , ans = 0 ;
	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= n ; ++j) {
			++p ;
			int v ; scanf("%d" , &v) ; ans += v ;

			ins(S , p , v) ;
			ins(p , i , INF) ; if (i != j) ins(p , j , INF) ;
		}

	for (int i = 1 ; i <= n ; ++i) {
		int x ; scanf("%d" , &x) ;
		ins(i , T , x) ;
	}

	///

	ans -= dinic() ;
	printf("%d\n" , ans) ;

	return 0 ;
}