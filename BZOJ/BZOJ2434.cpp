#include <queue>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define idx(x) (x - root)
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 ;

struct data {int idx , x ;} ;
struct Link {
	int num ;
	Link *next ;
}list[MAX_N] ;
struct Node {
	std::vector<int> wd ;
	Node *ch[26] , *fail ;

	void init() {
		fail = NULL ;
		for (int i = 0 ; i < 26 ; ++i) ch[i] = NULL ;
	}
}acam[MAX_N] ;

std::queue<Node*> que ;
std::vector<data> qry[MAX_N] ;

char s[MAX_N] ;
Link *head[MAX_N] ;
Node *root , *pt[MAX_N] , *fa[MAX_N] ;
int dfn[MAX_N] , ed[MAX_N] , BIT[MAX_N] ;
int n , ti , len , tot , cur , cnt , ans[MAX_N] ;

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

void insert(Node *rt , int p) {
	if (p == len) return ;

	char c = s[p] ;
	if (c == 'P') {
		pt[++cnt] = rt ;
		rt->wd.push_back(cnt) ;
		insert(rt , p + 1) ;
	}
	else if (c == 'B') insert(fa[idx(rt)] , p + 1) ;
	else {
		int to = c - 'a' ;
		if (!rt->ch[to]) {
			(rt->ch[to] = &acam[tot++])->init() ;
			fa[idx(rt->ch[to])] = rt ;
		}
		insert(rt->ch[to] , p + 1) ;
	}
}

void build() {
	que.push(root) ;

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

void dfs(int x) {
	dfn[x] = ++ti ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		dfs(nx) ;
	}
	ed[x] = ti ;
}

int lowbit(int x) {return x & (-x) ;}

void modify(int x , int a) {
	for (; x <= tot ; x += lowbit(x)) BIT[x] += a ;
}

int getsum(int x) {
	int s = 0 ;
	for (; x ; x -= lowbit(x)) s += BIT[x] ;

	return s ;
}

int main() {
	scanf("%s" , s) ; len = strlen(s) ;
	scanf("%d" , &n) ;
	for (int i = 0 ; i < n ; ++i) {
		int x , y ; scanf("%d %d" , &x , &y) ;
		qry[y].push_back((data){i , x}) ;
	}

	///

	fa[0] = NULL ; (root = &acam[tot++])->init() ;

	insert(root , 0) ; build() ;
	dfs(idx(root)) ;

	///

	Node *rt = root ;
	for (int i = 0 ; i < len ; ++i) {
		char c = s[i] ;

		if (c == 'B') {
			modify(dfn[idx(rt)] , -1) ;
			rt = fa[idx(rt)] ;
		}
		else if (c == 'P') {
			int m = rt->wd.size() ;
			for (int i = 0 ; i < m ; ++i) {
				int y = rt->wd[i] ;

				int ql = qry[y].size() ;
				for (int j = 0 ; j < ql ; ++j) {
					data tmp = qry[y][j] ;

					int x = idx(pt[tmp.x]) ;
					ans[tmp.idx] = getsum(ed[x]) - getsum(dfn[x] - 1) ;
				}
			}
		}
		else {
			rt = rt->ch[c - 'a'] ;
			modify(dfn[idx(rt)] , 1) ;
		}
	}

	for (int i = 0 ; i < n ; ++i) printf("%d\n" , ans[i]) ;

	return 0 ;
}