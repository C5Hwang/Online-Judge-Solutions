#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const ll INF = 1e15 ;
const int MAX_N = 1e5 + 10 , lgN = 16 + 5 , lim = 16 ;

struct area {int x , y ;}ar[MAX_N][lgN] ;
struct data {ll num , lazy ;}tre[MAX_N << 2] ;
struct Link {
	int num ;
	Link *next ;
}list[MAX_N << 1] ;

Link *head[MAX_N] ;
int n , m , ti , cur , w[MAX_N] , BIT[MAX_N] ;
int fa[MAX_N] , bfn[MAX_N] , dfn[MAX_N] , bls[MAX_N] , ed[MAX_N] ;

///

void down(int t) {
	ll a = tre[t].lazy ;
	int L = t << 1 , R = t << 1 | 1 ;
	if (!a) return ;

	tre[L].lazy += a ; tre[L].num += a ;
	tre[R].lazy += a ; tre[R].num += a ;
	tre[t].lazy = 0 ;
}

int find(int t , int x , int y) {
	if (x == y) return x ;
	down(t) ;

	ll a = tre[t].num ;
	int mid = (x + y) >> 1 ;
	if (tre[t << 1].num == a) return find(t << 1 , x , mid) ;
	else return find(t << 1 | 1 , mid + 1 , y) ;
}

void modify(int t , int x , int y , int fx , int fy , ll a) {
	if (y < fx || fy < x) return ;
	if (fx <= x && y <= fy) {
		tre[t].num += a ; tre[t].lazy += a ;
		return ;
	}
	down(t) ;

	int mid = (x + y) >> 1 ;
	modify(t << 1 , x , mid , fx , fy , a) ;
	modify(t << 1 | 1 , mid + 1 , y , fx , fy , a) ;

	tre[t].num = std::min(tre[t << 1].num , tre[t << 1 | 1].num) ;
}

void build(int t , int x , int y) {
	if (x == y) {
		tre[t].num = w[bls[x]] ;
		tre[t].lazy = 0 ;

		return ;
	}

	int mid = (x + y) >> 1 ;
	build(t << 1 , x , mid) ; build(t << 1 | 1 , mid + 1 , y) ;

	tre[t].num = std::min(tre[t << 1].num , tre[t << 1 | 1].num) ;
}

void bfs() {
	int L = 1 , R = 1 ;
	bls[1] = 1 ; bfn[1] = 1 ;

	for (; L <= R ;) {
		int x = bls[L++] ;

		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (bfn[nx]) continue ;

			bls[++R] = nx ; bfn[nx] = R ;
		}
	}

	for (int i = n ; i ; --i) {
		int x = bls[i] ;
		ar[x][0].x = ar[x][0].y = i ;

		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (bfn[nx] < bfn[x]) continue ;

			for (int j = 1 ; j <= lim ; ++j) {
				area *p = &ar[x][j] , *q = &ar[nx][j - 1] ;
				if (!q->x) break ;

				p->x = p->x ? std::min(p->x , q->x) : q->x ;
				p->y = p->y ? std::max(p->y , q->y) : q->y ;
			}
		}
	}
}

///

inline int lowbit(int x) {return x & (-x) ;}

inline void add(int x) {
	for (; x <= n ; x += lowbit(x)) ++BIT[x] ;
}

inline int getsum(int x) {
	int sum = 0 ;
	for (; x ; x -= lowbit(x)) sum += BIT[x] ;

	return sum ;
}

void dfs(int x) {
	dfn[x] = ++ti ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (dfn[nx]) continue ;

		fa[nx] = x ; dfs(nx) ;
	}

	ed[x] = ti ;
}

///

void reduce(int x , int a , int ty) {
	if (!a) return ;

	for (int i = 0 ; i <= lim && a ; ++i , a >>= 1) {
		if (!ar[x][i].x) return ;
		modify(1 , 1 , n , ar[x][i].x , ar[x][i].y , ty * a) ;
	}
}

void change(int x , int a) {
	reduce(x , a , -1) ;
	if (fa[x] && a > 1) {
		change(fa[x] , a >> 1) ;
		reduce(x , a >> 2 , 1) ;
	}
}

void update() {
	for (; tre[1].num <= 0 ;) {
		int x = find(1 , 1 , n) ;
		add(dfn[bls[x]]) ; modify(1 , 1 , n , x , x , INF) ;
	}
}

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

///

int main() {
	freopen("pang.in" , "r" , stdin) ;
	freopen("pang.out" , "w" , stdout) ;

	n = read() ;
	for (int i = 1 ; i <= n ; ++i) w[i] = read() ;
	for (int i = 1 ; i < n ; ++i) {
		int x , y ; x = read() ; y = read() ;

		ins(x , y) ; ins(y , x) ;
	}

	///

	bfs() ; build(1 , 1 , n) ;
	fa[1] = 0 ; dfs(1) ;

	///

	m = read() ;
	for (; m-- ;) {
		int op , x , a ;
		op = read() ; x = read() ;

		if (op == 1) {a = read() ; change(x , a) ; update() ;}
		else printf("%d\n" , getsum(ed[x]) - getsum(dfn[x] - 1)) ;
	}

	fclose(stdin) ; fclose(stdout) ;

	return 0 ;
}