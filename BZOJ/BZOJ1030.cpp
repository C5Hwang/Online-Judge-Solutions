#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 6e3 + 10 , MAX_M = 100 + 10 , mod = 1e4 + 7 ;

struct Node {
	bool word ;
	int f[MAX_M] ;
	Node *ch[26] , *fail ;

	void init() {
		word = 0 ; fail = NULL ;
		for (int i = 0 ; i < MAX_M ; ++i) f[i] = 0 ;
		for (int i = 0 ; i < 26 ; ++i) ch[i] = NULL ;
	}
}list[MAX_N] , *que[MAX_N] ;

Node *root ;
char s[MAX_M] ;
int n , m , len , cur ;

void insert(Node *&rt , int p , bool sta) {
	if (!rt) (rt = &list[cur++])->init() ;

	rt->word |= sta ;
	if (p == len) {rt->word = 1 ; return ;}

	int c = s[p] - 'A' ;
	insert(rt->ch[c] , p + 1 , sta | rt->word) ;
}

void build() {
	int L = 1 , R = 1 ;
	que[L] = root ; root->fail = NULL ;

	for (; L <= R ;) {
		Node *x = que[L++] ;

		for (int i = 0 ; i < 26 ; ++i) {
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

void dp(int n) {
	for (Node *x = root ; x != list + cur ; ++x) {
		for (int i = 0 ; i < 26 ; ++i) {
			Node *p = x ;
			for (; p && !p->ch[i] ; p = p->fail) ;
			if (p) p = p->ch[i] ;
			else p = root ;

			if (!p->word) (p->f[n + 1] += x->f[n]) %= mod ;
		}
	}
}

int qpow(int a , int t) {
	if (t == 1) return a ;

	int s = qpow(a , t >> 1) ;
	(s *= s) %= mod ; if (t & 1) (s *= a) %= mod ;

	return s ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 0 ; i < n ; ++i) {
		scanf("%s" , s) ; len = strlen(s) ;
		insert(root , 0 , 0) ;
	}

	///

	build() ;

	///

	root->f[0] = 1 ;
	for(int i = 0 ; i < m ; ++i) dp(i) ;

	int ans = qpow(26 , m) ;
	for (Node *x = root ; x != list + cur ; ++x)
		if (!x->word) ans = (ans + mod - x->f[m]) % mod ;

	printf("%d\n" , ans) ;

	return 0 ;
}