#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 3e4 + 10 ;

struct Node {
	bool flip ;
	int num , sum ;
	Node *ch[2] , *fa ;

	int getson() {return fa->ch[1] == this ;}
	bool isroot() {
		if (!fa) return 1 ;
		return fa->ch[0] != this && fa->ch[1] != this ;
	}
	void init(int x) {flip = 0 ; num = sum = x ; ch[0] = ch[1] = fa = NULL ;}
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
	void update() {
		sum = num ;
		for (int i = 0 ; i < 2 ; ++i) sum += ch[i] ? ch[i]->sum : 0 ;
	}
}lct[MAX_N] , *pt[MAX_N] , *tmp[MAX_N] ;

int n , m , a[MAX_N] ;

void rotate(Node *p , int d) {
	Node *q = p->fa ;
	if (q->isroot()) p->fa = q->fa ;
	else q->fa->connect(p , q->getson()) ;

	q->connect(p->ch[d] , d^1) ;
	p->connect(q , d) ;
	q->update() ;
}

void splay(Node *p) {
	int tot = 0 ; Node *t = p ;
	for (; !t->isroot() ; t = t->fa) tmp[tot++] = t ;
	tmp[tot++] = t ; for (; tot ;) tmp[--tot]->down() ;

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

int findroot(int x) {
	Node *p = pt[x] ;
	access(x) ; splay(p) ;
	for (; p->ch[0] ; p = p->ch[0]) ;

	return p - &lct[0] ;
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

int main() {
	scanf("%d" , &n) ;
	for (int i = 1 ; i <= n ; ++i) {
		scanf("%d" , &a[i]) ;
		pt[i] = &lct[i] ; pt[i]->init(a[i]) ;
	}

	scanf("%d" , &m) ;
	for (int i = 0 ; i < m ; ++i) {
		char op[20] ; int x , y ;
		scanf("%s %d %d" , op , &x , &y) ;

		if (op[0] == 'b') {
			int fx = findroot(x) , fy = findroot(y) ;
			if (fx == fy) printf("no\n") ;
			else {
				printf("yes\n") ;
				link(x , y) ;
			}
		}
		else if (op[0] == 'p') {
			access(x) ; splay(pt[x]) ;
			pt[x]->num = y ; pt[x]->sum += y - a[x] ;
			a[x] = y ;
		}
		else {
			int fx = findroot(x) , fy = findroot(y) ;

			if (fx == fy) {
				makeroot(x) ; access(y) ; splay(pt[y]) ;
				printf("%d\n" , pt[y]->sum) ;
			}
			else printf("impossible\n") ;
		}
	}

	return 0 ;
}
