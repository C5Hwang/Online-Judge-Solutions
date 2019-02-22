#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 100 + 10 , MAX_M = 800 + 10 , MAX_P = 8e4 + 50 , MAX_E = 1e5 + 10 , INF = 0x3f3f3f3f ;

struct Link {
	int num , val , cap ;
	Link *next , *reg ;
}list[MAX_E << 1] ;

std::queue<int> que ;

bool vis[MAX_P] ;
Link *head[MAX_P] , *id[MAX_P] ;
int cur , T , pre[MAX_P] , dis[MAX_P] , flow[MAX_P] ;
int n , m , tot , P , ti[MAX_N][MAX_N] , bh[MAX_N][MAX_M] , wk[MAX_P] , wt[MAX_N] ;

void ins(int x , int y , int f , int v) {
	list[cur].num = y ;
	list[cur].cap = f ;
	list[cur].val = v ;
	list[cur].next = head[x] ;
	list[cur].reg = &list[cur^1] ;
	head[x] = &list[cur++] ;

	list[cur].num = x ;
	list[cur].cap = 0 ;
	list[cur].val = -v ;
	list[cur].next = head[y] ;
	list[cur].reg = &list[cur^1] ;
	head[y] = &list[cur++] ;
}

bool spfa() {
	for (int i = 0 ; i <= tot ; ++i) dis[i] = INF ;

	que.push(0) ;
	dis[0] = 0 ; flow[0] = INF ; vis[0] = 1 ;

	for (; !que.empty() ;) {
		int x = que.front() ;
		que.pop() ; vis[x] = 0 ;

		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (!h->cap || dis[nx] <= dis[x] + h->val) continue ;

			dis[nx] = dis[x] + h->val ;
			pre[nx] = x ; id[nx] = h ; flow[nx] = std::min(flow[x] , h->cap) ;

			if (!vis[nx]) vis[nx] = 1 , que.push(nx) ;
		}
	}

	return dis[T] < INF ;
}

int work() {
	int s = 0 ;
	for (; spfa() ;) {
		s += flow[T] * dis[T] ;

		int x = wk[pre[T]] , k = ++wt[x] ;
		for (int i = T ; i ; i = pre[i])
			id[i]->cap -= flow[T] , id[i]->reg->cap += flow[T] ;

		if (k <= P) {
			for (int i = 1 ; i <= n ; ++i) ins(i , bh[x][k] , 1 , k * ti[x][i]) ;
			ins(bh[x][k] , T , 1 , 0) ;
		}
	}

	return s ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 1 ; i <= n ; ++i) {
		int t ; scanf("%d" , &t) ;
		ins(0 , i , t , 0) ; P += t ;
	}

	tot = n ;
	for (int j = 1 ; j <= n ; ++j)
		for (int i = 1 ; i <= m ; ++i) scanf("%d" , &ti[i][j]) ;

	for (int i = 1 ; i <= m ; ++i) {
		wt[i] = 1 ;
		for (int j = 1 ; j <= P ; ++j) bh[i][j] = ++tot , wk[tot] = i ;
	}

	///

	T = ++tot ;
	for (int i = 1 ; i <= m ; ++i) ins(bh[i][1] , T , 1 , 0) ;

	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= m ; ++j) ins(i , bh[j][1] , 1 , ti[j][i]) ;

	printf("%d\n" , work()) ;

	return 0 ;
}