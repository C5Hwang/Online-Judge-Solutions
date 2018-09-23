#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e6 + 10 ;

struct Node {
	int cnt ;
	Node *ch[26] , *fail ;

	void init() {
		cnt = 0 ; fail = NULL ;
		for (int i = 0 ; i < 26 ; ++i) ch[i] = NULL ;
	}
}list[MAX_N] ;

char s[MAX_N] ;
int n , cur , len , L , R ;
Node *pt[MAX_N] , *root , *que[MAX_N] ;

Node *insert(Node *&rt , int p) {
	if (!rt) (rt = &list[cur++])->init() ;

	++rt->cnt ;
	if (p == len) return rt ;

	int c = s[p] - 'a' ;
	return insert(rt->ch[c] , p + 1) ;
}

void build() {
	que[1] = root ;
	root->fail = NULL ;

	L = 1 ; R = 1 ;
	for (; L <= R ;) {
		Node *x = que[L++] ;

		for (int i = 0 ; i < 26 ; ++i) {
			if (!x->ch[i]) continue ;

			Node *nx = x->ch[i] , *p = x->fail ;
			for (; p && !p->ch[i] ; p = p->fail) ;
			if (p) nx->fail = p->ch[i] ;
			else nx->fail = root ;

			que[++R] = nx ;
		}
	}

	for (; R > 1 ; --R) que[R]->fail->cnt += que[R]->cnt ;
}

int main() {
	scanf("%d" , &n) ;
	for (int i = 0 ; i < n ; ++i) {
		scanf("%s" , s) ; len = strlen(s) ;
		pt[i] = insert(root , 0) ;
	}

	///

	build() ;

	for (int i = 0 ; i < n ; ++i) printf("%d\n" , pt[i]->cnt) ;

	return 0 ;
}