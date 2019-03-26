#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 ;

struct Node {
	int len , cnt[2] ;
	Node *ch[26] , *fail ;
}pam[MAX_N] ;

Node *last ;
int n , m , tot ;
char s1[MAX_N] , s2[MAX_N] ;

void extend(char *s , int n , int ty) {
	Node *p = last ;
	int c = s[n] - 'A' ;
	for (; s[n - 1 - p->len] != s[n] ; p = p->fail) ;

	if (p->ch[c]) last = p->ch[c] ;
	else {
		Node *cur = &pam[tot++] , *q = p->fail ;
		cur->len = p->len + 2 ;

		for (; s[n - 1 - q->len] != s[n] ; q = q->fail) ;
		if (!q->ch[c]) cur->fail = &pam[1] ;
		else cur->fail = q->ch[c] ;

		p->ch[c] = cur ; last = cur ;
	}
	++last->cnt[ty] ;
}

int main() {
	scanf("%s %s" , s1 , s2) ;
	n = strlen(s1) ; m = strlen(s2) ;

	///

	for (int i = n ; i ; --i) s1[i] = s1[i - 1] ;
	for (int i = m ; i ; --i) s2[i] = s2[i - 1] ;
	s1[0] = '#' ; s2[0] = '#' ;

	tot = 2 ; last = &pam[0] ;
	pam[1].len = 0 ; pam[1].fail = &pam[0] ;
	pam[0].len = -1 ; pam[0].fail = &pam[0] ;

	for (int i = 1 ; i <= n ; ++i) extend(s1 , i , 0) ;
	last = &pam[0] ;
	for (int i = 1 ; i <= m ; ++i) extend(s2 , i , 1) ;

	///

	ll ans = 0 ;
	for (int i = tot - 1 ; i > 1 ; --i) {
		Node *p = &pam[i] ;
		for (int j = 0 ; j < 2 ; ++j) p->fail->cnt[j] += p->cnt[j] ;
		ans += (ll)p->cnt[0] * p->cnt[1] ;
	}

	printf("%lld\n" , ans) ;

	return 0 ;
}