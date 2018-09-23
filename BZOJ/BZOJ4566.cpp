#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 2e5 + 10 ;

struct Link {
	int num ;
	Link *next ;
}list[MAX_N << 2] ;
struct Node {
	int len , cnt[2] ;
	Node *next[26] , *link ;
}sam[MAX_N << 2] ;

Node *last ;
Link *head[MAX_N] ;
int n , m , tot , cur ;
char s1[MAX_N] , s2[MAX_N] ;

void extend(int c , int ty) {
	Node *cur , *p = last ;

	if (p->next[c]) {
		Node *q = p->next[c] ;

		if (p->len + 1 == q->len) cur = q ;
		else {
			cur = &sam[tot++] ;
			*cur = *q ; cur->len = p->len + 1 ;
			cur->cnt[0] = cur->cnt[1] = 0 ;

			for (; p && p->next[c] == q ; p = p->link) p->next[c] = cur ;
			q->link = cur ;
		}
		++cur->cnt[ty] ; last = cur ;

		return ;
	}

	///

	cur = &sam[tot++] ;
	cur->len = last->len + 1 ; ++cur->cnt[ty] ;

	for (; p && !p->next[c] ; p = p->link) p->next[c] = cur ;

	if (!p) cur->link = &sam[0] ;
	else {
		Node *q = p->next[c] ;
		if (p->len + 1 == q->len) cur->link = q ;
		else {
			Node *clone = &sam[tot++] ;
			*clone = *q ; clone->len = p->len + 1 ;
			clone->cnt[0] = clone->cnt[1] = 0 ;

			for (; p && p->next[c] == q ; p = p->link) p->next[c] = clone ;
			q->link = cur->link = clone ;
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
	scanf("%s %s", s1 , s2) ;
	n = strlen(s1) ; m = strlen(s2) ;

	///

	last = &sam[tot++] ;
	last->len = 0 ; last->link = NULL ;

	for (int i = 0 ; i < n ; ++i) extend(s1[i] - 'a' , 0) ;
	last = &sam[0] ;
	for (int i = 0 ; i < m ; ++i) extend(s2[i] - 'a' , 1) ;

	///

	for (int i = 1 ; i < tot ; ++i) ins(sam[i].len , i) ;

	for (int i = std::max(n , m) ; i ; --i)
		for (Link *h = head[i] ; h ; h = h->next) {
			Node *p = &sam[h->num] ;

			for (int t = 0 ; t < 2 ; ++t) p->link->cnt[t] += p->cnt[t] ;
		}

	ll ans = 0 ;
	for (int i = 1 ; i < tot ; ++i) {
		Node *p = &sam[i] ;
		ll tmp = (ll)p->cnt[0] * p->cnt[1] * (p->len - p->link->len) ;

		ans += tmp ;
	}

	printf("%lld\n" , ans) ;

	return 0 ;
}