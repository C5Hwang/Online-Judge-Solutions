#include <stdio.h>
#include <stdlib.h>

const int MAX_N = 50000 + 10 ;

struct Node {
	int num , r ;
	Node *ch[2] ;

	int cmp(int x) {
		if (x <= num) return 0 ;
		else return 1 ;
	}
}tre[MAX_N] ;

Node *root ;
int n , cur , len , a[MAX_N] , b[MAX_N] ;

void rotate(Node *&rt , int d) {
	Node *son = rt->ch[d^1] ;
	rt->ch[d^1] = son->ch[d] ; son->ch[d] = rt ; rt = son ;
}

bool ins(Node *&rt , int a) {
	if (!rt) {
		rt = &tre[cur++] ;
		rt->num = a ; rt->r = rand() ;
		rt->ch[0] = rt->ch[1] = NULL ;

		return 1 ;
	}
	if (rt->num == a) return 0 ;

	int d = rt->cmp(a) ;
	
	bool res = ins(rt->ch[d] , a) ;
	if (rt->ch[d]->r < rt->r) rotate(rt , d^1) ;
	
	return res ;
}

int main() {
	int Q ; scanf("%d" , &Q) ;
	while (Q--) {
		cur = 0 ; len = 0 ; root = NULL ;

		scanf("%d" , &n) ;
		for (int i = 0 ; i < n ; ++i)
			scanf("%d" , &a[i]) ;
		
		///

		for (int i = 0 ; i < n ; ++i) {
			int na = a[i] ;
			if (ins(root , na)) b[len++] = na ;
		}

		for (int i = 0 ; i < len ; ++i)	{
			printf("%d" , b[i]) ;
			if (i == len - 1) printf("\n") ;
			else printf(" ") ;
		}
	}

	return 0 ;
}
