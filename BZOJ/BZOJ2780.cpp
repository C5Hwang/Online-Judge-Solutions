#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 , MAX_L = 36e4 + 10 ;

struct Node {
	int len , cnt , ap ;
	Node *next[26] , *link ;
}sam[MAX_N << 1] ;

char s[MAX_L] ;
Node *root , *last ;
int n , m , len , tot ;

void extend(int c , int n) {
	Node *p = last , *cur ;

	if (p->next[c]) {
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
		cur = &sam[tot++] ;
		cur->len = last->len + 1 ;

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

int main() {
	root = &sam[tot++] ;
	root->len = root->cnt = root->ap = 0 ; root->link = NULL ;

	scanf("%d %d" , &n , &m) ;
	for (int i = 1 ; i <= n ; ++i) {
		scanf("%s" , s) ; len = strlen(s) ;

		last = root ;
		for (int j = 0 ; j < len ; ++j)	extend(s[j] - 'a' , i) ;
	}

	///

	for (int i = 0 ; i < m ; ++i) {
		scanf("%s" , s) ; len = strlen(s) ;

		Node *p = root ;
		for (int j = 0 ; j < len ; ++j) {
			int c = s[j] - 'a' ;
			if (p->next[c]) p = p->next[c] ;
			else {p = root ; break ;}
		}

		if (p == root) printf("0\n") ;
		else printf("%d\n" , p->cnt) ;
	}

	return 0 ;
}