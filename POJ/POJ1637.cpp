#include <queue>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 200 + 10 , MAX_M = 4e3 + 10 , INF = 0x3f3f3f3f ;

struct Link {
	int num , flow ;
	Link *reg , *next ;
}list[MAX_M] ;

std::queue<int> q ;

Link *head[MAX_N] ;
int T , n , m , cur , ti , in[MAX_N] , ap[MAX_N] , dep[MAX_N] ;

bool bfs() {
	q.push(0) ; ap[0] = ++ti ; dep[0] = 1 ;

	while (!q.empty()) {
		int x = q.front() ; q.pop() ;

		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (ap[nx] == ti || !h->flow) continue ;

			q.push(nx) ; ap[nx] = ti ; dep[nx] = dep[x] + 1 ;
		}
	}

	return ap[n + 1] == ti ;
}

int dfs(int x , int f) {
	if (x == n + 1 || !f) return f ;

	int sum = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;

		if (dep[nx] != dep[x] + 1) continue ;

		int nf = dfs(nx , std::min(f , h->flow)) ;
		f -= nf ; h->flow -= nf ;
		h->reg->flow += nf ; sum += nf ;
	}

	if (f) dep[x] = -1 ;
	return sum ;
}

int dinic(int n) {
	int sum = 0 ;
	while (bfs()) sum += dfs(0 , INF) ;

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

void init() {
	cur = 0 ;
	memset(in , 0 , sizeof(in)) ;
	memset(head , 0 , sizeof(head)) ;
}

int main() {
	scanf("%d" , &T) ;
	while (T--) {
		init() ;

		scanf("%d %d" , &n , &m) ;
		for (int i = 0 ; i < m ; ++i) {
			int x , y , ty ;
			scanf("%d %d %d" , &x , &y , &ty) ;
			++in[x] ; --in[y] ;
			if (!ty) ins(x , y , 1) ;
		}

		int sum = 0 ; bool ans = 1 ;
		for (int i = 1 ; i <= n && ans ; ++i)
			if (in[i] % 2) ans = 0 ;
			else if (in[i] > 0) ins(0 , i , in[i] / 2) , sum += in[i] / 2 ;
			else if (in[i] < 0) ins(i , n + 1 , abs(in[i]) / 2) ;

		if (ans) {
			int f = dinic(0) ;
			if (f == sum) printf("possible\n") ;
			else printf("impossible\n") ;
		}
		else printf("impossible\n") ;
	}

	return 0 ;
}
