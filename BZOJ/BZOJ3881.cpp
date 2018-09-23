#include <queue>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

#define idx(x) (x - root)
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 , MAX_L = 2e6 + 10 ;

struct Link {
	int num ;
	Link *next ;
}list[MAX_L] ;
struct Node {
	Node *ch[26] , *fail ;

	void init() {
		fail = NULL ;
		for (int i = 0 ; i < 26 ; ++i) ch[i] = NULL ;
	}
}acam[MAX_L] ;

std::queue<Node*> que ;

char s[MAX_L] ;
Link *head[MAX_L] ;
Node *root , *pt[MAX_N] ;
int cnt , qn[MAX_L] , fa[MAX_L] , siz[MAX_L] , lfa[MAX_L] ;
int n , q , len , tot , cur , ti , dfn[MAX_L] , ed[MAX_L] , dep[MAX_L] , BIT[MAX_L] ;

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
		
		fa[nx] = x ; dep[nx] = dep[x] + 1 ;
		dfs1(nx) ; siz[x] += siz[nx] ;
	}
}

void dfs2(int x , int f) {
	lfa[x] = f ; dfn[x] = ++ti ;

	int hson = -1 , s = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;

		if (siz[nx] > s) s = siz[nx] , hson = nx ;
	}

	if (hson != -1) dfs2(hson , f) ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == hson) continue ;

		dfs2(nx , nx) ;
	}

	ed[x] = ti ;
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

Node *insert(Node *&rt , int p) {
	if (!rt) (rt = &acam[tot++])->init() ;
	if (p == len) return rt ;

	int c = s[p] - 'a' ;
	return insert(rt->ch[c] , p + 1) ;
}

void build() {
	que.push(root) ;
	root->fail = NULL ;

	for (; !que.empty() ;) {
		Node *x = que.front() ; que.pop() ;
		for (int i = 0 ; i < 26 ; ++i) {
			Node *nx = x->ch[i] ;
			if (!nx) continue ;

			Node *p = x->fail ;
			for (; p && !p->ch[i] ; p = p->fail) ;
			if (p) nx->fail = p->ch[i] ;
			else nx->fail = root ;

			que.push(nx) ;
		}
	}

	for (Node *x = acam + 1 ; x != acam + tot ; ++x)
		ins(idx(x->fail) , idx(x)) ;
}

///

bool cmp(int x , int y) {return dfn[x] < dfn[y] ;}

int lowbit(int x) {return x & (-x) ;}

void modify(int x , int a) {
	for (; x <= tot ; x += lowbit(x)) BIT[x] += a ;
}

int getsum(int x) {
	int s = 0 ;
	for (; x ; x -= lowbit(x)) s += BIT[x] ;

	return s ;
}

///

int main() {
	scanf("%d" , &n) ;
	for (int i = 0 ; i < n ; ++i) {
		scanf("%s" , s) ; len = strlen(s) ;
		pt[i] = insert(root , 0) ;
	}

	///

	build() ;
	fa[idx(root)] = -1 ; dep[idx(root)] = 1 ;
	dfs1(idx(root)) ; dfs2(idx(root) , idx(root)) ;

	///

	scanf("%d" , &q) ;
	for (; q-- ;) {
		int op , x ; scanf("%d" , &op) ;
		if (op == 1) {
			scanf("%s" , s) ;
			len = strlen(s) ; cnt = 0 ;

			Node *rt = root ;
			for (int i = 0 ; i < len ; ++i) {
				int c = s[i] - 'a' ; Node *p = rt ;

				for (; p && !p->ch[c] ; p = p->fail) ;
				if (p) rt = p->ch[c] ;
				else rt = root ;

				qn[cnt++] = idx(rt) ;
			}

			///

			std::sort(qn + 0 , qn + cnt , cmp) ;
			for (int i = 0 ; i < cnt ; ++i) modify(dfn[qn[i]] , 1) ;
			for (int i = 1 ; i < cnt ; ++i) {
				int d = lca(qn[i] , qn[i - 1]) ;
				modify(dfn[d] , -1) ;
			}
		}
		else {
			scanf("%d" , &x) ; x = idx(pt[x - 1]) ;

			int ans = getsum(ed[x]) - getsum(dfn[x] - 1) ;
			printf("%d\n" , ans) ;
		}
	}

	return 0 ;
}