#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std ;

const int MAX_N = 200 + 10 , MAX_M = 200 + 10 , INF = 0x3f3f3f3f ;

struct Link {
	int num , flow ;
	Link *next , *neg ;
}list[2 * MAX_M] ;

Link *head[MAX_N] ;
int S , T , n , m , bft , cur , res , dep[MAX_N] , bfn[MAX_N] , queue[MAX_N] ;

bool bfs() {
	int L = 0 , R = 1 ;
	bfn[S] = ++bft ; dep[S] = 1 ; queue[1] = S ;

	while (L < R) {
		int x = queue[++L] ;

		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (!h->flow || bfn[nx] == bft) continue ;

			bfn[nx] = bft ; dep[nx] = dep[x] + 1 ;
			queue[++R] = nx ;
		}
	}

	return bfn[T] == bft ;
}

int dfs(int x , int f) {
	if (x == T || !f) return f ;
	
	int sum = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		
		if (dep[nx] != dep[x] + 1 || !h->flow) continue ;
		
		int nf = dfs(nx , min(f , h->flow)) ;

		h->flow -= nf ; h->neg->flow += nf ;
		f -= nf ; sum += nf ;
	}
	if(f) dep[x] = -1 ;

	return sum ;
}

int Dinic() {
	int sum = 0 ;
	while (bfs()) sum += dfs(S , INF) ;

	return sum ;
}

void ins(int x , int y , int f) {
	list[cur].num = y ;
	list[cur].flow = f ;
	list[cur].next = head[x] ;
	list[cur].neg = &list[cur + 1] ;
	head[x] = &list[cur++] ;

	list[cur].num = x ;
	list[cur].flow = 0 ;
	list[cur].next = head[y] ;
	list[cur].neg = &list[cur - 1] ;
	head[y] = &list[cur++] ;
}

void init() {
	cur = bft = 0 ;
	memset(bfn , 0 , sizeof(bfn)) ;
	memset(head , 0 , sizeof(head)) ;
}

int main() {
	while (scanf("%d %d" , &m , &n) != EOF)	{
		init() ;
	
		S = 1 ; T = n ;
		for (int i = 0 ; i < m ; ++i) {
			int x , y , f ;
			scanf("%d %d %d" , &x , &y , &f) ;
			ins(x , y , f) ;
		}
	
		///
	
		res = Dinic() ;
	
		printf("%d\n" , res) ;
	}

	return 0 ;
}
