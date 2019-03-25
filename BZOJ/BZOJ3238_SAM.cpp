#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 5e5 + 10 ;

struct Link {
	int num ;
	Link *next ;
}list[MAX_N << 1] ;
struct Node {
	int len , pre , sum ;
	Node *link , *next[26] ;
}sam[MAX_N << 1] ;

ll ans ;
Node *last ;
char s[MAX_N] ;
int n , tot , cur ;
Link *head[MAX_N << 1] ;

int idx(Node *x) {return x - &sam[0] ;}

ll getsum(int x) {return (ll)x * (x + 1) / 2 ;}

void extend(int c) {
	Node *cur = &sam[tot++] , *p = last ;
	cur->len = last->len + 1 ; cur->pre = 1 ;

	for (; p && !p->next[c] ; p = p->link) p->next[c] = cur ;

	if (!p) cur->link = &sam[0] ;
	else {
		Node *q = p->next[c] ;
		if (p->len + 1 == q->len) cur->link = q ;
		else {
			Node *clone = &sam[tot++] ;
			*clone = *q ; clone->len = p->len + 1 ; clone->pre = 0 ;

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

void dfs(int x) {
	Node *p = &sam[x] ;
	p->sum = p->pre ;

	ll res = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ; Node *q = &sam[nx] ;

		dfs(nx) ;

		res += (ll)p->sum * q->sum ;
		p->sum += q->sum ;
	}
	res *= p->len ; res <<= 1 ;

	ans -= res ;
}

int main() {
	scanf("%s" , s) ; n = strlen(s) ;
	for (int i = 0 ; i < n ; ++i) {
		int j = n - i - 1 ;
		if (i < j) std::swap(s[i] , s[j]) ;
		else break ;
	}

	for (int i = 1 ; i < n ; ++i) {
		ll t1 = n - i , t2 = getsum(n) - getsum(i) ;
		ans += i * t1 + t2 ;
	}

	///

	last = &sam[tot++] ;
	last->len = last->pre = last->sum = 0 ;
	last->link = NULL ;

	for (int i = 0 ; i < n ; ++i) extend(s[i] - 'a') ;
	for (int i = 1 ; i < tot ; ++i) {
		Node *p = &sam[i] ;
		ins(idx(p->link) , idx(p)) ;
	}

	dfs(idx(&sam[0])) ;

	printf("%lld\n" , ans) ;

	return 0 ;
}