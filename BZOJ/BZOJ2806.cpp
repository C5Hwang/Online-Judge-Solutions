#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 11e5 + 10 ;

struct Node {
	int len ;
	Node *ch[2] , *fail ;
}sam[MAX_N << 1] ;

Node *last ;
char s[MAX_N] ;
int n , m , len , L , R , tot , f[MAX_N] , ml[MAX_N] , que[MAX_N] ;

void extend(int c) {
	Node *p = last ;
	if (p->ch[c]) {
		Node *q = p->ch[c] ;

		if (p->len + 1 == q->len) {last = q ; return ;}
		else {
			Node *cur = &sam[tot++] ;
			*cur = *q ; cur->len = p->len + 1 ;

			for (; p && p->ch[c] == q ; p = p->fail) p->ch[c] = cur ;
			q->fail = cur ; last = cur ; return ;
		}
	}

	///

	Node *cur = &sam[tot++] ;
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
			q->fail = cur->fail = clone ;
		}
	}
	last = cur ;
}

void push(int x) {
	for (; L <= R && f[x] <= f[que[R]] ; --R) ;
	que[++R] = x ;
}

void pop(int x) {
	for (; L <= R && que[L] < x ; ++L) ;
}

bool dp(int k) {
	for (int i = 0 ; i < k ; ++i) f[i] = i ;

	L = 1 ; R = 0 ;
	for (int i = k ; i <= len ; ++i) {
		f[i] = f[i - 1] + 1 ;

		push(i - k) ; pop(i - ml[i]) ;
		if (L > R) continue ;
		f[i] = std::min(f[que[L]] , f[i]) ;
	}

	int lim = len / 10 ;
	return f[len] <= lim ;
}

int getans() {
	int L = 0 , R = len + 1 ;

	for (; L + 1 < R ;) {
		int mid = (L + R) >> 1 ;
		if (dp(mid)) L = mid ;
		else R = mid ;
	}

	return L ;
}

int main() {
	scanf("%d %d" , &n , &m) ;

	last = &sam[tot++] ;
	for (int i = 0 ; i < m ; ++i) {
		scanf("%s" , s) ;

		len = strlen(s) ; last = &sam[0] ;
		for (int j = 0 ; j < len ; ++j) extend(s[j] - '0') ;
	}

	///

	for (; n-- ;) {
		scanf("%s" , s) ; len = strlen(s) ;
		for (int i = len ; i ; --i) s[i] = s[i - 1] ;

		///

		Node *p = &sam[0] ; int k = 0 ;
		for (int i = 1 ; i <= len ; ++i) {
			int c = s[i] - '0' ;
			for (; p && !p->ch[c] ; p = p->fail , k = p ? p->len : 0) ;

			if (p) p = p->ch[c] , ++k ;
			else p = &sam[0] ;
			ml[i] = k ;
		}

		printf("%d\n" , getans()) ;
	}

	return 0 ;
}