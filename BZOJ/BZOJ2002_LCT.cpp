#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 2e5 + 10 ;

struct Node {
	int siz ;
	bool flip ;
	Node *ch[2] , *fa ;

	int getson() {return fa->ch[1] == this ;}
	bool isroot() {
		if (!fa) return 1 ;
		return fa->ch[0] != this && fa->ch[1] != this ;
	}
	void init() {siz = 1 ; flip = 0 ; ch[0] = ch[1] = fa = NULL ;}
	void reverse() {
		flip ^= 1 ;
		std::swap(ch[0] , ch[1]) ;
	}
	void down() {
		if (!flip) return ;
		for (int i = 0 ; i < 2 ; ++i) if (ch[i]) ch[i]->reverse() ;
		flip = 0 ;
	}
	void update() {
		siz = 1 ;
		for (int i = 0 ; i < 2 ; ++i) siz += ch[i] ? ch[i]->siz : 0 ;
	}
	void connect(Node *p , int d) {
		ch[d] = p ;
		if (p) p->fa = this ;
	}
}lct[MAX_N] , *tmp[MAX_N] , *pt[MAX_N] ;

int n , m , a[MAX_N] ;

void rotate(Node *p , int d) {
	Node *q = p->fa ;
	if (!q->isroot()) q->fa->connect(p , q->getson()) ;
	else p->fa = q->fa ;

	q->connect(p->ch[d] , d^1) ;
	p->connect(q , d) ;
	q->update() ;
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
	access(x) ; splay(q) ;
	q->ch[1] = p->fa = NULL ;
	q->update() ;
}

int main() {
	scanf("%d" , &n) ;
	for (int i = 0 ; i < n ; ++i) (pt[i] = &lct[i])->init() ;
	for (int i = 0 ; i < n ; ++i) {
		scanf("%d" , &a[i]) ;
		if (a[i] + i < n) link(i , a[i] + i) ;
	}

	scanf("%d" , &m) ;
	for (int i = 0 ; i < m ; ++i) {
		int op , x , k ;
		scanf("%d %d" , &op , &x) ;
		if (op == 2) scanf("%d" , &k) ;

		if (op == 1) {
			access(x) ; splay(pt[x]) ;
			printf("%d\n" , pt[x]->siz) ;
		}
		else {
			int of = x + a[x] , nf = x + k ;
			if (of < n) cut(x , of) ;
			if (nf < n) link(x , nf) ;

			a[x] = k ;
		}
	}

	return 0 ;
}
