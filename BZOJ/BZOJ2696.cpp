#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 200 + 10 , MAX_P = 400 + 10 , MAX_M = 5e4 + 10 , INF = 0x3f3f3f3f ;

struct Link {
	int num , cap , val ;
	Link *next , *reg ;
}list[MAX_M << 1] ;

std::queue<int> que ;

bool vis[MAX_P] ;
Link *head[MAX_P] , *id[MAX_P] ;
int T , ti , tot , bh[MAX_N][2] , flow[MAX_P] , dis[MAX_P] , pre[MAX_P] ;
int n , m , k , maxt , cur , t[MAX_N][MAX_N] , f[MAX_N][MAX_N] , a[MAX_N] , b[MAX_N] , st[MAX_N] , ed[MAX_N] ;

void ins(int x , int y , int v , int c) {
	list[cur].num = y ;
	list[cur].cap = v ;
	list[cur].val = c ;
	list[cur].next = head[x] ;
	list[cur].reg = &list[cur^1] ;
	head[x] = &list[cur++] ;

	list[cur].num = x ;
	list[cur].cap = 0 ;
	list[cur].val = -c ;
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

			flow[nx] = std::min(flow[x] , h->cap) ;
			pre[nx] = x ; id[nx] = h ; dis[nx] = dis[x] + h->val ;

			if (!vis[nx]) que.push(nx) , vis[nx] = 1 ;
		}
	}

	return dis[T] < INF ;
}

int work() {
	int s = 0 ;
	for (; spfa() ;) {
		s += flow[T] * dis[T] ;
		for (int i = T ; i ; i = pre[i])
			id[i]->cap -= flow[T] , id[i]->reg->cap += flow[T] ;
	}

	return s ;
}

int main() {
	scanf("%d %d %d %d" , &n , &m , &k , &maxt) ;
	for (int i = 0 ; i < n ; ++i)
		for (int j = 0 ; j < n ; ++j) scanf("%d" , &t[i][j]) ;
	for (int i = 0 ; i < n ; ++i)
		for (int j = 0 ; j < n ; ++j) scanf("%d" , &f[i][j]) ;

	///

	tot = 1 ;

	for (int i = 0 ; i < m ; ++i) {
		int c ;
		scanf("%d %d %d %d %d" , &a[i] , &b[i] , &st[i] , &ed[i] , &c) ;

		bh[i][0] = ++tot ; bh[i][1] = ++tot ; ins(bh[i][0] , bh[i][1] , 1 , -c) ;
	}

	T = ++tot ;
	ins(0 , 1 , k , 0) ; ins(1 , T , INF , 0) ;

	for (int i = 0 ; i < m ; ++i) {
		if (t[0][a[i]] <= st[i]) ins(1 , bh[i][0] , INF , f[0][a[i]]) ;
		if (ed[i] + t[b[i]][0] <= maxt) ins(bh[i][1] , T , INF , f[b[i]][0]) ;
	}
	for (int i = 0 ; i < m ; ++i)
		for (int j = 0 ; j < m ; ++j) {
			if (i == j || ed[i] + t[b[i]][a[j]] > st[j]) continue ;

			ins(bh[i][1] , bh[j][0] , INF , f[b[i]][a[j]]) ;
		}

	///

	printf("%d\n" , -work()) ;

	return 0 ;
}