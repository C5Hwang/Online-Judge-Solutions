#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 , INF = 0x3f3f3f3f ;

struct Link {
	int num ;
	Link *next ;
}list[MAX_N << 1] ;
struct Matrix {
	int num[2][2] ;

	void init() {
		for (int i = 0 ; i < 2 ; ++i)
			for (int j = 0 ; j < 2 ; ++j) num[i][j] = 0 ;
	}
	friend Matrix operator *(Matrix A , Matrix B) {
		Matrix C ;
		for (int i = 0 ; i < 2 ; ++i)
			for (int j = 0 ; j < 2 ; ++j) {
				int tmp = -INF ;
				for (int r = 0 ; r < 2 ; ++r) tmp = std::max(tmp , A.num[i][r] + B.num[r][j]) ;
				C.num[i][j] = tmp ;
			}

		return C ;
	}
}tre[MAX_N << 2] ;

Link *head[MAX_N] ;
int a[MAX_N] , f[MAX_N][2] , g[MAX_N][2] ;
int n , m , ti , cur , dfl[MAX_N] , dfn[MAX_N] , siz[MAX_N] , fa[MAX_N] , lfa[MAX_N] , ed[MAX_N] ;

///

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

///

Matrix find(int t , int x , int y , int fx , int fy) {
	if (fx <= x && y <= fy) return tre[t] ;

	int mid = (x + y) >> 1 ;
	if (fy <= mid) return find(t << 1 , x , mid , fx , fy) ;
	else if (mid < fx) return find(t << 1 | 1 , mid + 1 , y , fx , fy) ;

	return find(t << 1 , x , mid , fx , fy) * find(t << 1 | 1 , mid + 1 , y , fx , fy) ;
}

void modify(int t , int x , int y , int f , int a1 , int a2) {
	if (f < x || y < f) return ;
	if (x == y) {
		tre[t].num[0][0] += a1 ;
		tre[t].num[0][1] += a1 ;
		tre[t].num[1][0] += a2 ;

		return ;
	}

	int mid = (x + y) >> 1 ;
	modify(t << 1 , x , mid , f , a1 , a2) ;
	modify(t << 1 | 1 , mid + 1 , y , f , a1 , a2) ;

	tre[t] = tre[t << 1] * tre[t << 1 | 1] ;
}

void build(int t , int x , int y) {
	if (x == y) {
		x = dfl[x] ;
		tre[t].num[0][0] = tre[t].num[0][1] = g[x][0] ;
		tre[t].num[1][0] = g[x][1] ; tre[t].num[1][1] = -INF ;

		return ;
	}

	int mid = (x + y) >> 1 ;
	build(t << 1 , x , mid) ; build(t << 1 | 1 , mid + 1 , y) ;

	tre[t] = tre[t << 1] * tre[t << 1 | 1] ;
}

///

Matrix getans(int x) {
	Matrix t1 = find(1 , 1 , n , dfn[x] , ed[x]) , t2 ;
	t2.init() ;

	return t1 * t2 ;
}

void update(int x , int y) {
	int ma = 0 , mb = y - a[x] ; a[x] = y ;
	for (; x ;) {
		Matrix t1 = getans(lfa[x]) , t2 ;
		modify(1 , 1 , n , dfn[x] , ma , mb) ;
		t2 = getans(lfa[x]) ;

		ma = std::max(t2.num[0][0] , t2.num[1][0]) - std::max(t1.num[0][0] , t1.num[1][0]) ;
		mb = t2.num[0][0] - t1.num[0][0] ; x = fa[lfa[x]] ;
	}
}

void dfs1(int x) {
	siz[x] = 1 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa[x]) continue ;

		fa[nx] = x ;
		dfs1(nx) ; siz[x] += siz[nx] ;
	}
}

void dfs2(int x , int f) {
	dfn[x] = ++ti ; dfl[ti] = x ; lfa[x] = f ;

	int hson = -1 , s = 0 ;
	for (Link *h = head[x] ; h ; h = h->next)
		if (h->num != fa[x] && siz[h->num] > s) s = siz[h->num] , hson = h->num ;

	if (hson != -1) dfs2(hson , f) , ed[x] = ed[hson] ;
	else ed[x] = dfn[x] ;

	for (Link *h = head[x] ; h ; h = h->next)
		if (h->num != hson && h->num != fa[x]) dfs2(h->num , h->num) ;
}

void dp(int x) {
	int fth = fa[x] ;
	g[x][1] = f[x][1] = a[x] ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fth) continue ;

		dp(nx) ;
		f[x][1] += f[nx][0] ;
		f[x][0] += std::max(f[nx][0] , f[nx][1]) ;
	}

	if (fth && lfa[fth] != lfa[x]) {
		g[fth][0] += std::max(f[x][0] , f[x][1]) ;
		g[fth][1] += f[x][0] ;
	}
}

///

int main() {
	n = read() ; m = read() ;
	for (int i = 1 ; i <= n ; ++i) a[i] = read() ;
	for (int i = 1 ; i < n ; ++i) {
		int x , y ; x = read() ; y = read() ;

		ins(x , y) ; ins(y , x) ;
	}

	///

	fa[1] = 0 ; dfs1(1) ;
	dfs2(1 , 1) ;

	dp(1) ;
	build(1 , 1 , n) ;

	///

	for(; m-- ;) {
		int x , y ; x = read() ; y = read() ;

		update(x , y) ;
		Matrix tmp = getans(1) ;
		printf("%d\n" , std::max(tmp.num[0][0] , tmp.num[1][0])) ;
	}

	return 0 ;
}