#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 1e5 + 10 , MAX_K = 20 + 5 , K = 17 ;

struct data {
	double ai[MAX_K] ;

	friend data operator +(data x , data y) {
		data ans ;
		for (int i = 0 ; i < K ; ++i) ans.ai[i] = x.ai[i] + y.ai[i] ;

		return ans ;
	}
	void init(int f , double a , double b) {
		if (f == 1) {
			double t1 = 1 , t2 = 1 ;
			for (int i = 0 ; i < K ; ++i , t1 *= a , t2 /= i) {
				double sj = i % 2 ? cos(b) : sin(b) ;
				int fh = (i % 4 == 2 || i % 4 == 3) ? -1 : 1 ;

				ai[i] = sj * fh * t1 * t2 ;
			}
		}
		else if (f == 2) {
			double t1 = 1 , t2 = 1 , eb = 0 ;
			for (int i = 0 ; i < 40 ; ++i , t1 *= b , t2 /= i) eb += t1 * t2 ;

			t1 = 1 ; t2 = 1 ;
			for (int i = 0 ; i < K ; ++i , t1 *= a , t2 /= i) ai[i] = t1 * t2 * eb ;
		}
		else {
			for (int i = 0 ; i < K ; ++i) ai[i] = 0 ;
			ai[0] = b ; ai[1] = a ;
		}
	}
	double getans(double x) {
		double ans = 0 , t = 1 ;
		for (int i = 0 ; i < K ; ++i , t *= x) ans += ai[i] * t ;

		return ans ;
	}
} ;

struct Node {
	bool flip ;
	data num , sum ;
	Node *fa , *ch[2] ;

	int getson() {return fa->ch[1] == this ;}
	bool isroot() {
		if (!fa) return 1 ;
		return fa->ch[0] != this && fa->ch[1] != this ;
	}
	void connect(Node *p , int d) {
		ch[d] = p ;
		if (p) p->fa = this ;
	}
	void update() {
		sum = num ;
		for (int i = 0 ; i < 2 ; ++i)
			if (ch[i]) sum = sum + ch[i]->sum ;
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
}lct[MAX_N] , *pt[MAX_N] , *tmp[MAX_N] ;

int n , m ;
char op[20] ;

void rotate(Node *p , int d) {
	Node *q = p->fa ;
	if (!q->isroot()) q->fa->connect(p , q->getson()) ;
	else p->fa = q->fa ;

	q->connect(p->ch[d] , d^1) ; p->connect(q , d) ;
	q->update() ;
}

void splay(Node *p) {
	int tot = 0 ; Node *t = p ;
	for (; !t->isroot() ; t = t->fa) tmp[tot++] = t ;
	tmp[tot++] = t ; for (; tot ;) tmp[--tot]->down() ;

	for (; !p->isroot() ;) {
		Node *q = p->fa ;
		int sp = p->getson() ;

		if (!q->isroot()) {
			int sq = q->getson() ;

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
	makeroot(x) ; access(y) ; splay(q) ;
	q->ch[0] = p->fa = NULL ;
	q->update() ;
}

int main() {
	scanf("%d %d %s" , &n , &m , op) ;
	for (int i = 0 ; i < n ; ++i) {
		int f ; double a , b ;
		scanf("%d %lf %lf" , &f , &a , &b) ;

		pt[i] = &lct[i] ;
		pt[i]->num.init(f , a , b) ; pt[i]->update() ;
	}

	///

	for (int i = 0 ; i < m ; ++i) {
		int u , v ; double a , b ;
		scanf("%s %d %d" , op , &u , &v) ;

		if (op[0] == 'm') scanf("%lf %lf" , &a , &b) ;
		else if (op[0] == 't') scanf("%lf" , &a) ;

		if (op[0] == 'a') link(u , v) ;
		else if (op[0] == 'd') cut(u , v) ;
		else if (op[0] == 'm') {
			Node *p = pt[u] ;
			splay(p) ;
			p->num.init(v , a , b) ; p->update() ;
		}
		else {
			int fx = findroot(u) , fy = findroot(v) ;
			if (fx != fy) {printf("unreachable\n") ; continue ;}

			Node *p = pt[u] , *q = pt[v] ;
			makeroot(u) ; access(v) ; splay(q) ;

			printf("%0.9lf\n" , q->sum.getans(a)) ;
		}
	}

	return 0 ;
}