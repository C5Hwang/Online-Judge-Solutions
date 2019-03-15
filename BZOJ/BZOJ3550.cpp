#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 600 + 10 , MAX_M = 1200 + 10 , INF = 0x3f3f3f3f ;

struct Link {
	int num , cap , val ;
	Link *next , *reg ;
}list[MAX_M << 1] ;

std::queue<int> que ;

bool vis[MAX_N] ;
Link *head[MAX_N] , *id[MAX_N] ;
int n , m , k , tot , cur , a[MAX_N] ;
int T , dis[MAX_N] , flow[MAX_N] , pre[MAX_N] ;

bool bfs() {
	for (int i = 0 ; i <= T ; ++i) dis[i] = -INF ;

	que.push(0) ;
	dis[0] = 0 ; flow[0] = INF ; vis[0] = 1 ;

	for (; !que.empty() ;) {
		int x = que.front() ;
		vis[x] = 0 ; que.pop() ;

		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (!h->cap || dis[nx] >= dis[x] + h->val) continue ;

			dis[nx] = dis[x] + h->val ;
			flow[nx] = std::min(flow[x] , h->cap) ; pre[nx] = x ; id[nx] = h ;

			if (!vis[nx]) vis[nx] = 1 , que.push(nx) ;
		}
	}

	return dis[T] > -INF ;
}

inline int work() {
	int sum = 0 ;
	for (; bfs() ;) {
		sum += dis[T] * flow[T] ;

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
	scanf("%d %d" , &n , &k) ; m = n * 3 ;
	for (int i = 1 ; i <= m ; ++i) scanf("%d" , &a[i]) ;
	for (int i = 1 ; i <= m ; ++i) if (i + n - 1 <= m) ++tot ;
	T = tot + 2 ;

	///

	ins(1 , T , k , 0) ; ins(0 , tot + 1 , k , 0) ;
	for (int i = 1 ; i <= tot ; ++i) ins(i + 1 , i , INF , 0) ;
	for (int i = 1 ; i <= m ; ++i) {
		int L = std::max(1 , i - n + 1) , R = std::min(tot , i) ;
		ins(R + 1 , L , 1 , a[i]) ;
	}

	printf("%d\n" , work()) ;

	return 0 ;
}