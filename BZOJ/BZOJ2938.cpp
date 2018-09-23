#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 3e4 + 10 ;

struct Node {
	bool word ;
	Node *ch[2] , *fail ;

	void init() {
		word = 0 ;
		ch[0] = ch[1] = fail = NULL ;
	}
}list[MAX_N] ;
struct Link {
	int num ;
	Link *next ;
}edge[MAX_N << 1] ;

char s[MAX_N] ;
Link *head[MAX_N] ;
int n , cur , tot , len ;
Node *root , *que[MAX_N] ;
bool ap[MAX_N] , cir[MAX_N] ;

void insert(Node *&rt , int p) {
	if (!rt) (rt = &list[cur++])->init() ;
	if (p == len) {rt->word = 1 ; return ;}

	int c = s[p] - '0' ;
	insert(rt->ch[c] , p + 1) ;
}

void build() {
	int L , R ; L = R = 1 ;
	que[L] = root ;

	for (; L <= R ;) {
		Node *x = que[L++] ;
		for (int i = 0 ; i < 2 ; ++i) {
			Node *nx = x->ch[i] ;
			if (!nx) continue ;

			Node *p = x->fail ;
			for (; p && !p->ch[i] ; p = p->fail) ;
			if (p) nx->fail = p->ch[i] ;
			else nx->fail = root ;

			que[++R] = nx ;
		}
	}

	for (int i = 2 ; i <= R ; ++i) que[i]->word |= que[i]->fail->word ;
}

void ins(int x , int y) {
	edge[tot].num = y ;
	edge[tot].next = head[x] ;
	head[x] = &edge[tot++] ;
}

bool dfs(int x) {
	ap[x] = 1 ; cir[x] = 1 ;

	bool ok = 0 ;
	for (Link *h = head[x] ; h && !ok ; h = h->next) {
		int nx = h->num ;
		if (cir[nx]) return 1 ;
		if (ap[nx]) continue ;

		ok |= dfs(nx) ;
	}

	cir[x] = 0 ;

	return ok ;
}

int main() {
	scanf("%d" , &n) ;
	for (int i = 0 ; i < n ; ++i) {
		scanf("%s" , s) ; len = strlen(s) ;
		insert(root , 0) ;
	}

	///

	build() ;
	for (Node *x = root ; x != list + cur ; ++x) {
		if (x->word) continue ;
		int idx = x - root ;

		for (int i = 0 ; i < 2 ; ++i) {
			Node *p = x ;
			for (; p && !p->ch[i] ; p = p->fail) ;
			if (p) p = p->ch[i] ;
			else p = root ;

			ins(idx , p - root) ;
		}
	}

	///

	bool ans = dfs(0) ;
	if (ans) printf("TAK\n") ;
	else printf("NIE\n") ;

	return 0 ;
}