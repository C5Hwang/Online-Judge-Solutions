#include <queue>
#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 , MAX_T = 4e6 + 10 ;

struct Node {
	int len ;
	Node *ch[10] , *fail ;
}sam[MAX_T] ;
struct Link {
	int num ;
	Link *next ;
}list[MAX_N << 1] ;

std::queue<int> que ;

bool vis[MAX_N] ;
Link *head[MAX_N] ;
Node *root[MAX_N] ;
int n , C , tot , cur , a[MAX_N] , d[MAX_N] ;

Node *extend(Node *last , int c) {
	Node *p = last ;
	if (p->ch[c]) {
		Node *q = p->ch[c] ;
		if (p->len + 1 == q->len) return q ;
		else {
			Node *cur = &sam[tot++] ;
			*cur = *q ; cur->len = p->len + 1 ;

			for (; p && p->ch[c] == q ; p = p->fail) p->ch[c] = cur ;
			q->fail = cur ;

			return cur ;
		}
	}

	///

	Node *cur = &sam[tot++] ;
	cur->len = last->len + 1 ;

	for (; p && !p->ch[c] ; p = p->fail) p->ch[c] = cur ;
	if (!p) cur->fail = &sam[0] ;
	else {
		Node *q = p->ch[c] ;
		if (p->len + 1 == q->len) cur->fail = q ;
		else {
			Node *clone = &sam[tot++] ;
			*clone = *q ; clone->len = p->len + 1 ;

			for (; p && p->ch[c] == q ; p = p->fail) p->ch[c] = clone ;
			q->fail	 = cur->fail = clone ;
		}
	}

	return cur ;
}

void bfs(int x) {
	for (int i = 1 ; i <= n ; ++i) vis[i] = 0 ;
	vis[x] = 1 ; que.push(x) ;

	root[x] = extend(&sam[0] , a[x]) ;
	for (; !que.empty() ;) {
		int x = que.front() ; que.pop() ;

		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (vis[nx]) continue ;

			root[nx] = extend(root[x] , a[nx]) ;
			que.push(nx) ; vis[nx] = 1 ;
		}
	}
}

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

int main() {
	scanf("%d %d" , &n , &C) ;
	for (int i = 1 ; i <= n ; ++i) scanf("%d" , &a[i]) ;
	for (int i = 1 ; i < n ; ++i) {
		int x , y ; scanf("%d %d" , &x , &y) ;
		ins(x , y) ; ins(y , x) ; ++d[x] ; ++d[y] ;
	}

	///

	tot = 1 ;
	for (int i = 1 ; i <= n ; ++i) if (d[i] == 1) bfs(i) ;

	ll ans = 0 ;
	for (int i = 1 ; i < tot ; ++i) ans += sam[i].len - sam[i].fail->len ;
	printf("%lld\n" , ans) ;

	return 0 ;
}