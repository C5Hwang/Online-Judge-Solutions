#include <map>
#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passsing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 ;

struct Node {
	int len ;
	Node *link ;
	std::map<int , Node*> next ;
}sam[MAX_N << 1] ;

ll ans ;
Node *last ;
int n , tot ;

void extend(int c) {
	Node *cur = &sam[tot++] , *p = last ;
	cur->len = last->len + 1 ;

	for (; p && !p->next.count(c) ; p = p->link) p->next[c] = cur ;

	if (!p) cur->link = &sam[0] ;
	else {
		Node *q = p->next[c] ;
		if (q->len == p->len + 1) cur->link = q ;
		else {
			Node *clone = &sam[tot++] ;
			*clone = *q ; clone->len = p->len + 1 ;

			for (; p && p->next[c] == q ; p = p->link) p->next[c] = clone ;
			q->link = cur->link = clone ;
		}
	}
	last = cur ;
}

int main() {
	scanf("%d" , &n) ;
	last = &sam[tot++] ;
	last->len = 0 ; last->link = NULL ;

	for (int i = 0 ; i < n ; ++i) {
		int x ; scanf("%d" , &x) ;
		extend(x) ;

		ans += last->len - last->link->len ;
		printf("%lld\n" , ans) ;
	}

	return 0 ;
}