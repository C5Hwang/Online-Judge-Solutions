#include <vector>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

#pragma comment(linker, "/STACK:1024000000,1024000000")
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 ;

struct data{int x , y , val ;} ;
struct Link {
	int num ;
	Link *next ;
}list[MAX_N << 1] ;

std::vector<data> eg[MAX_N] ;

Link *head[MAX_N] ;
int Q , n , m , cur , tot , f[MAX_N] , BIT[2][MAX_N] ;
int siz[MAX_N] , dep[MAX_N] , lfa[MAX_N] , fa[MAX_N] , num[MAX_N] ;

///

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

void dfs1(int x) {
	siz[x] = 1 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa[x]) continue ;

		fa[nx] = x ; dep[nx] = dep[x] + 1 ;
		dfs1(nx) ; siz[x] += siz[nx] ;
	}
}

void dfs2(int x , int f) {
	lfa[x] = f ; num[x] = ++tot ;

	int hson = -1 , s = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa[x]) continue ;

		if (siz[nx] > s) s = siz[nx] , hson = nx ;
	}

	if (hson != -1) dfs2(hson , f) ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa[x] || nx == hson) continue ;

		dfs2(nx , nx) ;
	}
}

int lca(int x , int y) {
	for (; lfa[x] != lfa[y] ;) {
		if (dep[lfa[x]] < dep[lfa[y]]) std::swap(x , y) ;
		x = fa[lfa[x]] ;
	}

	if (dep[x] > dep[y]) std::swap(x , y) ;

	return x ;
}

///

int lowbit(int x) {return x & (-x) ;}

void modify(int ty , int x , int a) {
	for (; x <= n ; x += lowbit(x)) BIT[ty][x] += a ;
}

int find(int ty , int x) {
	int sum = 0 ;
	for (; x ; x -= lowbit(x)) sum += BIT[ty][x] ;
	return sum ;
}

int query(int ty , int x , int y) {
	return find(ty , y) - find(ty , x - 1) ;
}

int getsum(int ty , int x , int y) {
	int sum = 0 ;
	for (; lfa[x] != lfa[y] ;) {
		if (dep[lfa[x]] < dep[lfa[y]]) std::swap(x , y) ;
		sum += query(ty , num[lfa[x]] , num[x]) ;
		x = fa[lfa[x]] ;
	}

	if (dep[x] > dep[y]) std::swap(x , y) ;
	sum += query(ty , num[x] , num[y]) ;

	return sum ;
}

///

void dp(int x) {
	f[x] = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa[x]) continue ;
		dp(nx) ; f[x] += f[nx] ;
	}

	modify(0 , num[x] , f[x]) ;

	for (int i = 0 ; i < eg[x].size() ; ++i) {
		data e = eg[x][i] ;
		int tmp = getsum(0 , e.x , e.y) - getsum(1 , e.x , e.y) ;
		f[x] = std::max(f[x] , tmp + e.val) ;
	}

	modify(1 , num[x] , f[x]) ;
}

void init() {
	cur = tot = 0 ;
	for (int i = 1 ; i <= n ; ++i) eg[i].clear() ;
	memset(BIT , 0 , sizeof(BIT)) ;
	memset(head , 0 , sizeof(head)) ;
}

inline int read() {
	int num = 0 , f = 1 ;
	char c = getchar() ;
	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 + c - '0' ;

	return num * f ;
}

///

int main() {
	Q = read() ;
	for (; Q-- ;) {
		n = read() ; m = read() ; init() ;
		for (int i = 1 ; i < n ; ++i) {
			int x , y ;
			x = read() ; y = read() ;
			ins(x , y) ; ins(y , x) ;
		}

		///

		fa[1] = -1 ; dep[1] = 1 ; dfs1(1) ; dfs2(1 , 1) ;
		for (int i = 0 ; i < m ; ++i) {
			int x , y , v , d ;
			x = read() ; y = read() ; v = read() ;
			d = lca(x , y) ; eg[d].push_back((data){x , y , v}) ;
		}

		///

		dp(1) ;
		printf("%d\n" , f[1]) ;
	}

	return 0 ;
}