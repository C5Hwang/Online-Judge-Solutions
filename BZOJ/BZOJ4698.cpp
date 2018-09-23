#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 ;

struct Node {
	Node *link ;
	int len , cnt , ap ;
	std::map<int , Node*> next ;
}sam[MAX_N << 1] ;

Node *root , *last ;
int n , m , tot , a[MAX_N] ;

void extend(int c , int n) {
	Node *p = last , *cur ;
	if (p->next.count(c)) {
		Node *q = p->next[c] ;

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
		for (; p && !p->next.count(c) ; p = p->link) p->next[c] = cur ;

		if (!p) cur->link = root ;
		else {
			Node *q = p->next[c] ;

			if (p->len + 1 == q->len) cur->link = q ;
			else {
				Node *clone = &sam[tot++] ;
				*clone = *q ; clone->len = p->len + 1 ;

				for (; p && p->next[c] == q ; p = p->link) p->next[c] = clone ;
				q->link = cur->link = clone ;
			}
		}
	}

	///

	last = cur ;
	for (p = cur ; p && p->ap < n ; p = p->link) ++p->cnt , p->ap = n ;
}

int main() {
	root = &sam[tot++] ;
	root->len = root->cnt = root->ap = 0 ; root->link = NULL ;

	scanf("%d" , &n) ;
	for (int i = 1 ; i <= n ; ++i) {
		scanf("%d" , &m) ;

		last = root ;
		for (int j = 0 ; j < m ; ++j) scanf("%d" , &a[j]) ;
		for (int j = 1 ; j < m ; ++j) extend(a[j - 1] - a[j] , i) ;
	}

	///

	int ans = 0 ;
	for (int i = 0 ; i < tot ; ++i) {
		Node *p = &sam[i] ;
		if (p->cnt == n) ans = std::max(ans , p->len) ;
	}

	printf("%d\n" , ans + 1) ;

	return 0 ;
}