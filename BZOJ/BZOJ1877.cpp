#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 200 + 10 , MAX_P = 400 + 10 , MAX_M = 21e3 + 10 , INF = 0x3f3f3f3f ;

struct Link {
	int num , cap , val ;
	Link *next , *reg ;
}list[MAX_M << 1] ;

std::queue<int> que ;

bool vis[MAX_P] ;
Link *head[MAX_P] , *id[MAX_P] ;
int n , m , T , cur , tot , bh[MAX_N][2] ;
int dis[MAX_P] , pre[MAX_P] , flow[MAX_P] ;

bool spfa() {
	for (int i = 1 ; i <= tot ; ++i) dis[i] = INF ;

	que.push(1) ;
	dis[1] = 0 ; vis[1] = 1 ; flow[1] = INF ;

	for (; !que.empty() ;) {
		int x = que.front() ;
		que.pop() ; vis[x] = 0 ;

		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (dis[nx] <= dis[x] + h->val || !h->cap) continue ;

			dis[nx] = dis[x] + h->val ;
			id[nx] = h ; pre[nx] = x ; flow[nx] = std::min(flow[x] , h->cap) ;

			if (!vis[nx]) vis[nx] = 1 , que.push(nx) ;
		}
	}

	return dis[T] < INF ;
}

void work() {
	int ms = 0 , mf = 0 ;
	for (; spfa() ;) {
		ms += flow[T] * dis[T] ; mf += flow[T] ;

		for (int x = T ; x > 1 ; x = pre[x])
			id[x]->cap -= flow[T] , id[x]->reg->cap += flow[T] ;
	}

	printf("%d %d\n" , mf , ms) ;
}

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

int main() {
	scanf("%d %d" , &n , &m) ;

	bh[1][0] = bh[1][1] = ++tot ;
	for (int i = 2 ; i < n ; ++i) {
		bh[i][0] = ++tot ; bh[i][1] = ++tot ;

		ins(bh[i][0] , bh[i][1] , 1 , 0) ;
	}
	T = bh[n][0] = bh[n][1] = ++tot ;

	for (int i = 0 ; i < m ; ++i) {
		int x , y , v ;
		scanf("%d %d %d" , &x , &y , &v) ;

		if (x != 1 || y != n) ins(bh[x][1] , bh[y][0] , INF , v) ;
		else ins(bh[x][1] , bh[y][0] , 1 , v) ;
	}

	work() ;

	return 0 ; 
}