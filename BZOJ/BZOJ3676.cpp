#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 3e5 + 10 ;

struct Node {
	int len , cnt ;
	Node *ch[26] , *fail ;
}pam[MAX_N] ;

ll ans ;
Node *last ;
int n , tot ;
char s[MAX_N] ;

void extend(int c , int L) {
	Node *p = last ;
	for (; s[L - 1 - p->len] != s[L] ; p = p->fail) ;

	if (p->ch[c]) last = p->ch[c] ;
	else {
		Node *cur = &pam[tot++] , *q = p->fail ;
		cur->len = p->len + 2 ;

		for (; s[L - 1 - q->len] != s[L] ; q = q->fail) ;
		if (!q->ch[c]) cur->fail = &pam[1] ;
		else cur->fail = q->ch[c] ;

		p->ch[c] = cur ; last = cur ;
	}
	++last->cnt ;
}

int main() {
	scanf("%s" , s) ; n = strlen(s) ;

	///

	last = &pam[1] ; tot = 2 ;
	pam[0].len = -1 ; pam[1].len = 0 ;
	pam[0].fail = &pam[0] ; pam[1].fail = &pam[0] ;

	for (int i = n ; i ; --i) s[i] = s[i - 1] ;
	s[0] = '#' ;
	for (int i = 1 ; i <= n ; ++i) extend(s[i] - 'a' , i) ;

	///

	ans = 0 ;
	for (int i = tot - 1 ; i > 0 ; --i) {
		Node *p = &pam[i] ;
		p->fail->cnt += p->cnt ;
		ans = std::max(ans , (ll)p->cnt * p->len) ;
	}

	printf("%lld\n" , ans) ;

	return 0 ;
}