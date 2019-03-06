#include <queue>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 500 + 10 , MAX_M = 5e3 + 10 , INF = 0x3f3f3f3f ;

struct Edge {int x , y ;}eg[MAX_M] ;
struct Link {
	int num , cap ;
	Link *next , *reg ;
}list[MAX_M << 1] ;

std::queue<int> que ;

ll ans1 , ans2 ;
bool vis[MAX_N] ;
Link *head[MAX_N] ;
int n , m , T , cur , a[MAX_N] ;
int ti , ap[MAX_N] , dep[MAX_N] ;

int dfs(int x , int f) {
	if (x == T || !f) return f ;

	int sum = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (dep[nx] != dep[x] + 1) continue ;

		int nf = dfs(nx , std::min(f , h->cap)) ;
		sum += nf ; h->reg->cap += nf ;
		f -= nf ; h->cap -= nf ;
	}
	if (f) dep[x] = -1 ;

	return sum ;
}

bool bfs() {
	que.push(0) ;
	dep[0] = 1 ; ap[0] = ++ti ;

	for (; !que.empty() ;) {
		int x = que.front() ; que.pop() ;

		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (!h->cap || ap[nx] == ti) continue ;

			que.push(nx) ;
			dep[nx] = dep[x] + 1 ; ap[nx] = ti ;
		}
	}

	return ap[T] == ti ;
}

inline int dinic() {
	int sum = 0 ;
	for (; bfs() ; sum += dfs(0 , INF)) ;

	return sum ;
}

int find(int x) {
	int sum = 1 ; vis[x] = 1 ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (!h->reg->cap || vis[nx]) continue ;

		sum += find(nx) ;
	}

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

void build(int x) {
	cur = 0 ;
	memset(head , 0 , sizeof(head)) ;

	for (int i = 1 ; i <= n ; ++i)
		if (a[i] >= 0) {
			if (a[i] & x) ins(i , T , INF) ;
			else ins(0 , i , INF) ;
		}
	for (int i = 0 ; i < m ; ++i) {
		Edge *p = &eg[i] ;
		ins(p->x , p->y , 1) ; ins(p->y , p->x , 1) ;
	}
}

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

int main() {
	n = read() ; m = read() ; T = n + 1 ;
	for (int i = 1 ; i <= n ; ++i) a[i] = read() ;
	for (int i = 0 ; i < m ; ++i) eg[i].x = read() , eg[i].y = read() ;

	///

	ans1 = ans2 = 0 ;
	for (int i = 0 ; i <= 30 ; ++i) {
		int a = 1 << i ;
		build(a) ;

		memset(vis , 0 , sizeof(vis)) ;
		ans1 += (ll)a * dinic() ;
		ans2 += (ll)a * (find(T) - 1) ;
	}

	printf("%lld\n%lld\n" , ans1 , ans2) ;

	return 0 ;
}