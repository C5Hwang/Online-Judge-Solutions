#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 5e5 + 10 , MAX_T = 1e6 + 10 ;

struct Node {
	int len ;
	Node *ch[26] , *fail ;
}sam[MAX_T] ;
struct Link {
	int num ;
	Link *next ;
}list[MAX_T] ;

ll ans ;
Node *last ;
char s[MAX_N] ;
Link *head[MAX_T] ;
int R , tot , cur , cnt , vert[MAX_T << 2] , sta[MAX_T << 2] , f[MAX_T] ;
int n , m , ti , root[MAX_N] , dfn[MAX_T] , dep[MAX_T] , siz[MAX_T] , lfa[MAX_T] , fa[MAX_T] ;

///

void dfs1(int x) {
	siz[x] = 1 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;

		fa[nx] = x ; dep[nx] = dep[x] + 1 ;
		dfs1(nx) ; siz[x] += siz[nx] ;
	}
}

void dfs2(int x , int f) {
	lfa[x] = f ; dfn[x] = ++ti ;

	int hson = -1 , s = 0 ;
	for (Link *h = head[x] ; h ; h = h->next)
		if (siz[h->num] > s) s = siz[h->num] , hson = h->num ;

	if (hson != -1) dfs2(hson , f) ;

	for (Link *h = head[x] ; h ; h = h->next)
		if (h->num != hson) dfs2(h->num , h->num) ;
}

int lca(int x , int y) {
	for (; lfa[x] != lfa[y] ;) {
		if (dep[lfa[x]] > dep[lfa[y]]) std::swap(x , y) ;
		y = fa[lfa[y]] ;
	}

	if (dep[x] > dep[y]) return y ;
	else return x ;
}

///

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

void extend(int c) {
	Node *cur = &sam[tot++] , *p = last ;
	cur->len = last->len + 1 ;

	for (; p && !p->ch[c] ; p = p->fail) p->ch[c] = cur ;
	if (!p) cur->fail = &sam[0] ;
	else {
		Node *q = p->ch[c] ;
		if (p->len + 1 == q->len) cur->fail = q ;
		else {
			Node *clone = &sam[tot++] ;
			*clone = *q ; clone->len = p->len + 1 ;

			for (; p && p->ch[c] == q ; p = p->fail) p->ch[c] = clone ;
			cur->fail = q->fail = clone ;
		}
	}
	last = cur ;
}

bool cmp(int x , int y) {
	return dfn[x] < dfn[y] ;
}

void init() {
	cur = 0 ;
	for (int i = 0 ; i < cnt ; ++i) {
		int x = vert[i] ;
		head[x] = NULL ; f[x] = 0 ;
	}
}

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

///

void build(int n) {
	int R = 0 ;
	vert[cnt++] = 0 ; sta[++R] = 0 ;

	for (int i = 0 ; i < n ; ++i) {
		int x = vert[i] , tp = sta[R] , d = lca(x , tp) ;
		if (x == tp) continue ;

		if (d != tp) {
			for (; dep[sta[R - 1]] > dep[d] ;) {ins(sta[R - 1] , sta[R]) ; --R ;}

			ins(d , sta[R--]) ;
			if (sta[R] != d) {sta[++R] = d ; vert[cnt++] = d ;}
		}
		sta[++R] = x ;
	}

	for (int i = 1 ; i < R ; ++i) ins(sta[i] , sta[i + 1]) ;
}

void dp(int x) {
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ; dp(nx) ;
		ans += (ll)f[nx] * f[x] * sam[x].len ; f[x] += f[nx] ;
	}
}

///

int main() {
	n = read() ; m = read() ; scanf("%s" , s) ;
	for (int i = n ; i ; --i) s[i] = s[i - 1] ;
	for (int i = n ; i ; --i) {
		int j = n - i + 1 ;
		if (i > j) std::swap(s[i] , s[j]) ;
	}

	///

	last = &sam[tot++] ;
	for (int i = 1 ; i <= n ; ++i) extend(s[i] - 'a') ;

	Node *p = &sam[0] ;
	for (int i = 1 ; i <= n ; ++i) {
		p = p->ch[s[i] - 'a'] ;
		root[n - i + 1] = p - &sam[0] ;
	}

	vert[cnt++] = 0 ;
	for (int i = 1 ; i < tot ; ++i) {
		vert[cnt++] = i ;
		ins(sam[i].fail - &sam[0] , i) ;
	}

	fa[0] = 0 ; dep[0] = 1 ;
	dfs1(0) ; dfs2(0 , 0) ;

	///

	for (; m-- ;) {
		init() ; cnt = read() ;
		for (int i = 0 ; i < cnt ; ++i) {
			int x = read() ; x = root[x] ;
			vert[i] = x ; f[x] = 1 ;
		}
		std::sort(vert + 0 , vert + cnt , cmp) ;

		///

		build(cnt) ;
		ans = 0 ; dp(0) ;

		printf("%lld\n" , ans) ;
	}

	return 0 ;
}