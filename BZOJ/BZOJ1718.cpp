#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 5e3 + 10 , MAX_M = 1e4 + 10 ;

struct Link {
	int num ;
	bool flag ;
	Link *next , *reg ;
}list[MAX_M << 1] ;
struct Edge {
	int x , y ;
}eg[MAX_M] ;

Link *head[MAX_N] ;
int cnt , bk[MAX_N] , in[MAX_N] ;
int n , m , ti , cur , dfn[MAX_N] , low[MAX_N] ;

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	list[cur].reg = &list[cur^1] ;
	head[x] = &list[cur++] ;

	list[cur].num = x ;
	list[cur].next = head[y] ;
	list[cur].reg = &list[cur^1] ;
	head[y] = &list[cur++] ;
}

void dfs(int x) {
	dfn[x] = low[x] = ++ti ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (h->flag) continue ;

		if (!dfn[nx]) {
			h->reg->flag = 1 ;
			dfs(nx) ;

			low[x] = std::min(low[x] , low[nx]) ;
			if (low[nx] > dfn[x]) h->flag = 1 ;
			else h->reg->flag = 0 ;
		}
		else low[x] = std::min(dfn[nx] , low[x]) ;
	}
}

void find(int x) {
	bk[x] = cnt ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (h->flag) continue ;

		if (!bk[nx]) h->reg->flag = 1 , find(nx) ;
	}
}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 0 ; i < m ; ++i) {
		int a , b ; scanf("%d %d" , &a , &b) ;

		ins(a , b) ; eg[i] = (Edge){a , b} ;
	}

	///

	dfs(1) ;
	for(int i = 1 ; i <= n ; ++i)
		if (!bk[i]) ++cnt , find(i) ;

	for (int i = 0 ; i < m ; ++i) {
		Edge *p = &eg[i] ;
		p->x = bk[p->x] ; p->y = bk[p->y] ;

		if (p->x == p->y) continue ;
		++in[p->x] ; ++in[p->y] ;
	}

	int ans = 0 ;
	for (int i = 1 ; i <= cnt ; ++i) if (in[i] == 1) ++ans ;

	printf("%d\n" , (ans + 1) >> 1) ;

	return 0 ;
}