#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const ll MAX_DIS = 1e15 ;
const int MAX_N = 1e3 + 10 , MAX_M = 4e3 + 10 , INF = 0x3f3f3f3f ;

struct Link {
	int num , cap , val , idx ;
	Link *next , *reg ;
}list[MAX_M << 1] ;

std::queue<int> que ;

ll dis[MAX_N] ;
bool vis[MAX_N] ;
Link *head[MAX_N] , *id[MAX_N] ;
int T , cur , pre[MAX_N] , flow[MAX_N] ;
int n , k , t1 , t2 , tot , s[MAX_N] , e[MAX_N] ;

bool bfs() {
	for (int i = 0 ; i <= T ; ++i) dis[i] = MAX_DIS ;

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

			if (!vis[nx]) vis[nx] = 1 , que.push(nx) ;
		}
	}

	return dis[T] < MAX_DIS ;
}

inline ll work() {
	ll sum = 0 ;
	for (; bfs() ;) {
		sum += flow[T] * dis[T] ;

		for (int x = T ; x ; x = pre[x])
			id[x]->cap -= flow[T] , id[x]->reg->cap += flow[T] ;
	}

	return sum ;
}

void ins(int x , int y , int f , int v , int p) {
	if (!f) return ;

	list[cur].num = y ;
	list[cur].cap = f ;
	list[cur].val = v ;
	list[cur].idx = p ;
	list[cur].next = head[x] ;
	list[cur].reg = &list[cur^1] ;
	head[x] = &list[cur++] ;

	list[cur].num = x ;
	list[cur].cap = 0 ;
	list[cur].val = -v ;
	list[cur].idx = p ;
	list[cur].next = head[y] ;
	list[cur].reg = &list[cur^1] ;
	head[y] = &list[cur++] ;
}

int main() {
	scanf("%d %d %d %d" , &n , &k , &t1 , &t2) ;
	for (int i = 1 ; i <= n ; ++i) scanf("%d" , &s[i]) ;
	for (int i = 1 ; i <= n ; ++i) scanf("%d" , &e[i]) ;

	for (int i = 1 ; i <= n ; ++i) if (i + k - 1 <= n) ++tot ;
	T = tot + 2 ;

	///

	ll sum = 0 ;
	ins(0 , tot + 1 , t1 , 0 , 0) ; ins(1 , T , t1 , 0 , 0) ;

	for (int i = 1 ; i <= tot ; ++i) {
		int v = k - t1 - t2 ;
		ins(i , i + 1 , v , 0 , 0) ;
	}
	for (int i = 1 ; i <= n ; ++i) {
		int L = std::max(1 , i - k + 1) , R = std::min(tot , i) ;

		sum += e[i] ;
		if (e[i] - s[i] >= 0) ins(R + 1 , L , 1 , e[i] - s[i] , i) ;
		else {
			ins(0 , L , 1 , 0 , 0) ; ins(R + 1 , T , 1 , 0 , 0) ;
			ins(L , R + 1 , 1 , s[i] - e[i] , i) ; sum -= (e[i] - s[i]) ;
		}
	}

	///

	printf("%lld\n" , sum - work()) ;
	for (int i = 1 ; i <= n ; ++i) {
		int p = std::min(tot , i) + 1 ;

		for (Link *h = head[p] ; h ; h = h->next)
			if (h->idx == i) {
				if (h->cap) printf("E") ;
				else printf("S") ;

				break ;
			}
	}
	printf("\n") ;

	return 0 ;
}