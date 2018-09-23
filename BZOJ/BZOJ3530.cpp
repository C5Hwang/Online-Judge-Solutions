#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_L = 1200 + 10 , MAX_N = 1500 + 10 , mod = 1e9 + 7 ;

struct Node {
	bool word ;
	int f[MAX_L][2][2] ;
	Node *ch[10] , *fail ;

	void init() {
		word = 0 ; fail = NULL ;
		for (int i = 0 ; i < 10 ; ++i) ch[i] = NULL ;
	}
}list[MAX_N] ;

int n , cur , len ;
Node *root , *que[MAX_N] ;
char num[MAX_N] , s[MAX_N] ;

void insert(Node *&rt , int p) {
	if (!rt) (rt = &list[cur++])->init() ;
	if (p == len) {rt->word = 1 ; return ;}

	int c = s[p] - '0' ;
	insert(rt->ch[c] , p + 1) ;
}

void build() {
	int L = 1 , R = 1 ;
	que[L] = root ;

	for (; L <= R ;) {
		Node *x = que[L++] ;
		for (int i = 0 ; i < 10 ; ++i) {
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

void dp(int L) {
	int c = num[L - 1] - '0' ;

	for (Node *x = root ; x != list + cur ; ++x) {
		if (x->word) continue ;

		for (int i = 0 ; i < 10 ; ++i) {
			Node *p = x ;
			for (; p && !p->ch[i] ; p = p->fail) ;
			if (p) p = p->ch[i] ;
			else p = root ;

			if (p->word) continue ;

			if (!i) {
				(root->f[L - 1][0][1] += x->f[L][0][1]) %= mod ;
				if (c) (root->f[L - 1][0][1] += x->f[L][1][1]) %= mod ;
				else (root->f[L - 1][1][1] += x->f[L][1][1]) %= mod ;

				(p->f[L - 1][0][0] += x->f[L][0][0]) %= mod ;
				if (c) (p->f[L - 1][0][0] += x->f[L][1][0]) %= mod ;
				else (p->f[L - 1][1][0] += x->f[L][1][0]) %= mod ;
			}
			else {
				p->f[L - 1][0][0] = ((ll)p->f[L - 1][0][0] + x->f[L][0][0] + x->f[L][0][1]) % mod ;
				if (c > i) p->f[L - 1][0][0] = ((ll)p->f[L - 1][0][0] + x->f[L][1][0] + x->f[L][1][1]) % mod ;
				else if (c == i) p->f[L - 1][1][0] = ((ll)p->f[L - 1][1][0] + x->f[L][1][0] + x->f[L][1][1]) % mod ;
			}
		}
	}
}

int main() {
	scanf("%s" , num) ;
	scanf("%d" , &n) ;
	for (int i = 0 ; i < n ; ++i) {
		scanf("%s" , s) ; len = strlen(s) ;
		insert(root , 0) ;
	}

	///

	build() ;

	len = strlen(num) ;
	for (int i = 0 ; i < len ; ++i) {
		int j = len - i - 1 ;
		if (i < j) std::swap(num[i] , num[j]) ;
	}

	root->f[len][1][1] = 1 ;
	for (int i = len ; i ; --i) dp(i) ;

	///

	int ans = 0 ;
	for (Node *x = root ; x != list + cur ; ++x)
		if (!x->word) ans = ((ll)ans + x->f[0][0][0] + x->f[0][1][0]) % mod ;
	printf("%d\n" , ans) ;

	return 0 ;
}