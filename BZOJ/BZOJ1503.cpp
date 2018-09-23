#include <stdio.h>
#include <stdlib.h>

const int MAX_N = 100000 + 10 ;

struct Node {
	int num , r , s ;
	Node *ch[2] ;

	int cmp(int x) {
		if (x <= num) return 0 ;
		else return 1 ;
	}
}tre[MAX_N] ;

Node *root = NULL ;
int n , cur , sum , lsum , lim ;

void update(Node *rt) {
	int sum = 1 ;
	
	for (int d = 0 ; d < 2 ; ++d)
		if (rt->ch[d]) sum += rt->ch[d]->s ;
	
	rt->s = sum ;
}

void rotate(Node *&rt , int d) {
	Node *son = rt->ch[d^1] ;
	rt->ch[d^1] = son->ch[d] ; son->ch[d] = rt ; rt = son ;
	
	update(rt->ch[d]) ; update(rt) ;
}

void ins(Node *&rt , int a) {
	if (!rt) {
		rt = &tre[++cur] ;
		rt->num = a ; rt->s = 1 ; rt->r = rand() ;
		rt->ch[0] = rt->ch[1] = NULL ;

		return ;
	}

	int d = rt->cmp(a) ;

	ins(rt->ch[d] , a) ; update(rt) ;
	if (rt->ch[d]->r < rt->r) rotate(rt , d^1) ;
}

void add(Node *rt , int a) {
	if (!rt) return ;

	rt->num += a ;
	add(rt->ch[0] , a) ;
	add(rt->ch[1] , a) ;
}

void del(Node *&rt , int a) {
	if (rt->num == a) {
		if (!rt->ch[0]) rt = rt->ch[1] ;
		else if (!rt->ch[1]) rt = rt->ch[0] ;
		else {
			int d = rt->ch[0]->r < rt->ch[1]->r ? 1 : 0 ;

			rotate(rt , d) ; del(rt->ch[d] , a) ;
		}
		
		if (rt) update(rt) ;

		return ;
	}

	int d = rt->cmp(a) ;

	del(rt->ch[d] , a) ; update(rt) ;
}

int kth(Node *rt , int a) {
	if (!rt) return -1 ;
	
	int k = rt->ch[0] ? rt->ch[0]->s + 1 : 1 ;

	if (k == a) return rt->num ;
	else if (k > a) return kth(rt->ch[0] , a) ;
	else return kth(rt->ch[1] , a - k) ;
}

int main() {
	scanf("%d %d" , &n , &lim) ;
	for (int i = 0 ; i < n ; ++i) {
		char q ; int a ;
		getchar() ;
		scanf("%c %d" , &q , &a) ;

		if (q == 'I')
			{if (a >= lim) ins(root , a) , ++sum ;}
		else if (q == 'A') add(root , a) ;
		else if (q == 'S') {
				add(root , -a) ;
				
				for (int minn = kth(root , 1) ; minn < lim && sum > 0 ; minn = kth(root , 1))
					del(root , minn) , --sum , ++lsum ;
			}
		else if (q == 'F') {
				int res = kth(root , (sum - a + 1)) ;
				printf("%d\n" , res) ;
			}
	}
	printf("%d\n" , lsum) ;

	return 0 ;
}

