#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ll long long

const int MAX_N = 9e4 + 10 ;

struct state {
	int len ; ll cnt ;
	state *next[30] , *link ;
}sam[MAX_N << 1] ;
struct Link {
	int num ;
	Link *next ;
}list[MAX_N << 1] ;

state *last ;
Link *head[MAX_N] ;
int n , m , tot , cur ;
char s[MAX_N] , ans[MAX_N] ;

void extend(int c) {
	state *cur = &sam[++tot] , *p = last ;
	cur->len = last->len + 1 ;

	for (; p && !p->next[c] ; p = p->link) p->next[c] = cur ;
	if (!p) cur->link = &sam[0] ;
	else {
		state *q = p->next[c] ;
		if (p->len + 1 == q->len) cur->link = q ;
		else {
			state *clone = &sam[++tot] ;
			*clone = *q ; clone->len = p->len + 1 ;

			for (; p && p->next[c] == q ; p = p->link) p->next[c] = clone ;
			cur->link = q->link = clone ;
		}
	}
	last = cur ;
}

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

int main() {
	scanf("%s" , s) ;
	n = strlen(s) ;
	
	///
	
	last = &sam[0] ;
	last->len = 0 ; last->link = NULL ;
	for (int i = 0 ; i < n ; ++i)
		extend(s[i] - 'a') ;
	for (int i = 0 ; i <= tot ; ++i) {
		state *p = &sam[i] ;
		ins(p->len , i) ;
	}
	for (int i = n ; i >= 0 ; --i)
		for (Link *h = head[i] ; h ; h = h->next) {
			int x = h->num ; ll s = 1 ;
			state *p = &sam[x] ;

			for (int j = 0 ; j < 26 ; ++j)
				if (p->next[j]) s += p->next[j]->cnt ;
			p->cnt = s ;
		}

	///

	scanf("%d" , &m) ;
	for (int i = 0 ; i < m ; ++i) {
		ll a ; scanf("%lld" , &a) ;
		a = sam[0].cnt - a ;

		///

		int l = 0 ;
		state *p = &sam[0] ;
		for (; a < p->cnt ;) {
			int c ;
			for (c = 25 ; c >= 0 ; --c)
				if (p->next[c] && p->next[c]->cnt < a) a -= p->next[c]->cnt ;
				else if (p->next[c]) break ;

			if (c < 0) break ;
			ans[l++] = c + 'a' ;
			p = p->next[c] ;
		}

		for (int i = 0 ; i < l ; ++i) printf("%c" , ans[i]) ;
		printf("\n") ;
	}	

	return 0 ;
}
