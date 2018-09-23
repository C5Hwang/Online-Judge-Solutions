#include <stack>
#include <stdio.h>
#include <stdlib.h>

const int MAX_N = 5e5 + 10 , INF = 1e3 + 10 ;

struct Node {
	bool flip ;
	Node *ch[2] , *fa ;
	int num , ls , rs , ms , siz , sum , lazy ;

	int getson() {return fa->ch[1] == this ;}
	int getrank() {return ch[0] ? ch[0]->siz + 1 : 1 ;}
	void connect(Node *p , int d) {
		ch[d] = p ;
		if (p) p->fa = this ;
	}
	void init() {
		flip = 0 ;
		lazy = INF ;
		ch[0] = ch[1] = fa = NULL ;
		num = ls = rs = ms = siz = sum = 0 ;
	}
	void change(int x) {
		lazy = x ; sum = siz * x ; num = x ;
		if (x >= 0) ls = rs = ms = sum ;
		else ls = rs = ms = x ;
	}
	void reverse() {
		std::swap(ch[0] , ch[1]) ;
		std::swap(ls , rs) ;
		flip ^= 1 ;
	}
	void down() {
		if (flip) {
			for (int i = 0 ; i < 2 ; ++i)
				if (ch[i]) ch[i]->reverse() ;
			flip = 0 ;
		}
		if (lazy < INF) {
			for (int i = 0 ; i < 2 ; ++i)
				if (ch[i]) ch[i]->change(lazy) ;
			lazy = INF ;
		}
	}
	void update() {
		sum = num ; siz = 1 ;
		for (int i = 0 ; i < 2 ; ++i) {
			sum += ch[i] ? ch[i]->sum : 0 ;
			siz += ch[i] ? ch[i]->siz : 0 ;
		}

		if (!ch[0] && !ch[1]) ls = rs = ms = num ;
		else if (!ch[0]) {
			ls = std::max(num , ch[1]->ls + num) ;
			rs = std::max(ch[1]->rs , num + ch[1]->sum) ;

			ms = std::max(std::max(ls , rs) , ch[1]->ms) ;
		}
		else if (!ch[1]) {
			ls = std::max(ch[0]->ls , num + ch[0]->sum) ;
			rs = std::max(num , ch[0]->rs + num) ;

			ms = std::max(std::max(ls , rs) , ch[0]->ms) ;
		}
		else {
			ls = std::max(ch[0]->ls , ch[0]->sum + num + std::max(ch[1]->ls , 0)) ;
			rs = std::max(ch[1]->rs , ch[1]->sum + num + std::max(ch[0]->rs , 0)) ;

			int lp = std::max(ch[0]->rs , 0) , rp = std::max(ch[1]->ls , 0) ;
			ms = std::max(std::max(std::max(ch[0]->ms , ch[1]->ms) , std::max(ls , rs)) , lp + rp + num) ;
		}
	}
}sp[MAX_N] ;

std::stack<int> sta ;

Node *root ;
int n , m , a[MAX_N] ;

void collect(Node *rt) {
	if (!rt) return ;

	int p = rt - &sp[0] ;
	sta.push(p) ;

	collect(rt->ch[0]) ; collect(rt->ch[1]) ;
}

Node *build(int x , int y) {
	if (x > y) return NULL ;

	int mid = (x + y) >> 1 ;
	Node *rt = &sp[sta.top()] ; rt->init() ; sta.pop() ;
	rt->num = a[mid] ;

	rt->ch[0] = build(x , mid - 1) ;
	rt->ch[1] = build(mid + 1 , y) ;

	if (rt->ch[0]) rt->ch[0]->fa = rt ;
	if (rt->ch[1]) rt->ch[1]->fa = rt ;
	rt->update() ;

	return rt ;
}

void rotate(Node *p , int d) {
	Node *q = p->fa ;
	if (q->fa) q->fa->connect(p , q->getson()) ;
	else root = p , p->fa = NULL ;

	q->connect(p->ch[d] , d^1) ;
	p->connect(q , d) ;
	q->update() ;
}

Node *find(Node *rt , int f) {
	rt->down() ;
	int r = rt->getrank() ;

	if (r == f) return rt ;
	else if (r < f) return find(rt->ch[1] , f - r) ;
	else return find(rt->ch[0] , f) ;
}

void splay(Node *p , Node *&rt) {
	while (p != rt) {
		int sp = p->getson() , sq ;
		Node *q = p->fa ;

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
	for (int i = 5e5 - 1 ; i >= 0 ; --i) sta.push(i) ;
	for (int i = 1 ; i <= n ; ++i) scanf("%d" , &a[i]) ;

	///
	
	root = build(0 , n + 1) ;
	for (int i = 0 ; i < m ; ++i) {
		char oper[20] ; int x , y , L , c ;
		scanf("%s" , oper) ;
		if (oper[0] != 'M' || (oper[0] == 'M' && oper[2] != 'X'))
			scanf("%d %d" , &x , &L) ;

		///

		if (oper[0] == 'I') {
			for (int i = 1 ; i <= L ; ++i) scanf("%d" , &a[i]) ;

			Node *tmp = build(1 , L) , *p1 = find(root , x + 1) , *p2 = find(root , x + 2) ;
			splay(p1 , root) ; splay(p2 , root->ch[1]) ;

			root->ch[1]->connect(tmp , 0) ;
			root->ch[1]->update() ; root->update() ;
		}
		else if (oper[0] == 'D') {
			y = x + L - 1 ;

			Node *p1 = find(root , x) , *p2 = find(root , y + 2) ;
			splay(p1 , root) ; splay(p2 , root->ch[1]) ;
			collect(root->ch[1]->ch[0]) ;
			
			root->ch[1]->ch[0] = NULL ;
			root->ch[1]->update() ; root->update() ;
		}
		else if (oper[0] == 'M' && oper[2] == 'K') {
			scanf("%d" , &c) ; y = x + L - 1 ;

			Node *p1 = find(root , x) , *p2 = find(root , y + 2) ;
			splay(p1 , root) ; splay(p2 , root->ch[1]) ;
			
			root->ch[1]->ch[0]->change(c) ;
			root->ch[1]->update() ; root->update() ;
		}
		else if (oper[0] == 'R') {
			y = x + L - 1 ;

			Node *p1 = find(root , x) , *p2 = find(root , y + 2) ;
			splay(p1 , root) ; splay(p2 , root->ch[1]) ;

			root->ch[1]->ch[0]->reverse() ;
		}
		else if (oper[0] == 'G') {
			y = x + L - 1 ;

			if (x > y) {
				printf("0\n") ;
				continue ;
			}
			Node *p1 = find(root , x) , *p2 = find(root , y + 2) ;
			splay(p1 , root) ; splay(p2 , root->ch[1]) ;
			printf("%d\n" , root->ch[1]->ch[0]->sum) ;
		}
		else {
			Node *p1 = find(root , 1) , *p2 = find(root , root->siz) ;
			splay(p1 , root) ; splay(p2 , root->ch[1]) ;

			printf("%d\n" , root->ch[1]->ch[0]->ms) ;
		}
	}

	return 0 ;
}
