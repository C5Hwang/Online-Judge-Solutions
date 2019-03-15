#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e3 + 10 , MAX_M = 12e3 + 10 , INF = 0x3f3f3f3f ;

struct Link {
	int num , cap , val ;
	Link *next , *reg ;
}list[MAX_M << 1] ;

std::queue<int> que ;

bool vis[MAX_N] ;
int n , m , cur , a[MAX_N] ;
Link *head[MAX_N] , *id[MAX_N] ;
int T , dis[MAX_N] , flow[MAX_N] , pre[MAX_N] ;

bool bfs() {
	for (int i = 0 ; i <= T ; ++i) dis[i] = INF ;

	que.push(0) ;
	dis[0] = 0 ; vis[0] = 1 ; flow[0] = INF ;

	for (; !que.empty() ;) {
		int x = que.front() ;
		vis[x] = 0 ; que.pop() ;

		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (!h->cap || dis[nx] <= dis[x] + h->val) continue ;

			dis[nx] = dis[x] + h->val ;
			flow[nx] = std::min(flow[x] , h->cap) ; pre[nx] = x ; id[nx] = h ;

			if (!vis[nx]) que.push(nx) , vis[nx] = 1 ;
		}
	}

	return dis[T] < INF ;
}

inline int work() {
	int sum = 0 ;
	for (; bfs() ;) {
		sum += flow[T] * dis[T] ;

		for (int x = T ; x ; x = pre[x])
			id[x]->cap -= flow[T] , id[x]->reg->cap += flow[T] ;
	}

	return sum ;
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
	for (int i = 1 ; i <= n ; ++i) scanf("%d" , &a[i]) ;

	T = n + 2 ;
	for (int i = 1 ; i <= n + 1 ; ++i) {
		int v = a[i - 1] - a[i] ;

		if (i > 1) ins(i - 1 , i , INF , 0) ;
		if (v > 0) ins(0 , i , v , 0) ;
		else ins(i , T , -v , 0) ;
	}

	for (; m-- ;) {
		int x , y , c ;
		scanf("%d %d %d" , &x , &y , &c) ;

		ins(y + 1 , x , INF , c) ;
	}

	printf("%d\n" , work()) ;

	return 0 ;
}