#include <queue>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 5e3 + 10 , MAX_E = 5e4 + 10 , INF = 0x3f3f3f3f ;

struct Link {
	int num , cap , cost ;
	Link *next , *reg ;
}list[2 * MAX_E] ;

std::queue<int> q ;

bool vis[MAX_N] ;
Link *head[MAX_N] , *id[MAX_N] ;
int n , m , S , T , cur , pre[MAX_N] , dis[MAX_N] , flow[MAX_N] ;

bool spfa() {
	for (int i = 1 ; i <= n ; ++i) dis[i] = INF , vis[i] = 0 ;
	vis[S] = 1 ; dis[S] = 0 ; flow[S] = INF ; q.push(S) ;

	while (!q.empty()) {
		int x = q.front() ; vis[x] = 0 ; q.pop() ;

		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (dis[nx] <= dis[x] + h->cost || !h->cap) continue ;

			flow[nx] = std::min(flow[x] , h->cap) ;
			dis[nx] = dis[x] + h->cost ;
			pre[nx] = x ; id[nx] = h ;

			if (!vis[nx]) {vis[nx] = 1 ; q.push(nx) ;}
		}
	}

	return dis[T] < INF ;
}

void MinCostMaxFlow(long long &c , long long &f) {
	while (spfa()) {
		f += (long long)flow[T] ; c += (long long)dis[T] * flow[T] ;

		int x = T ;
		for (; x != S ; x = pre[x]) {
			id[x]->cap -= flow[T] ;
			id[x]->reg->cap += flow[T] ;
		}
	}
}

///

void ins(int x , int y , int f , int c) {
	list[cur].num = y ;
	list[cur].cap = f ;
	list[cur].cost = c ;
	list[cur].reg = &list[cur + 1] ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;

	list[cur].num = x ;
	list[cur].cap = 0 ;
	list[cur].cost = -c ;
	list[cur].reg = &list[cur - 1] ;
	list[cur].next = head[y] ;
	head[y] = &list[cur++] ;
}

int main() {
	scanf("%d %d %d %d" , &n , &m , &S , &T) ;
	for (int i = 0 ; i < m ; ++i) {
		int x , y , w , f ;
		scanf("%d %d %d %d" , &x , &y , &w , &f) ;
		ins(x , y , w , f) ;
	}

	///
	
	long long ac = 0 , af = 0 ;
	MinCostMaxFlow(ac , af) ;

	printf("%lld %lld\n" , af , ac) ;

	return 0 ;
}
