#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 100 + 10 , MAX_M = 400 + 10 , MAX_E = 5e4 + 10 , INF = 0x3f3f3f3f ;

struct Link {
	int num , cap ;
	Link *next , *reg ;
}list[MAX_E] ;

std::queue<int> que ;

Link *head[MAX_M] ;
int ti , ap[MAX_M] , dep[MAX_M] ;
int n , f , d , S , T , tot , cur , fo[MAX_N] , co[2][MAX_N] , dr[MAX_N] ;

bool bfs() {
	que.push(S) ;
	dep[S] = 1 ; ap[S] = ++ti ;

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

int dfs(int x , int f) {
	if (x == T) return f ;

	int flow = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (!h->cap || dep[nx] != dep[x] + 1) continue ;

		int tf = dfs(nx , std::min(f , h->cap)) ;
		h->cap -= tf ; f -= tf ;
		h->reg->cap += tf ; flow += tf ;
	}
	if (f) dep[x] = -1 ;

	return flow ;
}

int dinic() {
	int sum = 0 ;
	for (; bfs() ; sum += dfs(S , INF)) ;

	return sum ;
}

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

int main() {
	scanf("%d %d %d" , &n , &f , &d) ;
	for (int i = 1 ; i <= f ; ++i) fo[i] = ++tot ;
	for (int i = 1 ; i <= n ; ++i) co[0][i] = ++tot ;
	for (int i = 1 ; i <= n ; ++i) co[1][i] = ++tot ;
	for (int i = 1 ; i <= d ; ++i) dr[i] = ++tot ;

	S = 0 ; T = ++tot ;
	for (int i = 1 ; i <= f ; ++i) ins(S , fo[i] , 1) ;
	for (int i = 1 ; i <= n ; ++i) ins(co[0][i] , co[1][i] , 1) ;
	for (int i = 1 ; i <= d ; ++i) ins(dr[i] , T , 1) ;

	for (int i = 1 ; i <= n ; ++i) {
		int x , y ; scanf("%d %d" , &x , &y) ;
		for (int j = 0 ; j < x ; ++j) {
			int a ; scanf("%d" , &a) ;
			ins(fo[a] , co[0][i] , 1) ;
		}
		for (int j = 0 ; j < y ; ++j) {
			int a ; scanf("%d" , &a) ;
			ins(co[1][i] , dr[a] , 1) ;
		}
	}

	///

	printf("%d\n" , dinic()) ;

	return 0 ;
}