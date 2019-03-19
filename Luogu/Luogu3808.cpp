#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e6 + 10 ;

struct Node {
	bool vis ;
	Node *ch[26] , *fail ;

	void init() {
		fail = NULL ; vis = 0 ;
		for (int i = 0 ; i < 26 ; ++i) ch[i] = NULL ;
	}
}acam[MAX_N] ;

char s[MAX_N] ;
int n , tot , L , R ;
Node *root , *ed[MAX_N] , *que[MAX_N] ;

Node* add() {
	Node *p = root ;
	for (int i = 0 ; i < n ; ++i) {
		int c = s[i] - 'a' ;

		if (!p->ch[c]) (p->ch[c] = &acam[tot++])->init() ;
		p = p->ch[c] ;
	}

	return p ;
}

void build() {
	root->fail = NULL ;

	L = R = 1 ; que[L] = root ;
	for (; L <= R ;) {
		Node *x = que[L++] ;

		for (int i = 0 ; i < 26 ; ++i) {
			Node *nx = x->ch[i] , *p = x->fail ;
			if (!nx) continue ;

			for (; p && !p->ch[i] ;) p = p->fail ;
			if (p) nx->fail = p->ch[i] ;
			else nx->fail = root ;

			que[++R] = nx ;
		}
	}
}

int main() {
	int T ; scanf("%d" , &T) ;

	(root = &acam[tot++])->init() ;
	for (int i = 0 ; i < T ; ++i) {
		scanf("%s" , s) ;
		n = strlen(s) ; ed[i] = add() ;
	}

	///

	build() ;

	Node *p = root ;
	scanf("%s" , s) ; n = strlen(s) ;
	for (int i = 0 ; i < n ; ++i) {
		int c = s[i] - 'a' ;
		
		for (; p && !p->ch[c] ; p = p->fail) ;
		if (!p) p = root ;
		else p = p->ch[c] ;

		p->vis = 1 ;
	}
	for (int i = R ; i > 1 ; --i) que[i]->fail->vis |= que[i]->vis ;

	int ans = 0 ;
	for (int i = 0 ; i < T ; ++i) if (ed[i]->vis) ++ans ;

	printf("%d\n" , ans) ;

	return 0 ;
}