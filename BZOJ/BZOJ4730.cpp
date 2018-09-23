#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 , L = 19 ;

struct Node {
	Node *ch[2] ;
	int lazy , sum ;

	void init() {lazy = sum = 0 ; ch[0] = ch[1] = NULL ;}
	void update() {
		sum = 0 ;
		for (int i = 0 ; i < 2 ; ++i) if (ch[i]) sum += ch[i]->sum ;
	}
	void down(int dep) {
		if (lazy & (1 << dep)) std::swap(ch[0] , ch[1]) ;

		for (int i = 0 ; i < 2 ; ++i) if (ch[i]) ch[i]->lazy ^= lazy ;
		lazy = 0 ;
	}
}tri[MAX_N * L] ;

struct Link {
	int num ;
	Link *next ;
}list[MAX_N << 1] ;

///

bool ap[MAX_N] ;
Node *root[MAX_N] ;
Link *head[MAX_N] ;
int T , n , m , cur , tot , sg[MAX_N] ;

///

void add(Node *&rt , int dep , int x) {
	if (!rt) {rt = &tri[tot++] ;rt->init() ;}
	if (dep < 0) {rt->sum = 1 ;return ;}

	rt->down(dep) ;

	int d = x & (1 << dep) ? 1 : 0 ;
	add(rt->ch[d] , dep - 1 , x) ;
	rt->update() ;
}

int find(Node *rt , int dep) {
	if (!rt) return 0 ;

	rt->down(dep) ;

	int hf = 1 << dep ;
	if (!rt->ch[0] || rt->ch[0]->sum < hf) return find(rt->ch[0] , dep - 1) ;
	else return (1 << dep) + find(rt->ch[1] , dep - 1) ;
}

void xor_all(Node *rt , int x) {
	rt->lazy ^= x ;
}

void merge(Node *&r1 , Node *r2 , int dep) {
	if (dep < 0) return ;

	if (!r2) return ;
	else if (!r1) r1 = r2 ;
	else {
		r1->down(dep) ; r2->down(dep) ;
		merge(r1->ch[0] , r2->ch[0] , dep - 1) ;
		merge(r1->ch[1] , r2->ch[1] , dep - 1) ;

		r1->update() ;
	}
}

void getsg(int x , int fa) {
	ap[x] = 1 ;

	int totsg = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa) continue ;

		getsg(nx , x) ; totsg ^= sg[nx] ;
	}

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa) continue ;

		xor_all(root[nx] , totsg ^ sg[nx]) ;
		merge(root[x] , root[nx] , L) ;
	}

	add(root[x] , L , totsg) ;
	sg[x] = find(root[x] , L) ;
}

///

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

void init() {
	cur = tot = 0 ;
	memset(ap , 0 , sizeof(ap)) ;
	memset(root , 0 , sizeof(root)) ;
	memset(head , 0 , sizeof(head)) ;
}

///

int main() {
	scanf("%d" , &T) ;
	for (; T-- ;) {
		init() ;

		scanf("%d %d" , &n , &m) ;
		for (int i = 0 ; i < m ; ++i) {
			int x , y ;
			scanf("%d %d" , &x , &y) ;
			ins(x , y) ; ins(y , x) ;
		}

		int totsg = 0 ;
		for (int i = 1 ; i <= n ; ++i)
			if (!ap[i]) {getsg(i , -1) ; totsg ^= sg[i] ;}

		if (totsg) printf("Alice\n") ;
		else printf("Bob\n") ;
	}

	return 0 ;
}