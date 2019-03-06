#include <queue>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 500 + 10 , MAX_M = 5e3 + 10 , offset = 1e3 , INF = 0x3f3f3f3f ;

struct Edge {int x , y ;} eg[MAX_M] ;
struct Link {
	int num , cap ;
	Link *next , *reg ;
}list[MAX_M << 1] ;

std::queue<int> que ;

Link *head[MAX_N] ;
int n , m , cur , a[MAX_N] ;
int T , ti , dep[MAX_N] , ap[MAX_N] ;

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
			if (ap[nx] == ti || !h->cap) continue ;

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

void ins(int x , int y , int v) {
	list[cur].num = y ;
	list[cur].cap = v ;
	list[cur].reg = &list[cur^1] ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;

	list[cur].num = x ;
	list[cur].cap = 0 ;
	list[cur].reg = &list[cur^1] ;
	list[cur].next = head[y] ;
	head[y] = &list[cur++] ;
}

void build(int x) {
	cur = 0 ; memset(head , 0 , sizeof(head)) ;

	for (int i = 1 ; i <= n ; ++i)
		if (a[i] >= 0) {
			if (a[i] & x) ins(i , T , INF) ;
			else ins(0 , i , INF) ;
		}
		else ins(0 , i , 1) ;

	for (int i = 0 ; i < m ; ++i) {
		Edge *p = &eg[i] ;
		ins(p->x , p->y , offset) ; ins(p->y , p->x , offset) ;
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
	n = read() ; m = read() ;
	T = n + 1 ; ll ans1 = 0 , ans2 = 0 ;

	for (int i = 1 ; i <= n ; ++i) a[i] = read() , ans2 += a[i] >= 0 ? a[i] : 0 ;
	for (int i = 0 ; i < m ; ++i) eg[i].x = read() , eg[i].y = read() ;

	///

	for (int i = 0 ; i <= 30 ; ++i) {
		int a = 1 << i ;
		build(a) ;

		int v = dinic() , v1 = v / offset , v2 = v % offset ;
		ans1 += (ll)a * v1 ; ans2 += (ll)a * v2 ;
	}

	printf("%lld\n%lld\n" , ans1 , ans2) ;

	return 0 ;
}