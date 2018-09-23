#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 3e5 + 10 ;

struct Node {
	bool flip ;
	int num , xsum , siz ;
	Node *ch[2] , *fa ;

	int getson() {return fa->ch[1] == this ;}
	bool isroot() {
		if (!fa) return 1 ;
		return fa->ch[0] != this && fa->ch[1] != this ;
	}
	void init() {flip = 0 ; num = xsum = siz = 0 ; ch[0] = ch[1] = fa = NULL ;}
	void reverse() {
		flip ^= 1 ;
		std::swap(ch[0] , ch[1]) ;
	}
	void connect(Node *p , int d) {
		ch[d] = p ;
		if (p) p->fa = this ;
	}
	void update() {
		xsum = num ; siz = 1 ;
		for (int i = 0 ; i < 2 ; ++i) if (ch[i]) xsum ^= ch[i]->xsum , siz += ch[i]->siz ;
	}
	void down() {
		if (!flip) return ;
		for (int i = 0 ; i < 2 ; ++i) if (ch[i]) ch[i]->reverse() ;
		flip = 0 ;
	}
}lct[MAX_N] , *pt[MAX_N] , *tmp[MAX_N] ;

int n , m ;

void rotate(Node *p , int d) {
	Node *q = p->fa ;
	if (q->isroot()) p->fa = q->fa ;
	else q->fa->connect(p , q->getson()) ;

	q->connect(p->ch[d] , d^1) ;
	p->connect(q , d) ;
	q->update() ;
}

void splay(Node *p) {
	Node *t = p ; int o = 0 ;
	for (; !t->isroot() ; t = t->fa) tmp[o++] = t ;
	tmp[o++] = t ; for (; o ; tmp[--o]->down()) ;

	for (; !p->isroot() ;) {
		Node *q = p->fa ;
		int sp = p->getson() , sq ;

		if (!q->isroot()) {
			sq = q->getson() ;

			if (sp^sq) rotate(p , sp^1) , sp ^= 1 ;
			else rotate(q , sq^1) ;
		}
		rotate(p , sp^1) ;
	}
	p->update() ;
}

void access(int x) {
	Node *p = pt[x] , *q = NULL ;
	for (; p ;) {
		splay(p) ;
		p->ch[1] = q ; p->update() ;
		q = p ; p = p->fa ;
	}
}

void makeroot(int x) {
	Node *p = pt[x] ;
	access(x) ; splay(p) ;
	p->reverse() ;
}

void link(int x , int y) {
	Node *p = pt[x] , *q = pt[y] ;
	makeroot(x) ; p->fa = q ;
}

void cut(int x , int y) {
	Node *p = pt[x] , *q = pt[y] ;
	makeroot(x) ; access(y) ; splay(q) ;
	if (q->siz != 2) return ;
	q->ch[0] = p->fa = NULL ; q->update() ;
}

int findset(int x) {
	Node *p = pt[x] ;
	access(x) ; splay(p) ;
	for (; p->ch[0] ; p = p->ch[0]) ;

	return p - &lct[0] ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 1 ; i <= n ; ++i) {
		pt[i] = &lct[i] ; pt[i]->init() ;
		scanf("%d" , &pt[i]->num) ;
		pt[i]->xsum = pt[i]->num ; pt[i]->siz = 1 ;
	}

	///

	for (int i = 0 ; i < m ; ++i) {
		int op , x , y ;
		scanf("%d %d %d" , &op , &x , &y) ;

		if (!op) {
			Node *p = pt[y] ;
			makeroot(x) ; access(y) ; splay(p) ;
			printf("%d\n" , p->xsum) ;
		}
		else if (op == 1) {
			int fx = findset(x) , fy = findset(y) ;
			if (fx != fy) link(x , y) ;
		}
		else if (op == 2) {
			int fx = findset(x) , fy = findset(y) ;
			if (fx == fy) cut(x , y) ;
		}
		else {
			Node *p = pt[x] ;
			access(x) ; splay(p) ;
			p->xsum ^= (p->num ^ y) ; p->num = y ;
		}
	}

	return 0 ;
}
