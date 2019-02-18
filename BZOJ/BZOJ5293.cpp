#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 3e5 + 10 , MAX_K = 50 + 5 , K = 50 , mod = (119 << 23) + 1 ;

struct Link {
	int num ;
	Link *next ;
}list[MAX_N << 1] ;

Link *head[MAX_N] ;
int sum[MAX_N][MAX_K] ;
int n , m , cur , dep[MAX_N] , siz[MAX_N] , fa[MAX_N] , lfa[MAX_N] ;

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

void dfs1(int x , int f) {
	fa[x] = f ; siz[x] = 1 ;

	if (x != f) {
		int a = dep[x] , s = a ;
		for (int i = 1 ; i <= 50 ; ++i , s = (ll)s * a % mod)
			sum[x][i] = (sum[f][i] + s) % mod ;
	}

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == f) continue ;

		dep[nx] = dep[x] + 1 ;
		dfs1(nx , x) ; siz[x] += siz[nx] ;
	}
}

void dfs2(int x , int f) {
	int hson = -1 , s = 0 ;
	lfa[x] = f ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa[x]) continue ;

		if (siz[nx] > s) s = siz[nx] , hson = nx ;
	}

	if (hson != -1) dfs2(hson , f) ;

	for (Link *h = head[x] ; h ; h = h->next)
		if (h->num != fa[x] && h->num != hson) dfs2(h->num , h->num) ;
}

int lca(int x , int y) {
	for (; lfa[x] != lfa[y] ;) {
		if (dep[lfa[x]] > dep[lfa[y]]) x = fa[lfa[x]] ;
		else y = fa[lfa[y]] ;
	}

	return dep[x] > dep[y] ? y : x ;
}

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

int main() {
	n = read() ;
	for (int i = 1 ; i < n ; ++i) {
		int x , y ; x = read() ; y = read() ;

		ins(x , y) ; ins(y , x) ;
	}

	///

	dfs1(1 , 1) ; dfs2(1 , 1) ;

	m = read() ;
	for (; m-- ;) {
		int x , y , k , d , res ;
		x = read() ; y = read() ; k = read() ;
		d = lca(x , y) ;

		res = ((ll)mod + sum[x][k] + sum[y][k] - sum[d][k]) % mod ;
		if (d != 1) res = (res - sum[fa[d]][k] + mod) % mod ;

		printf("%d\n" , res) ;
	}

	return 0 ;
}