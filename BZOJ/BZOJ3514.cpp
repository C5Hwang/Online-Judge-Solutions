#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 2e5 + 10 , MAX_L = 4e5 + 10 , lgN = 20 + 5 ;

struct Edge {
	int x , y ;
}eg[MAX_N] ;
struct Node {
	bool flip ;
	int num , minnum ;
	Node *ch[2] , *fa ;

	int getson() {return fa->ch[1] == this ;}
	bool isroot() {
		if (!fa) return 1 ;
		return fa->ch[0] != this && fa->ch[1] != this ;
	}
	void init(int a) {flip = 0 ; num = minnum = a ; ch[0] = ch[1] = fa = NULL ;}
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
	void update() {
		minnum = num ;
		for (int i = 0 ; i < 2 ; ++i)
			if (ch[i]) minnum = std::min(minnum , ch[i]->minnum) ;
	}
	void connect(Node *p , int d) {
		ch[d] = p ;
		if (p) p->fa = this ;
	}
}lct[MAX_L] , *pt[MAX_L] , *tmp[MAX_L] ;
struct Tree {
	int num ;
	Tree *left , *right ;
}ctree[MAX_N * lgN] , *root[MAX_N] ;

///

int n , m , k , deal , cur , ans , ntr[MAX_N] ;

///

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
	makeroot(x) ; access(y) ; splay(p) ;
	p->ch[1] = q->fa = NULL ; p->update() ;
}

int findroot(int x) {
	Node *p = pt[x] ;
	access(x) ; splay(p) ;
	for (; p->ch[0] ; p = p->ch[0]) ;

	return p - &lct[0] ;
}

void insert(int m , int x , int y) {
	if (x == y) {ntr[m] = m ; return ;}

	int fx = findroot(x) , fy = findroot(y) ;
	if (fx == fy) {
		makeroot(x) ; access(y) ; splay(pt[x]) ;
		int a = pt[x]->minnum ;

		ntr[m] = a ;
		Edge *p = &eg[a] ;
		cut(a + n , p->x) ; cut(a + n , p->y) ;
	}
	else ntr[m] = 0 ;

	link(m + n , x) ; link(m + n , y) ;
}

///

Tree *build(int x , int y) {
	Tree *rt = &ctree[cur++] ;
	rt->num = 0 ;
	
	if (x == y) return rt ;

	int mid = (x + y) >> 1 ;
	rt->left = build(x , mid) ;
	rt->right = build(mid + 1 , y) ;

	return rt ;
}

void change(Tree *ort , Tree *&rt , int x , int y , int f) {
	rt = &ctree[cur++] ;
	*rt = *ort ; ++rt->num ;

	if (x == y) return ;
	
	int mid = (x + y) >> 1 ;
	if (f <= mid) change(ort->left , rt->left , x , mid , f) ;
	else change(ort->right , rt->right , mid + 1 , y , f) ;
}

int getans(Tree *ort , Tree *rt , int x , int y , int fx , int fy) {
	if (y < fx || fy < x) return 0 ;
	if (fx <= x && y <= fy) return rt->num - ort->num ;

	int mid = (x + y) >> 1 ,
		s1 = getans(ort->left , rt->left , x , mid , fx , fy) ,
		s2 = getans(ort->right , rt->right , mid + 1 , y , fx , fy) ;

	return s1 + s2 ;
}

///

int main() {
	scanf("%d %d %d %d", &n , &m , &k , &deal) ;
	for (int i = 1 ; i <= n ; ++i) (pt[i] = &lct[i])->init(m + 1) ;
	for (int i = 1 ; i <= m ; ++i) (pt[i + n] = &lct[i + n])->init(i) ;

	///

	for (int i = 1 ; i <= m ; ++i) {
		int x , y ;
		scanf("%d %d" , &x , &y) ;
		insert(i , x , y) ; eg[i] = (Edge){x , y} ;
	}

	///
	
	root[0] = build(0 , m) ;
	for (int i = 1 ; i <= m ; ++i)
		change(root[i - 1] , root[i] , 0 , m , ntr[i]) ;

	ans = 0 ;
	for (int i = 0 ; i < k ; ++i) {
		int x , y ; scanf("%d %d" , &x , &y) ; x ^= ans ; y ^= ans ;

		ans = n - getans(root[x - 1] , root[y] , 0 , m , 0 , x - 1) ;
		printf("%d\n" , ans) ;

		if (!deal) ans = 0 ;
	}

	return 0 ;
}
