#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 5e4 + 10 , INF = 0x7FFFFFFF ;

struct Node {
	bool flip ;
	int num , mnum , lazy , s ;
	Node *ch[2] , *fa ;

	int getson() {return fa->ch[1] == this ;}
	int getrank() {return ch[0] ? ch[0]->s + 1 : 1 ;}
	void init() {flip = 0 ; mnum = num = lazy = s = 0 ; ch[0] = ch[1] = fa = NULL ;}
	void connect(Node *p , int d) {
		ch[d] = p ;
		if (p) p->fa = this ;
	}
	void update() {
		s = 1 ; mnum = num ;
		for (int i = 0 ; i < 2 ; ++i)
			if (ch[i]) mnum = std::max(mnum , ch[i]->mnum) , s += ch[i]->s ;
	}
	void down() {
		if (flip) {
			std::swap(ch[0] , ch[1]) ;
			for (int i = 0 ; i < 2 ; ++i) if (ch[i]) ch[i]->flip ^= 1 ;
			flip = 0 ;
		}

		for (int i = 0 ; i < 2 ; ++i)
			if (ch[i]) ch[i]->num += lazy , ch[i]->mnum += lazy , ch[i]->lazy += lazy ;
		lazy = 0 ;
	}
}sp[MAX_N] ;

Node *root ;
int n , m , cur ;

Node *build(int x , int y) {
	if (x > y) return NULL ;

	int mid = (x + y) >> 1 ;
	Node *rt = &sp[cur++] ;
	rt->init() ;

	rt->ch[0] = build(x , mid - 1) ;
	rt->ch[1] = build(mid + 1 , y) ;

	if (rt->ch[0]) rt->ch[0]->fa = rt ;
	if (rt->ch[1]) rt->ch[1]->fa = rt ;
	rt->update() ;

	return rt ;
}

Node *find(Node *rt , int f) {
	rt->down() ;
	int r = rt->getrank() ;

	if (r == f) return rt ;
	else if (r > f) return find(rt->ch[0] , f) ;
	else return find(rt->ch[1] , f - r) ;
}

void rotate(Node *p , int d) {
	Node *q = p->fa ;
	if (q->fa) q->fa->connect(p , q->getson()) ;
	else root = p , p->fa = NULL ;

	q->connect(p->ch[d] , d^1) ;
	p->connect(q , d) ;
	q->update() ;
}

void splay(Node *p , Node *&rt) {
	while (p != rt) {
		int np = p->getson() , nq ;
		Node *q = p->fa ;

		if (q != rt) {
			nq = q->getson() ;

			if (np ^ nq) rotate(p , np^1) , np ^= 1 ;
			else rotate(q , nq^1) ;
		}

		rotate(p , np^1) ;
	}

	p->update() ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	root = build(0 , n + 1) ;
	for (int i = 0 ; i < m ; ++i) {
		int ty , x , y , a ;
		scanf("%d" , &ty) ;
		if (ty > 1) scanf("%d %d" , &x , &y) ;
		else scanf("%d %d %d" , &x , &y , &a) ;

		Node *p1 = find(root , x) , *p2 = find(root , y + 2) ;
		splay(p1 , root) ; splay(p2 , root->ch[1]) ;

		if (ty == 1) {
			root->ch[1]->ch[0]->num += a ;
			root->ch[1]->ch[0]->mnum += a ;
			root->ch[1]->ch[0]->lazy += a ;
		}
		else if (ty == 2) root->ch[1]->ch[0]->flip ^= 1 ;
		else printf("%d\n" , root->ch[1]->ch[0]->mnum) ;
	}

	return 0 ;
}
