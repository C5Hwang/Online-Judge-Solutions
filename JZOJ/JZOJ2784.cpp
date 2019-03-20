#include <vector>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 ;

struct data {int x , idx ;} ;
struct Node {
	int idx ;
	Node *ch[26] , *fail , *fa ;
}tre[MAX_N] ;
struct Link {
	int num ;
	Link *next ;
}list[MAX_N << 1] ;

std::vector<data> qry[MAX_N] ;

char s[MAX_N] ;
Link *head[MAX_N] ;
Node *root , *que[MAX_N] ;
int n , m , cur , tot , L , R , ans[MAX_N] , BIT[MAX_N] , dfn[MAX_N] , ed[MAX_N] , pl[MAX_N] ;

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

void build() {
	L = R = 0 ;
	que[0] = root ;

	for (; L <= R ;) {
		Node *x = que[L++] ;

		for (int i = 0 ; i < 26 ; ++i) {
			Node *nx = x->ch[i] , *p = x->fail ;
			if (!nx) continue ;

			for (; p && !p->ch[i] ; p = p->fail) ;
			if (!p) nx->fail = root ;
			else nx->fail = p->ch[i] ;

			ins(nx->fail - root , nx - root) ; que[++R] = nx ;
		}
	}
}

void dfs(int x) {
	dfn[x] = ++tot ;
	for (Link *h = head[x] ; h ; h = h->next) dfs(h->num) ;
	ed[x] = tot ;
}

inline int lowbit(int x) {return x & (-x) ;}

int find(int x) {
	int s = 0 ;
	for (; x ; x -= lowbit(x)) s += BIT[x] ;

	return s ;
}

void modify(int x , int a) {
	for (; x <= tot ; x += lowbit(x)) BIT[x] += a ;
}

int main() {
	scanf("%s %d" , s , &m) ; n = strlen(s) ;
	for (int i = 0 ; i < m ; ++i) {
		int x , y ; scanf("%d %d" , &x , &y) ;
		qry[y].push_back((data){x , i}) ;
	}

	///

	root = &tre[tot++] ;
	Node *p = root ; cur = 0 ;
	for (int i = 0 ; i < n ; ++i) {
		if (s[i] == 'P') {
			p->idx = ++cur ; pl[cur] = p - root ;
		}
		else if (s[i] == 'B') p = p->fa ;
		else {
			int c = s[i] - 'a' ;
			if (!p->ch[c]) p->ch[c] = &tre[tot++] ;
			p->ch[c]->fa = p ; p = p->ch[c] ;
		}
	}

	cur = 0 ; build() ;

	///

	tot = 0 ; p = root ; dfs(0) ;
	for (int i = 0 ; i < n ; ++i) {
		if (s[i] == 'P') {
			int x = p->idx , siz = qry[x].size() ;

			for (int i = 0 ; i < siz ; ++i) {
				int nx = pl[qry[x][i].x] ;
				ans[qry[x][i].idx] = find(ed[nx]) - find(dfn[nx] - 1) ;
			}
		}
		else if (s[i] == 'B') {
			int id = p - root ; 
			modify(dfn[id] , -1) ; p = p->fa ;
		}
		else {
			int c = s[i] - 'a' , id ;
			p = p->ch[c] ; id = p - root ;
			modify(dfn[id] , 1) ;
		}
	}

	for (int i = 0 ; i < m ; ++i) printf("%d\n" , ans[i]) ;

	return 0 ;
}