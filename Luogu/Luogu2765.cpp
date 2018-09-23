#include <queue>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
 
const int MAX_N = 4000 + 10 , MAX_E = 1e6 + 10 , idf = 2000 , INF = 0x3f3f3f3f ;

std::queue<int> q ;

struct Link {
	int num , flow ;
	Link *next , *reg ;
}list[MAX_E] ;

Link *head[MAX_N] ;
int n , m , T , cur ;
int ti , maxflow , ap[MAX_N] , dep[MAX_N] , to[MAX_N] ;

bool bfs() {
	q.push(0) ; ap[0] = ++ti ; dep[0] = 1 ;
	while (!q.empty()) {
		int x = q.front() ; q.pop() ;

		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (ap[nx] == ti || !h->flow) continue ;

			q.push(nx) ; dep[nx] = dep[x] + 1 ; ap[nx] = ti ;
		}
	}

	return ap[T] == ti ;
}

int dfs(int x , int f) {
	if (!f || x == T) return f ;
	
	int sum = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (dep[x] + 1 != dep[nx] || !h->flow) continue ;

		int nf = dfs(nx , std::min(f , h->flow)) ;
		h->flow -= nf ; f -= nf ;
		h->reg->flow += nf ; sum += nf ;
	}

	return sum ;
}

int dinic() {
	while (bfs()) maxflow += dfs(0 , INF) ;

	return maxflow ;
}

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].flow = 1 ;
	list[cur].next = head[x] ;
	list[cur].reg = &list[cur + 1];
	head[x] = &list[cur++] ;

	list[cur].num = x ;
	list[cur].flow = 0 ;
	list[cur].next = head[y] ;
	list[cur].reg = &list[cur - 1] ;
	head[y] = &list[cur++] ;
}

///
bool check(int tot) {
	m = tot ;
	ins(0 , m) ; ins(m + idf , T) ;

	for (int i = 1 ; i < m ; ++i) {
		int x = (int)sqrt(i + m) ;
		if (x * x == i + m) ins(i , m + idf) ;
	}

	int res = dinic() ;

	return (m - res) <= n ;
}

int main() {
	scanf("%d" , &n) ;
	int ans ; T = 4001 ; maxflow = 0 ;
	for (ans = 1 ; check(ans) ; ++ans) ;

	///

	--ans ;
	for (int i = 1 ; i <= ans ; ++i) {
		for (Link *h = head[i] ; h ; h = h->next) {
			if (h->flow || !h->num) continue ;

			to[i] = h->num - idf ; break ;
		}
	}

	///
	
	printf("%d\n" , ans) ;
	++ti ;
	for (int i = 1 ; i <= ans ; ++i) {
		if (ap[i] == ti) continue ;

		ap[i] = ti ;
		int j = i ;
		for (; j ; j = to[j]) printf("%d " , j) , ap[j] = ti ;
		printf("\n") ;
	}

	return 0 ;
}
