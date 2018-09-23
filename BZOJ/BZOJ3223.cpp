#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 1e5 + 10 ;

struct Point {
	bool flip ;
	int num , s ;
	Point *ch[2] , *fa ;
	
	void init() {num = s = 0 ; flip = 0 ; ch[0] = ch[1] = fa = NULL ;}
	int getrank() {return ch[0] ? ch[0]->s + 1 : 1 ;}
	int getson() {return fa->ch[1] == this ;}
	void down() {
		if (!flip) return ;
		std::swap(ch[0] , ch[1]) ;
		for (int i = 0 ; i < 2 ; ++i) if (ch[i]) ch[i]->flip ^= 1 ;
		flip = 0 ;
	}
	void update() {
		s = 1 ;
		for (int i = 0 ; i < 2 ; ++i) s += ch[i] ? ch[i]->s : 0 ;
	}
	void connect(Point *p , int d) {
		this->ch[d] = p ;
		if (p) p->fa = this ;
	}
}sp[MAX_N] ;

Point *root ;
int n , m , cur ;

Point *build(int x , int y) {
	if (x > y) return NULL ;
	int mid = (x + y) >> 1 ;
	Point *rt = &sp[cur++] ;
	rt->init() ;

	rt->num = mid ;
	rt->ch[0] = build(x , mid - 1) ;
	rt->ch[1] = build(mid + 1 , y) ;

	if (rt->ch[0]) rt->ch[0]->fa = rt ;
	if (rt->ch[1]) rt->ch[1]->fa = rt ;

	rt->update() ;
	return rt ;
}

Point *find(Point *rt , int num) {
	rt->down() ;

	int r = rt->getrank() ;

	if (r == num) return rt ;
	else if (r < num) return find(rt->ch[1] , num - r) ;
	else return find(rt->ch[0] , num) ;
}

void rotate(Point *p , int d) {
	Point *q = p->fa ;
	if (q->fa) q->fa->connect(p , q->getson()) ;
	else root = p , p->fa = NULL ;

	q->connect(p->ch[d] , d^1) ;
	p->connect(q , d) ;
	q->update() ;
}

void splay(Point *p , Point *&rt) {
	while (p != rt) {
		int np = p->getson() , nq ;
		Point *q = p->fa ;

		if (q != rt) {
			nq = q->getson() ;

			if (np == nq) rotate(q , nq^1) ;
			else rotate(p , np^1) , np ^= 1 ;
		}

		rotate(p , np^1) ;
	}

	p->update() ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	root = build(0 , n + 1) ;
	
	///
	
	for (int i = 0 ; i < m ; ++i) {
		int x , y ; scanf("%d %d" , &x , &y) ;

		Point *L = find(root , x) , *R = find(root , y + 2) ;
		splay(L , root) ; splay(R , root->ch[1]) ;
		root->ch[1]->ch[0]->flip ^= 1 ;
	}

	for (int i = 2 ; i <= n + 1 ; ++i)
		printf("%d " , find(root , i)->num) ;

	return 0 ;
}
