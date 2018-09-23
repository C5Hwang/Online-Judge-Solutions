#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 1e4 + 10 ;

struct Node {
	bool flip ;
	Node *ch[2] , *fa ;

	int getson() {return fa->ch[1] == this ;}
	bool isroot() {
		if (!fa) return 1 ;
		return fa->ch[0] != this && fa->ch[1] != this ;
	}
	void reverse() {
		flip ^= 1 ;
		std::swap(ch[0] , ch[1]) ;
	}
	void down() {
		if (!flip) return ;
		for (int i = 0 ; i < 2 ; ++i)
			if (ch[i]) ch[i]->reverse() ;
		flip = 0 ;
	}
	void connect(Node *p , int d) {
		ch[d] = p ;
		if (p) p->fa = this ;
	}
}lct[MAX_N] , *tmp[MAX_N] , *pt[MAX_N] ;

int n , m ;

void rotate(Node *p , int d) {
	Node *q = p->fa ;
	if (!q->isroot()) q->fa->connect(p , q->getson()) ;
	else p->fa = q->fa ;

	q->connect(p->ch[d] , d^1) ;
	p->connect(q , d) ;
}

void splay(Node *p) {
	int tot = 0 ; Node *t = p ;
	for (; !t->isroot() ; t = t->fa) tmp[tot++] = t ;
	tmp[tot++] = t ; for (; tot ;) tmp[--tot]->down() ;

	for (; !p->isroot() ;) {
		int sp = p->getson() , sq ;
		Node *q = p->fa ;

		if (!q->isroot()) {
			sq = q->getson() ;
			if (sp^sq) rotate(p , sp^1) , sp ^= 1 ;
			else rotate(q , sq^1) ;
		}

		rotate(p , sp^1) ;
	}
}

void access(int x) {
	Node *p = pt[x] , *q = NULL ;
	for (; p ;) {
		splay(p) ;
		p->ch[1] = q ;
		q = p ; p = p->fa ;
	}
}

void makeroot(int x) {
	Node *p = pt[x] ;
	access(x) ; splay(p) ;
	p->reverse() ;
}

int findroot(int x) {
	Node *p = pt[x] ;
	access(x) ; splay(p) ;
	for (; p->ch[0] ; p = p->ch[0]) ;

	return p - &lct[0] ;
}

void link(int x , int y) {
	Node *p = pt[x] , *q = pt[y] ;
	makeroot(y) ; q->fa = p ;
}

void cut(int x , int y) {
	Node *p = pt[x] , *q = pt[y] ;
	makeroot(x) ; access(y) ; splay(p) ;
	p->ch[1] = q->fa = NULL ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 1 ; i <= n ; ++i) pt[i] = &lct[i] ;

	for (int i = 0 ; i < m ; ++i) {
		char op[10] ; int x , y ;
		scanf("%s %d %d" , op , &x , &y) ;

		if (op[0] == 'Q') {
			int fx = findroot(x) , fy = findroot(y) ;

			if (fx == fy) printf("Yes\n") ;
			else printf("No\n") ;
		}
		else if (op[0] == 'C') link(x , y) ;
		else cut(x , y) ;
	}

	return 0 ;
}
