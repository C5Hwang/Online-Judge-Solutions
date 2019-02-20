#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const ll INF = 1e15 ;
const int MAX_N = 500 + 10 , MAX_P = 1e3 + 10 , MAX_M = 1e5 + 10 ;

struct Link {
	int num ; ll cap ;
	Link *next , *reg ;
}list[(MAX_M + MAX_N) << 1] ;

std::queue<int> que ;

Link *head[MAX_P] ;
ll f[MAX_N][MAX_N] ;
int n , m , cur , x[MAX_M] , y[MAX_M] , v[MAX_M] ;
int T , ti , tot , bh[MAX_N][2] , ap[MAX_P] , dep[MAX_P] ;

void ins(int x , int y , ll v) {
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

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

ll dfs(int x , ll f) {
	if (!f || x == T) return f ;

	ll sum = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (dep[nx] != dep[x] + 1) continue ;

		ll nf = dfs(nx , std::min(f , h->cap)) ;
		sum += nf ; h->reg->cap += nf ;
		h->cap -= nf ; f -= nf ;
	}
	if (f) dep[x] = -1 ;

	return sum ;
}

bool bfs() {
	int S = bh[1][0] ;
	que.push(S) ; ap[S] = ++ti ; dep[S] = 1 ;

	for (; !que.empty() ;) {
		int x = que.front() ; que.pop() ;
		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (ap[nx] == ti || !h->cap) continue ;

			que.push(nx) ;
			ap[nx] = ti ; dep[nx] = dep[x] + 1 ;
		}
	}

	return ap[T] == ti ;
}

ll dinic() {
	ll sum = 0 ;
	for (; bfs() ;) sum += dfs(1 , INF) ;

	return sum ;
}

int main() {
	n = read() ; m = read() ;
	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= n ; ++j)
			f[i][j] = i == j ? 0 : INF ;

	for (int i = 0 ; i < m ; ++i) {
		int tx , ty ;
		tx = read() ; ty = read() ; v[i] = read() ;
		f[tx][ty] = std::min(f[tx][ty] , (ll)v[i]) ; f[ty][tx] = std::min(f[ty][tx] , (ll)v[i]) ;

		x[i] = tx ; y[i] = ty ;
	}

	///

	bh[1][0] = bh[1][1] = ++tot ;
	for (int i = 2 ; i < n ; ++i) bh[i][0] = ++tot , bh[i][1] = ++tot ;
	bh[n][0] = bh[n][1] = T = ++tot ;

	for (int i = 1 ; i <= n ; ++i) {
		int v = read() ;
		if (i == 1 || i == n) continue ;
		ins(bh[i][0] , bh[i][1] , v) ;
	}

	for (int k = 1 ; k <= n ; ++k)
		for (int i = 1 ; i <= n ; ++i)
			for (int j = 1 ; j <= n ; ++j)
				f[i][j] = std::min(f[i][j] , f[i][k] + f[k][j]) ;

	for (int i = 0 ; i < m ; ++i) {
		int tx = x[i] , ty = y[i] ;
		if (f[1][n] - v[i] == f[1][tx] + f[ty][n]) ins(bh[tx][1] , bh[ty][0] , INF) ;
		if (f[1][n] - v[i] == f[1][ty] + f[tx][n]) ins(bh[ty][1] , bh[tx][0] , INF) ;
	}

	///

	ll ans = dinic() ;
	printf("%lld\n" , ans) ;

	return 0 ;
}