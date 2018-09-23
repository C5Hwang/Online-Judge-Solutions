#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 ;

struct Link {
	int num ;
	Link *next ;
}list[MAX_N << 1] ;
struct Node {
	int len , cnt , ap ; ll f ;
	Node *next[26] , *link ;
}sam[MAX_N << 1] ;

ll ans[MAX_N] ;
Link *head[MAX_N] ;
Node *last , *root ;
char s[MAX_N] , ts[MAX_N] ;
int n , k , L , len , tot , cur , pt[MAX_N] ;

void extend(int c , int n) {
	Node *p = last , *cur ;
	if (p->next[c]) {
		Node *q = p->next[c];

		if (p->len + 1 == q->len) cur = q ;
		else {
			cur = &sam[tot++] ;
			*cur = *q ; cur->len = p->len + 1 ;

			for (; p && p->next[c] == q ; p = p->link) p->next[c] = cur ;
			q->link = cur ;
		}
	}
	else {
		cur = &sam[tot++] ; cur->len = last->len + 1 ;

		for (; p && !p->next[c] ; p = p->link) p->next[c] = cur ;

		if (!p) cur->link = root ;
		else {
			Node *q = p->next[c] ;
			if (p->len + 1 == q->len) cur->link = q ;
			else {
				Node *clone = &sam[tot++] ;
				*clone = *q ; clone->len = p->len + 1 ;

				for (; p && p->next[c] == q ; p = p->link) p->next[c] = clone ;
				cur->link = q->link = clone ;
			}
		}
	}

	///

	last = cur ;
	for (p = cur ; p && p->ap != n ; p = p->link) ++p->cnt , p->ap = n ;
}

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

int main() {
	root = &sam[tot++] ;
	root->len = 0 ; root->cnt = 0 ; root->link = NULL ;

	scanf("%d %d" , &n , &k) ;
	for (int i = 1 ; i <= n ; ++i) {
		scanf("%s" , s) ; len = strlen(s) ;

		last = root ;
		for (int j = 0 ; j < len ; ++j) {
			extend(s[j] - 'a' , i) ;
			ts[L] = s[j] ; pt[L++] = i ;
		}
	}

	///

	for (int i = 1 ; i < tot ; ++i) {
		Node *p = &sam[i] ;
		ins(p->len , p - root) ;
	}

	for (int i = 1 ; i <= L ; ++i)
		for (Link *h = head[i] ; h ; h = h->next) {
			Node *p = &sam[h->num] ;

			if (p->cnt >= k) p->f = p->len - p->link->len ;
			p->f += p->link->f ;
		}

	///

	int np = 0 ; Node *p = root ;
	for (int i = 0 ; i < L ; ++i) {
		if (np != pt[i]) p = root , np = pt[i] ;

		p = p->next[ts[i] - 'a'] ;
		ans[np] += p->f ;
	}

	for (int i = 1 ; i <= n ; ++i) printf("%lld " , ans[i]) ;

	return 0 ;
}