#include <queue>
#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 , MAX_V = 2e6 + 10 ;

struct Link {
	int num ;
	Link *next ;
}list[MAX_N << 1] ;
struct Node {
	int len ;
	Node *next[15] , *link ;
}sam[MAX_V << 1] ;

std::queue<int> que ;

bool ap[MAX_N] ;
Link *head[MAX_N] ;
Node *root[MAX_N] ;
int n , c , cur , tot , cnt[MAX_N] , col[MAX_N] , fa[MAX_N] ;

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

Node *extend(Node *p , int c) {
	if (p->next[c]) {
		Node *q = p->next[c] ;

		if (p->len + 1 == q->len) return q ;
		else {
			Node *clone = &sam[tot++] ;
			*clone = *q ; clone->len = p->len + 1 ;

			for (; p && p->next[c] == q ; p = p->link) p->next[c] = clone ;
			q->link = clone ;

			return clone ;
		}
	}

	///

	Node *cur = &sam[tot++] ; cur->len = p->len + 1 ;
	for (; p && !p->next[c] ; p = p->link) p->next[c] = cur ;

	if (!p) cur->link = &sam[0] ;
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

	return cur ;
}

void bfs(int S) {
	for (int i = 1 ; i <= n ; ++i) ap[i] = 0 , fa[i] = -1 ;
	fa[S] = 0 ; que.push(S) ; ap[S] = 1 ;

	for (; !que.empty() ;) {
		int x = que.front() ; que.pop() ;
		root[x] = extend(root[fa[x]] , col[x]) ;

		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (ap[nx]) continue ;

			fa[nx] = x ; ap[nx] = 1 ;
			que.push(nx) ;
		}
	}
}

int main() {
	scanf("%d %d" , &n , &c) ;
	for (int i = 1 ; i <= n ; ++i) scanf("%d" , &col[i]) ;
	for (int i = 1 ; i < n ; ++i) {
		int x , y ; scanf("%d %d" , &x , &y) ;
		ins(x , y) ; ins(y , x) ; ++cnt[x] ; ++cnt[y] ;
	}

	///

	root[0] = &sam[tot++] ;
	root[0]->len = 0 ; root[0]->link = NULL ;

	for (int i = 1 ; i <= n ; ++i) if (cnt[i] == 1) bfs(i) ;

	///

	ll ans = 0 ;
	for (int i = 1 ; i < tot ; ++i) {
		Node *p = &sam[i] ;
		ans += p->len - p->link->len ;
	}

	printf("%lld\n" , ans) ;

	return 0 ;
}