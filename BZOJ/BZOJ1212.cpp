#include <queue>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e6 + 10 , MAX_M = 200 + 10 ;

struct Node {
	int len ; bool word ;
	Node *ch[26] , *fail , *last ;

	void init(int L) {
		len = L ; word = 0 ;
		fail = last = NULL ;
		for (int i = 0 ; i < 26 ; ++i) ch[i] = NULL ;
	}
}list[MAX_M] ;

std::queue<Node*> que ;

Node *root ;
bool f[MAX_N] ;
char s[MAX_N] ;
int n , m , cur , len ;

void add(Node *&rt , int p) {
	if (!rt) (rt = &list[cur++])->init(p) ;
	if (p == len) {rt->word = 1 ; return ;}

	int t = s[p] - 'a' ;
	add(rt->ch[t] , p + 1) ;
}

void build() {
	que.push(root) ;
	root->fail = root->last = NULL ;

	for (; !que.empty() ;) {
		Node *x = que.front() ; que.pop() ;

		for (int i = 0 ; i < 26 ; ++i) {
			if (!x->ch[i]) continue ;

			Node *p = x->fail , *nx = x->ch[i] ;

			for (; p && !p->ch[i] ; p = p->fail) ;
			if (p) nx->fail = p->ch[i] ;
			else nx->fail = root ;
			nx->last = nx->fail->word ? nx->fail : nx->fail->last ;

			que.push(nx) ;
		}
	}
}

void update(Node *rt , int p) {
	if (!rt) return ;

	if (rt->word) {
		int np = p - rt->len ;
		if (np < 0) f[p] = 1 ;
		else f[p] |= f[np] ;
	}
	update(rt->last , p) ;
}

void dp() {
	for (int i = 0 ; i < len ; ++i) f[i] = 0 ;

	Node *rt = root ;
	for (int i = 0 ; i < len ; ++i) {
		int c = s[i] - 'a' ;
		for (; rt != root && !rt->ch[c] ; rt = rt->fail) ;

		if (rt->ch[c]) {
			rt = rt->ch[c] ;
			update(rt , i) ;
		}
	}
}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 0 ; i < n ; ++i) {
		scanf("%s" , s) ;
		len = strlen(s) ; add(root , 0) ;
	}
	build() ;

	///

	for (int i = 0 ; i < m ; ++i) {
		scanf("%s" , s) ;
		len = strlen(s) ; dp() ;

		int ans = 0 ;
		for (int i = 0 ; i < len ; ++i) if (f[i]) ans = std::max(ans , i + 1) ;
		printf("%d\n" , ans) ;
	}

	return 0 ;
}