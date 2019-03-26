#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 ;

struct Node {
	int len ;
	Node *ch[26] , *fail ;

	void init() {
		fail = NULL ;
		for (int i = 0 ; i < 26 ; ++i) ch[i] = NULL ;
	}
}pam[MAX_N] ;

Node *last ;
char s[MAX_N] ;
int n , tot , s1[MAX_N] , s2[MAX_N] ;

void extend(int c , int n) {
	Node *p = last ;
	for (; s[n - 1 - p->len] != s[n] ; p = p->fail) ;

	if (p->ch[c]) last = p->ch[c] ;
	else {
		Node *cur = &pam[tot++] , *q = p->fail ;
		cur->init() ; cur->len = p->len + 2 ;

		for (; s[n - 1 - q->len] != s[n] ; q = q->fail) ;
		if (!q->ch[c]) cur->fail = &pam[1] ;
		else cur->fail = q->ch[c] ;

		p->ch[c] = cur ; last = cur ;
	}
}

void build(int *f , int ty) {
	tot = 2 ; last = &pam[0] ;
	pam[0].init() ; pam[1].init() ;
	pam[1].len = 0 ; pam[1].fail = &pam[0] ;
	pam[0].len = -1 ; pam[0].fail = &pam[0] ;

	for (int i = 1 ; i <= n ; ++i) {
		int j = ty ? n - i + 1 : i ;

		extend(s[i] - 'a' , i) ; f[j] = last->len ;
	}
}

int main() {
	scanf("%s" , s) ; n = strlen(s) ;

	///

	for (int i = n ; i ; --i) s[i] = s[i - 1] ;
	s[0] = '#' ; build(s1 , 0) ;

	for (int i = n ; i ; --i) {
		int j = n - i + 1 ;
		if (i > j) std::swap(s[i] , s[j]) ;
		else break ;
	}
	build(s2 , 1) ;

	///

	int ans = 0 ;
	for (int i = 1 ; i < n ; ++i) {
		int res = s1[i] + s2[i + 1] ;
		ans = std::max(ans , res) ;
	}

	printf("%d\n" , ans) ;

	return 0 ;
}