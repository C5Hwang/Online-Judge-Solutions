#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 ;

struct Node {
	int len , cnt , ap ; ll f ;
	Node *ch[26] , *fail ;
}sam[MAX_N << 1] ;
struct Link {
	Node *p ;
	Link *next ;
}list[MAX_N << 1] ;

Node *last ;
ll ans[MAX_N] ;
Link *head[MAX_N] ;
char s[MAX_N] , ts[MAX_N] ;
int n , k , tot , cnt , cur , len , pl[MAX_N] ;

void extend(int c) {
	Node *p = last ;
	if (p->ch[c]) {
		Node *q = p->ch[c] ;
		if (p->len + 1 == q->len) last = q ;
		else {
			Node *cur = &sam[tot++] ;
			*cur = *q ; cur->len = p->len + 1 ;

			for (; p && p->ch[c] == q ; p = p->fail) p->ch[c] = cur ;
			q->fail = cur ; last = cur ;
		}

		return ;
	}

	///

	Node *cur = &sam[tot++] ;
	cur->len = p->len + 1 ;

	for (; p && !p->ch[c] ; p = p->fail) p->ch[c] = cur ;
	if (!p) cur->fail = &sam[0] ;
	else {
		Node *q = p->ch[c] ;
		if (p->len + 1 == q->len) cur->fail = q ;
		else {
			Node *clone = &sam[tot++] ;
			*clone = *q ; clone->len = p->len + 1 ;

			for (; p && p->ch[c] == q ; p = p->fail) p->ch[c] = clone ;
			cur->fail = q->fail = clone ;
		}
	}
	last = cur ;
}

void ins(int x , Node *y) {
	list[cur].p = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

int main() {
	scanf("%d %d" , &n , &k) ;

	tot = 1 ;
	for (int i = 1 ; i <= n ; ++i) {
		last = &sam[0] ;
		scanf("%s" , s) ; len = strlen(s) ;

		for (int j = 0 ; j < len ; ++j) {
			extend(s[j] - 'a') ;
			ts[cnt] = s[j] ; pl[cnt++] = i ;

			Node *p = last ;
			for (; p ; p = p->fail)
				if (p->ap != i) ++p->cnt , p->ap = i ;
				else break ;
		}
	}

	///

	int ml = 0 ;
	for (int i = 1 ; i < tot ; ++i) {
		Node *p = &sam[i] ;
		if (p->cnt >= k) p->f = p->len - p->fail->len ;
		ins(p->len , p) ; ml = std::max(ml , p->len) ;
	}

	for (int i = 1 ; i <= ml ; ++i)
		for (Link *h = head[i] ; h ; h = h->next)
			h->p->f += h->p->fail->f ;

	///

	Node *p = &sam[0] ; int np = -1 ;
	for (int i = 0 ; i < cnt ; ++i) {
		if (pl[i] != np) {np = pl[i] ; p = &sam[0] ;}

		int c = ts[i] - 'a' ;
		p = p->ch[c] ; ans[np] += p->f ;
	}

	for (int i = 1 ; i <= n ; ++i) printf("%lld " , ans[i]) ;

	return 0 ;
}