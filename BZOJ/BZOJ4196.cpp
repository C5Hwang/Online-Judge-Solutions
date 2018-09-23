#include <stdio.h>
#include <stdlib.h>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 ;

struct Link {
	int num ;
	Link *next ;
}list[MAX_N] ;
struct Node {
	int sum[2] , lazy ;
}tree[MAX_N << 2] ;

Link *head[MAX_N] ;
int n , q , ti , cur ;
int siz[MAX_N] , dfn[MAX_N] , ed[MAX_N] , fa[MAX_N] , lfa[MAX_N] ;

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

		fa[nx] = x ;
		dfs1(nx) ; siz[x] += siz[nx] ;
	}
}

void dfs2(int x , int f) {
	dfn[x] = ++ti ; lfa[x] = f ;

	int hson = -1 , s = 0 ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa[x]) continue ;

		if (siz[nx] > s) hson = nx , s = siz[nx] ;
	}

	if (hson != -1) dfs2(hson , f) ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa[x] || nx == hson) continue ;

		dfs2(nx , nx) ;
	}

	ed[x] = ti ;
}

void update(int t) {
	int L = t << 1 , R = L | 1 ;

	for (int i = 0 ; i < 2 ; ++i)
		tree[t].sum[i] = tree[L].sum[i] + tree[R].sum[i] ;
}

void down(int t , int x , int y) {
	if (tree[t].lazy == -1) return ;

	int mid = (x + y) >> 1 , L = t << 1 , R = L | 1 , a = tree[t].lazy ;

	tree[L].sum[a] = (mid - x + 1) ; tree[L].sum[a^1] = 0 ;
	tree[R].sum[a] = y - mid ; tree[R].sum[a^1] = 0 ;

	tree[L].lazy = tree[R].lazy = a ;
	tree[t].lazy = -1 ;
}

void build(int t , int x , int y) {
	if (x == y) {
		tree[t].sum[0] = 1 ; tree[t].sum[1] = 0 ;
		tree[t].lazy = -1 ;

		return ;
	}

	int mid = (x + y) >> 1 ;
	build(t << 1 , x , mid) ; build(t << 1 | 1 , mid + 1 , y) ;

	update(t) ;
}

int modify(int t , int x , int y , int fx , int fy , int a) {
	if (y < fx || fy < x) return 0 ;
	if (fx <= x && y <= fy) {
		int res = tree[t].sum[a^1] ;

		tree[t].lazy = a ;
		tree[t].sum[a] = (y - x + 1) ; tree[t].sum[a^1] = 0 ;

		return res ;
	}
	down(t , x , y) ;

	int mid = (x + y) >> 1 ,
		s1 = modify(t << 1 , x , mid , fx , fy , a) ,
		s2 = modify(t << 1 | 1 , mid + 1 , y , fx , fy , a) ;

	update(t) ;

	return s1 + s2 ;
}

int main() {
	scanf("%d" , &n) ;
	for (int i = 1 ; i < n ; ++i) {
		int x ; scanf("%d" , &x) ;
		ins(x , i) ;
	}

	///

	fa[0] = -1 ;
	dfs1(0) ; dfs2(0 , 0) ;

	build(1 , 1 , n) ;

	///

	scanf("%d" , &q) ;
	for (; q-- ;) {
		char s[20] ; int x ;
		scanf("%s %d" , s , &x) ;

		if (s[0] == 'i') {
			int ans = 0 ;

			for (int p = x ; p != -1 ; p = fa[p]) {
				int L = dfn[lfa[p]] , R = dfn[p] ;
				ans += modify(1 , 1 , n , L , R , 1) ;

				p = lfa[p] ;
			}

			printf("%d\n" , ans) ;
		}
		else {
			int ans = modify(1 , 1 , n , dfn[x] , ed[x] , 0) ;

			printf("%d\n" , ans) ;
		}
	}

	return 0 ;
}