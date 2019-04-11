#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const ll INF = 1e11 ;
const int MAX_N = 1e5 + 10 ;

struct Link {
	int num ;
	Link *next ;
}list[MAX_N << 1] ;
struct Matrix {
	ll num[2][2] ;

	void init() {
		for (int i = 0 ; i < 2 ; ++i)
			for (int j = 0 ; j < 2 ; ++j) num[i][j] = 0 ;
	}
	friend Matrix operator *(Matrix A , Matrix B) {
		Matrix C ;
		for (int i = 0 ; i < 2 ; ++i)
			for (int j = 0 ; j < 2 ; ++j) {
				ll tmp = INF ;
				for (int r = 0 ; r < 2 ; ++r) tmp = std::min(tmp , A.num[i][r] + B.num[r][j]) ;
				C.num[i][j] = tmp ;
			}

		return C ;
	}
}tre[MAX_N << 2] ;

char s[5] ;
Link *head[MAX_N] ;
int n , m , cur , ti , p[MAX_N] ;
ll f[MAX_N][2] , g[MAX_N][2] , nw[2][MAX_N] ;
int dfn[MAX_N] , dfl[MAX_N] , lfa[MAX_N] , fa[MAX_N] , siz[MAX_N] , ed[MAX_N] ;

///

void build(int t , int x , int y) {
	if (x == y) {
		x = dfl[x] ;
		tre[t].num[0][0] = INF ;
		tre[t].num[0][1] = g[x][0] ;
		tre[t].num[1][0] = tre[t].num[1][1] = g[x][1] ;

		return ;
	}

	int mid = (x + y) >> 1 ;
	build(t << 1 , x , mid) ; build(t << 1 | 1 , mid + 1 , y) ;

	tre[t] = tre[t << 1] * tre[t << 1 | 1] ;
}

Matrix find(int t , int x , int y , int fx , int fy) {
	if (fx <= x && y <= fy) return tre[t] ;

	int mid = (x + y) >> 1 ;
	if (fy <= mid) return find(t << 1 , x , mid , fx , fy) ;
	else if (mid < fx) return find(t << 1 | 1 , mid + 1 , y , fx , fy) ;

	return find(t << 1 , x , mid , fx , fy) * find(t << 1 | 1 , mid + 1 , y , fx , fy) ;
}

void modify(int t , int x , int y , int f , ll a , ll b) {
	if (f < x || y < f) return ;
	if (x == y) {
		tre[t].num[0][1] += a ;
		tre[t].num[1][0] += b ; tre[t].num[1][1] += b ;

		return ;
	}

	int mid = (x + y) >> 1 ;
	modify(t << 1 , x , mid , f , a , b) ;
	modify(t << 1 | 1 , mid + 1 , y , f , a , b) ;

	tre[t] = tre[t << 1] * tre[t << 1 | 1] ;
}

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

Matrix getans(int x) {
	Matrix A = find(1 , 1 , n , dfn[x] , ed[x]) , B ;
	B.init() ;

	return A * B ;
}

void update(int a , ll x , ll y) {
	ll mx = x - nw[0][a] , my = y - nw[1][a] ;
	nw[0][a] = x ; nw[1][a] = y ;

	for (; a ;) {
		int b = lfa[a] ;
		Matrix t1 = getans(b) , t2 ;
		modify(1 , 1 , n , dfn[a] , mx , my) ;
		t2 = getans(b) ;

		mx = t2.num[1][0] - t1.num[1][0] ;
		my = std::min(t2.num[0][0] , t2.num[1][0]) - std::min(t1.num[0][0] , t1.num[1][0]) ;

		a = fa[b] ;
	}
}

///

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
	int hson = -1 , s = 0 ;
	lfa[x] = f ; dfn[x] = ++ti ; dfl[ti] = x ;

	for (Link *h = head[x] ; h ; h = h->next)
		if (h->num != fa[x] && siz[h->num] > s) s = siz[h->num] , hson = h->num ;

	if (hson != -1) dfs2(hson , f) , ed[x] = ed[hson] ;
	else ed[x] = dfn[x] ;

	for (Link *h = head[x] ; h ; h = h->next)
		if (h->num != fa[x] && h->num != hson) dfs2(h->num , h->num) ;
}

void dp(int x) {
	f[x][1] = g[x][1] = p[x] ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa[x]) continue ;

		dp(nx) ;
		f[x][0] += f[nx][1] ;
		f[x][1] += std::min(f[nx][0] , f[nx][1]) ;
	}

	int fth = fa[x] ;
	if (fth && lfa[fth] != lfa[x])
		g[fth][0] += f[x][1] ,
		g[fth][1] += std::min(f[x][0] , f[x][1]) ;
}

///

int main() {
	n = read() ; m = read() ; scanf("%s" , s) ;
	for (int i = 1 ; i <= n ; ++i) p[i] = read() , nw[0][i] = 0 , nw[1][i] = p[i] ;
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

	for (; m-- ;) {
		int a , b , t1 , t2 ;
		a = read() ; t1 = read() ; b = read() ; t2 = read() ;

		if (t1) update(a , INF , p[a]) ;
		else update(a , 0 , INF) ;
		if (t2) update(b , INF , p[b]) ;
		else update(b , 0 , INF) ;

		///

		Matrix tmp = getans(1) ;
		ll ans = std::min(tmp.num[0][0] , tmp.num[1][0]) ;

		if (ans >= INF) printf("-1\n") ;
		else printf("%lld\n" , ans) ;

		update(a , 0 , p[a]) ; update(b , 0 , p[b]) ;
	}

	return 0 ;
}