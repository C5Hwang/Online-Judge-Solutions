#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 100 + 10 , MAX_E = 3e4 + 10 , INF = 0x3f3f3f3f ;

struct Link {
	int num , cap ;
	Link *next , *reg ;
}list[MAX_E] ;

std::queue<int> que ;

bool u[MAX_N][MAX_N] ;
Link *head[MAX_N << 1] ;
int ti , ap[MAX_N << 1] , dep[MAX_N << 1] ;
int n , m , k , cur , S , T , l[MAX_N] , c[MAX_N] ;

bool bfs() {
	que.push(S) ;
	dep[S] = 1 ; ap[S] = ++ti ;

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
	if (x == T) return flow ;

	int sum = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (dep[nx] != dep[x] + 1 || !h->cap) continue ;

		int tf = dfs(nx , std::min(flow , h->cap)) ;
		flow -= tf ; h->cap -= tf ;
		sum += tf ; h->reg->cap += tf ;
	}
	if (flow) dep[x] = -1 ;

	return sum ;
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
	scanf("%d %d %d" , &n , &m , &k) ;
	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= m ; ++j) {
			u[i][j] = 1 ; ++l[i] ; ++c[j] ;
		}
	for (int i = 1 ; i <= n ; ++i) {
		int a ; scanf("%d" , &a) ;
		l[i] -= a ;
	}
	for (int i = 1 ; i <= m ; ++i) {
		int a ; scanf("%d" , &a) ;
		c[i] -= a ;
	}

	for (int i = 0 ; i < k ; ++i) {
		int x , y ; scanf("%d %d" , &x , &y) ;
		u[x][y] = 0 ; --l[x] ; --c[y] ;
	}

	///

	bool ok = 1 ;
	for (int i = 1 ; i <= n && ok ; ++i) if (l[i] < 0) ok = 0 ;
	for (int i = 1 ; i <= m && ok ; ++i) if (c[i] < 0) ok = 0 ;

	if (!ok) {printf("JIONG!\n") ; return 0 ;}

	S = 0 ; T = n + m + 1 ;
	for (int i = 1 ; i <= n ; ++i) ins(S , i , l[i]) ;
	for (int i = 1 ; i <= m ; ++i) ins(i + n , T , c[i]) ;

	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= m ; ++j)
			if (u[i][j]) ins(i , j + n , 1) ;

	printf("%d\n" , n * m - k - dinic()) ;

	return 0 ;
}