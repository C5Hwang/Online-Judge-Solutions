#include <stdio.h>
#include <stdlib.h>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 ;

struct Node {
	int num , siz , r ;
	Node *ch[2] ;

	int getrank() {return ch[0] ? ch[0]->siz + 1 : 1 ;}
	void init(int a) {num = a ; siz = 1 ; r = 0 ; ch[0] = ch[1] = NULL ;}
	void update() {
		siz = 1 ;
		for (int i = 0 ; i < 2 ; ++i) siz += ch[i] ? ch[i]->siz : 0 ;
	}
}list[MAX_N] ;

Node *root ;
int n , cur ;

void rotate(Node *&rt , int d) {
	Node *son = rt->ch[d^1] ;

	rt->ch[d^1] = son->ch[d] ; son->ch[d] = rt ;
	rt->update() ; son->update() ; rt = son ;
}

void ins(Node *&rt , int a) {
	if (!rt) {
		rt = &list[cur++] ;
		rt->init(a) ; rt->r = rand() ;

		return ;
	}

	int d = rt->num > a ? 0 : 1 ;
	ins(rt->ch[d] , a) ; rt->update() ;

	if (rt->ch[d]->r > rt->r) rotate(rt , d^1) ;
}

void del(Node *&rt , int a) {
	if (rt->num == a) {
		if (!rt->ch[0]) rt = rt->ch[1] ;
		else if (!rt->ch[1]) rt = rt->ch[0] ;
		else {
			int d = rt->ch[0]->r > rt->ch[1]->r ? 0 : 1 ;
			rotate(rt , d^1) ; del(rt->ch[d^1] , a) ;
		}

		if (rt) rt->update() ;

		return ;
	}

	int d = rt->num > a ? 0 : 1 ;
	del(rt->ch[d] , a) ; rt->update() ;
}

int findrank(Node *rt , int a) {
	if (!rt) return 0 ;

	int r = rt->getrank() ;
	if (rt->num > a) return findrank(rt->ch[0] , a) ;
	else return findrank(rt->ch[1] , a) + r ;
}

int findnum(Node *rt , int k) {
	int r = rt->getrank() ;

	if (r == k) return rt->num ;
	else if (r < k) return findnum(rt->ch[1] , k - r) ;
	else return findnum(rt->ch[0] , k) ;
}

int main() {
	scanf("%d" , &n) ;
	for (int i = 0 ; i < n ; ++i) {
		int op , a ;
		scanf("%d %d" , &op , &a) ;

		if (op == 1) ins(root , a) ;
		else if (op == 2) del(root , a) ;
		else if (op == 3) printf("%d\n" , findrank(root , a - 1) + 1) ;
		else if (op == 4) printf("%d\n", findnum(root , a)) ;
		else if (op == 5) printf("%d\n" , findnum(root , findrank(root , a - 1))) ;
		else printf("%d\n" , findnum(root , findrank(root , a) + 1)) ;
	}

	return 0 ;
}