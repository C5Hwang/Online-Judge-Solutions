#include <stdio.h>
#include <stdlib.h>

const int MAX_N = 1e5 + 10 , lgN = 20 + 10 ;

struct Node {
	int num , sum ;
	Node *left , *right ;

	void init() {num = sum = 0 ; left = right = NULL ;}
}tree[MAX_N * lgN] ;

Node *root[MAX_N] ;
int n , m , q , cur , fa[MAX_N] ;

int findset(int x) {return fa[x] == x ? x : (fa[x] = findset(fa[x])) ;}

void ins(Node *&rt , int x , int y , int f , int a) {
	rt = &tree[cur++] ; rt->init() ;
	++rt->sum ;

	if (x == y) {rt->num = a ; return ;}

	int mid = (x + y) >> 1 ;
	if (f <= mid) ins(rt->left , x , mid , f , a) ;
	else ins(rt->right , mid + 1 , y , f , a) ;
}

Node *merge(Node *r1 , Node *r2) {
	if (!r1) return r2 ;
	else if (!r2) return r1 ;

	r1->sum += r2->sum ;
	r1->left = merge(r1->left , r2->left) ;
	r1->right = merge(r1->right , r2->right) ;

	return r1 ;
}

int getans(Node *rt , int x , int y , int f) {
	if (!rt) return -1 ;
	if (x == y) return rt->num ;

	int mid = (x + y) >> 1 ,  r = rt->left ? rt->left->sum : 0 ;

	if (f <= r) return getans(rt->left , x , mid , f) ;
	else return getans(rt->right , mid + 1 , y , f - r) ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 1 ; i <= n ; ++i) fa[i] = i ;
	for (int i = 1 ; i <= n ; ++i) {
		int a ; scanf("%d" , &a) ;
		ins(root[i] , 1 , n , a , i) ;
	}

	for (int i = 0 ; i < m ; ++i) {
		int x , y , fx , fy ;
		scanf("%d %d" , &x , &y) ;

		if (!x || !y) continue ;
		fx = findset(x) ; fy = findset(y) ;

		if (fx != fy) root[fx] = merge(root[fx] , root[fy]) , fa[fy] = fx ;
	}

	///

	scanf("%d" , &q) ;
	for (int i = 0 ; i < q ; ++i) {
		char op ; int x , y ;
		scanf(" %c %d %d" , &op , &x , &y) ;

		if (op == 'Q') {
			int f = findset(x) , ans = getans(root[f] , 1 , n ,  y) ;
			printf("%d\n" , ans) ;
		}
		else {
			if (!x || !y) continue ;
			
			int fx = findset(x) , fy = findset(y) ;
			if (fx != fy) merge(root[fx] , root[fy]) , fa[fy] = fx ;
		}
	}

	return 0 ;
}