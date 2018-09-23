#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define uint unsigned int

const int MAX_N = 1e5 + 10 , mod = 51061 ;

struct Node {
	bool flip ;
	uint num , sum , siz , ad , ti ;
	Node *ch[2] , *fa ;

	int getson() {return fa->ch[1] == this ;}
	bool isroot() {
		if (!fa) return 1 ;
		return fa->ch[0] != this && fa->ch[1] != this ;
	}
	void init() {flip = 0 ; num = ad = 0 ; siz = ti = sum = 1 ; ch[0] = ch[1] = fa = NULL ;}
	void add(uint c) {
		c %= mod ;
		ad = (ad + c) % mod ;
		num = (num + c) % mod ; sum = (sum + c * siz) % mod ;
	}
	void times(uint c) {
		c %= mod ;
		ti = (ti * c) % mod ; ad = (ad * c) % mod ;
		num = (num * c) % mod ; sum = (sum * c) % mod ;
	}
	void reverse() {
		flip ^= 1 ;
		std::swap(ch[0] , ch[1]) ;
	}
	void connect(Node *p , int d) {
		ch[d] = p ;
		if (p) p->fa = this ;
	}
	void update() {
		siz = 1 ; sum = num ;
		for (int i = 0 ; i < 2 ; ++i)
			if (ch[i]) siz += ch[i]->siz , sum = (sum + ch[i]->sum) % mod ;
	}
	void down() {
		for (int i = 0 ; i < 2 ; ++i) {
			if (!ch[i]) continue ;
			if (flip) ch[i]->reverse() ;
			ch[i]->times(ti) ; ch[i]->add(ad) ;
		}
		flip = 0 ; ad = 0 ; ti = 1 ;
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
	int tot = 0 ; Node *t = p ;
	for (; !t->isroot() ; t = t->fa) tmp[tot++] = t ;
	tmp[tot++] = t ; for (; tot ;) tmp[--tot]->down() ;

	while (!p->isroot()) {
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
	access(x) ; splay(pt[x]) ;
	pt[x]->reverse() ;
}

void link(int x , int y) {
	Node *p = pt[x] , *q = pt[y] ;
	makeroot(x) ; p->fa = q ;
}

void cut(int x , int y) {
	Node *p = pt[x] , *q = pt[y] ;
	makeroot(x) ; access(y) ; splay(p) ;
	p->ch[1] = q->fa = NULL ; p->update() ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 1 ; i <= n ; ++i) {
		pt[i] = &lct[i] ;
	   	pt[i]->init() ; pt[i]->num = 1 ;
	}
	for (int i = 1 ; i < n ; ++i) {
		int x , y ;
		scanf("%d %d" , &x , &y) ;
		link(x , y) ;
	}

	///
	
	for (int i = 0 ; i < m ; ++i) {
		char op ; int u1 , v1 , u2 , v2 ; uint c ;

		scanf(" %c" , &op) ;
		if (op == '+') {
			scanf("%d %d %d" , &u1 , &v1 , &c) ; c %= mod ;

			Node *p = pt[u1] , *q = pt[v1] ;
			makeroot(u1) ; access(v1) ; splay(q) ;

			q->add(c) ;
		}
		else if (op == '-') {
			scanf("%d %d %d %d" , &u1 , &v1 , &u2 , &v2) ;

			cut(u1 , v1) ; link(u2 , v2) ;
		}
		else if (op == '*') {
			scanf("%d %d %d" , &u1 , &v1 , &c) ; c %= mod ;

			Node *p = pt[u1] , *q = pt[v1] ;
			makeroot(u1) ; access(v1) ; splay(q) ;

			q->times(c) ;
		}
		else {
			scanf("%d %d" , &u1 , &v1) ;

			Node *p = pt[u1] , *q = pt[v1] ;
			makeroot(u1) ; access(v1) ; splay(q) ;

			printf("%d\n" , q->sum) ;
		}
	}

	return 0 ;
}
