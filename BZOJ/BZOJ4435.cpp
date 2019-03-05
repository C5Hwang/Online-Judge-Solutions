#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 3e3 + 10 , MAX_M = 5e3 + 10 , INF = 0x3f3f3f3f ;

struct Link {
	int num , val ;
	Link *next ;
}list[MAX_N << 1] ;
struct Edge {
	int num , cap ;
	Edge *next , *reg ;
}eg[MAX_M << 1] ;

bool vis[MAX_N] ;
Link *head[MAX_N] ;
Edge *nhd[MAX_N] , *id[MAX_N] ;
int S , T , ti , L , R , ap[MAX_N] , flow[MAX_N] , pre[MAX_N] , que[MAX_N] ;
int n , m , tot , cur , ans , vert[MAX_N] , t1[MAX_N] , t2[MAX_N] , c[MAX_N][MAX_N] ;

///

bool bfs() {
	L = 0 ; R = 0 ; que[0] = S ;
	ap[S] = ++ti ; flow[S] = INF ;

	for (; L <= R ;) {
		int x = que[L++] ;

		for (Edge *h = nhd[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (!h->cap || ap[nx] == ti) continue ;

			que[++R] = nx ;
			pre[nx] = x ; id[nx] = h ; ap[nx] = ti ;
			flow[nx] = std::min(flow[x] , h->cap) ;
		}
	}

	return ap[T] == ti ;
}

inline int dinic() {
	int sum = 0 ;
	for (; bfs() ;) {
		int f = flow[T] ; sum += f ;

		for (int x = T ; x != S ; x = pre[x])
			id[x]->cap -= f , id[x]->reg->cap += f ;
	}

	return sum ;
}

///

void ins(int x , int y , int v) {
	eg[cur].num = y ;
	eg[cur].cap = v ;
	eg[cur].next = nhd[x] ;
	eg[cur].reg = &eg[cur^1] ;
	nhd[x] = &eg[cur++] ;

	eg[cur].num = x ;
	eg[cur].cap = v ;
	eg[cur].next = nhd[y] ;
	eg[cur].reg = &eg[cur^1] ;
	nhd[y] = &eg[cur++] ;
}

void add_edge(int x , int y , int v) {
	list[tot].num = y ;
	list[tot].val = v ;
	list[tot].next = head[x] ;
	head[x] = &list[tot++] ;
}

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

void find(int x) {
	vis[x] = 1 ;

	for (Edge *h = nhd[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (!h->cap || vis[nx]) continue ;

		find(nx) ;
	}
}

void init() {
	for (int x = 1 ; x <= n ; ++x) {
		for (Edge *h = nhd[x] ; h ; h = h->next) {
			int nx = h->num ;
			h->cap = c[x][nx] ;
		}
	}
}

void work(int x , int y) {
	if (x == y) return ;

	S = vert[x] ; T = vert[y] ;
	init() ; int v = dinic() ;
	add_edge(S , T , v) ; add_edge(T , S , v) ;

	///

	memset(vis , 0 , sizeof(vis)) ; find(S) ;

	int o1 = 0 , o2 = 0 ;
	for (int i = x ; i <= y ; ++i)
		if (vis[vert[i]]) t1[o1++] = vert[i] ;
		else t2[o2++] = vert[i] ;
	for (int i = 0 ; i < o1 ; ++i) vert[x + i] = t1[i] ;
	for (int i = 0 ; i < o2 ; ++i) vert[x + o1 + i] = t2[i] ;

	work(x , x + o1 - 1) ; work(x + o1 , y) ;
}

void getans(int x , int f , int p , int val) {
	if (p < x) ans += val ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == f) continue ;

		getans(nx , x , p , std::min(val , h->val)) ;
	}
}

///

int main() {
	n = read() ; m = read() ;
	for (int i = 0 ; i < m ; ++i) {
		int x , y ;
		x = read() ; y = read() ;
		++c[x][y] ; ++c[y][x] ;
	}

	for (int i = 1 ; i <= n ; ++i)
		for (int j = i ; j <= n ; ++j)
			if (c[i][j]) ins(i , j , c[i][j]) ;

	///

	for (int i = 1 ; i <= n ; ++i) vert[i] = i ;
	work(1 , n) ;

	ans = 0 ;
	for (int i = 1 ; i <= n ; ++i) getans(i , i , i , INF) ;
	printf("%d\n" , ans) ;

	return 0 ;
}