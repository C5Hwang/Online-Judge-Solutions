#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 100 + 10 , MAX_A = 1e3 + 10 , MAX_V = 2e4 + 10 , MAX_E = 8e4 + 10 , INF = 0x3f3f3f3f ;

std::queue<int> q ;

struct Link {
	int num , flow ;
	Link *next , *reg ;
}list[MAX_E] ;

Link *head[MAX_V] ;
int ti , cur , ap[MAX_V] , dep[MAX_V] ;
int tot , tbh[MAX_A] , abh[MAX_N][MAX_N] ;
int n , m , maxty , ty[MAX_N] , d[MAX_N][MAX_N] ;

///

bool bfs() {
	q.push(0) ; ap[0] = ++ti ; dep[0] = 1 ;
	while (!q.empty()) {
		int x = q.front() ; q.pop() ;

		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (!h->flow || ap[nx] == ti) continue ;

			q.push(nx) ; ap[nx] = ti ; dep[nx] = dep[x] + 1 ;
		}
	}

	return ap[tot] == ti ;
}

int dfs(int x , int f) {
	if (x == tot || !f) return f ;

	int sum = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (dep[x] + 1 != dep[nx]) continue ;

		int nf = dfs(nx , std::min(f , h->flow)) ;
		f -= nf ; h->flow -= nf ;
		h->reg->flow += nf ; sum += nf ;
	}

	if (f) dep[x] = -1 ;

	return sum ;
}

int dinic() {
	int sum = 0 ;
	while (bfs())
		sum += dfs(0 , INF) ;

	return sum ;
}

///

void ins(int x , int y , int v) {
	list[cur].num = y ;
	list[cur].flow = v ;
	list[cur].next = head[x] ;
	list[cur].reg = &list[cur + 1] ;
	head[x] = &list[cur++] ;

	list[cur].num = x ;
	list[cur].flow = 0 ;
	list[cur].next = head[y] ;
	list[cur].reg = &list[cur - 1] ;
	head[y] = &list[cur++] ;

}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 1 ; i <= n ; ++i) 
		scanf("%d" , &ty[i]) , maxty = std::max(maxty , ty[i]) ;

	for (int i = 1 ; i <= maxty ; ++i) tbh[i] = ++tot ;
	for (int i = 1 ; i <= n ; ++i)
		for (int j = i ; j <= n ; ++j)
			scanf("%d" , &d[i][j]) , abh[i][j] = ++tot ;

	///
	
	++tot ;
	int sum = 0 ;
	for (int i = 1 ; i <= maxty ; ++i) ins(tbh[i] , tot , m * i * i) ;
	for (int i = 1 ; i <= n ; ++i)
		for (int j = i ; j <= n ; ++j) {
			int cost = d[i][j] ;
			if (i == j) cost -= ty[i] ;

			if (cost > 0) ins(0 , abh[i][j] , cost) , sum += cost ;
			else ins(abh[i][j] , tot , -cost) ;

			if (i != j) {
				ins(abh[i][j] , abh[i + 1][j] , INF) ;
				ins(abh[i][j] , abh[i][j - 1] , INF) ;
			}
			else ins(abh[i][j] , tbh[ty[i]] , INF) ;
		}

	///
	
	printf("%d\n" , sum - dinic()) ;

	return 0 ;
}
