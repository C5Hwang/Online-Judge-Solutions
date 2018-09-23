#include <queue>
#include <stdio.h>
#include <stdlib.h>

const int MAX_N = 10000 + 10 , MAX_M = 20000 + 10 , INF = 0x3f3f3f3f ;

struct Link {
	int num , f ;
	Link *next , *reg ;
}list[4 * MAX_M + 6 * MAX_N] ;

std::queue<int> q ;

Link *head[4 * MAX_N] ;
int n1 , n2 , n3 , m1 , m2 , S , T ;
int time , cur , bft[4 * MAX_N] , dep[4 * MAX_N] ;

bool bfs() {
	q.push(S) ; bft[S] = ++time ; dep[S] = 1 ;
	while (!q.empty()) {
		int x = q.front() ; q.pop() ;
		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (!h->f || bft[nx] == time) continue ;

			q.push(nx) ;
			dep[nx] = dep[x] + 1 ; bft[nx] = time ;
		}
	}

	return bft[T] == time ;
}

int dfs(int x , int flow) {
	if (x == T || !flow) return flow ;

	int sum = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (dep[nx] != dep[x] + 1) continue ;

		int nf = dfs(nx , std::min(flow , h->f)) ;

		flow -= nf ;
		h->f -= nf ;
		h->reg->f += nf ;
		sum += nf ;

		if (!flow) break ;
	}
	if (flow) dep[x] = -1 ;

	return sum ;
}

int dinic() {
	int ans = 0 ;
	while (bfs()) {
		ans += dfs(S , INF) ;
	}

	return ans ;
}

void ins(int x , int y) {
	list[cur].f = 1 ;
	list[cur].num = y ;
	list[cur].next = head[x] ;
	list[cur].reg = &list[cur + 1] ;
	head[x] = &list[cur++] ;

	list[cur].f = 0 ;
	list[cur].num = x ;
	list[cur].next = head[y] ;
	list[cur].reg = &list[cur - 1] ;
	head[y] = &list[cur++] ;
}

int main() {
	scanf("%d %d %d" , &n1 , &n2 , &n3) ;
	scanf("%d" , &m1) ;
	for (int i = 0 ; i < m1 ; ++i) {
		int x , y ;
		scanf("%d %d" , &x , &y) ;
		x += n2 ;
		ins(y , x) ;
	}
	scanf("%d" , &m2) ;
	for (int i = 0 ; i < m2 ; ++i) {
		int x , y ;
		scanf("%d %d" , &x , &y) ;
		x += n2 + n1 ; y += n2 + 2 * n1 ;
		ins(x , y) ;
	}

	///
	
	S = 0 ; T = n1 * 2 + n2 + n3 + 1 ; 
	for (int i = 1 ; i <= n2 ; ++i) ins(S , i) ;
	for (int i = 1 ; i <= n1 ; ++i) ins(n2 + i , n1 + n2 + i) ;
	for (int i = 1 ; i <= n3 ; ++i) ins(i + n2 + n1 * 2 , T) ;

	///
	
	int res = dinic() ;
	printf("%d\n" , res) ;

	return 0 ;
}
