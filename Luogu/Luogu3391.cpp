#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 1e5 + 10 ;

struct Node {
	bool flip ;
	int num , siz ;
	Node *ch[2] , *fa ;

	int getson() {return fa->ch[1] == this ;}
	int getrank() {return ch[0] ? ch[0]->siz + 1 : 1 ;}
	void init() {flip = 0 ; num = siz = 0 ; ch[0] = ch[1] = fa = NULL ;}
	void update() {
		siz = 1 ;
		for (int i = 0 ; i < 2 ; ++i) siz += ch[i] ? ch[i]->siz : 0 ;
	}
	void connect(Node *p , int d) {
		ch[d] = p ;
		if (p) p->fa = this ;
	}
	void down() {
		if (!flip) return ;
		for (int i = 0 ; i < 2 ; ++i) if (ch[i]) ch[i]->reverse() ;
		flip = 0 ;
	}
	void reverse() {
		flip ^= 1 ;
		std::swap(ch[0] , ch[1]) ;
	}
}sp[MAX_N] ;

Node *root ;
int n , m , cur ;

Node *build(int x , int y) {
	if (x > y) return NULL ;

	int mid = (x + y) >> 1 ;
	Node *rt = &sp[cur++] ;
	rt->init() ; rt->num = mid ;

	rt->ch[0] = build(x , mid - 1) ; rt->ch[1] = build(mid + 1 , y) ;
	if (rt->ch[0]) rt->ch[0]->fa = rt ;
	if (rt->ch[1]) rt->ch[1]->fa = rt ;

	rt->update() ;

	return rt ;
}

Node *find(Node *rt , int k) {
	rt->down() ;
	int r = rt->getrank() ;

	if (r == k) return rt ;
	else if (r < k) return find(rt->ch[1] , k - r) ;
	else return find(rt->ch[0] , k) ;
}

void rotate(Node *p , int d) {
	Node *q = p->fa ;
	if (q->fa) q->fa->connect(p , q->getson()) ;
	else p->fa = NULL , root = p ;

	q->connect(p->ch[d] , d^1) ;
	p->connect(q , d) ;
	q->update() ;
}

void splay(Node *p , Node *&rt) {
	while (p != rt) {
		Node *q = p->fa ;
		int sp = p->getson() , sq ;

		if (q != rt) {
			sq = q->getson() ;
			if (sp^sq) rotate(p , sp^1) , sp ^= 1 ;
			else rotate(q , sq^1) ;
		}

		rotate(p , sp^1) ;
	}
	p->update() ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	root = build(0 , n + 1) ;

	///

	for (int i = 0 ; i < m ; ++i) {
		int x , y ; scanf("%d %d" , &x , &y) ;
		Node *p = find(root , x) , *q = find(root , y + 2) ;
		splay(p , root) ; splay(q , root->ch[1]) ;

		root->ch[1]->ch[0]->reverse() ;
	}

	for (int i = 2 ; i <= n + 1 ; ++i)
		printf("%d " , find(root , i)->num) ;
	printf("\n") ;

	return 0 ;
}
