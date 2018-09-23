#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 2e5 + 10 , lgN = 20 + 5 ;

struct Chair {
	int num ;
	Chair *left , *right ;

	void init() {num = 0 ; left = right = NULL ;}
	void update() {num = std::min(left->num , right->num) ;}
}tree[MAX_N * lgN] ;

Chair *root[MAX_N] ;
int n , m , cur , a[MAX_N] ;

void build(Chair *&rt , int x , int y) {
	rt = &tree[cur++] ;
	rt->init() ;
	if (x == y) return ;

	int mid = (x + y) >> 1 ;
	build(rt->left , x , mid) ; build(rt->right , mid + 1 , y) ;
}

void change(Chair *ort , Chair *&rt , int x , int y , int f , int a) {
	rt = &tree[cur++] ;
	*rt = *ort ;
	if (x == f && y == f) {
		rt->num = a ;
		return ;
	}

	int mid = (x + y) >> 1 ;
	if (mid < f) change(ort->right , rt->right , mid + 1 , y , f , a) ;
	else change(ort->left , rt->left , x , mid , f , a ) ;

	rt->update() ;
}

int getans(Chair *rt , int x , int y , int f) {
	if (x == y) return x ;

	int mid = (x + y) >> 1 ;
	if (rt->left->num >= f) return getans(rt->right , mid + 1 , y , f) ;
	else return getans(rt->left , x , mid , f) ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 1 ; i <= n ; ++i) {
		scanf("%d" , &a[i]) ;
		if (a[i] > n) a[i] = n + 1 ;
	}

	///

	build(root[0] , 0 , n + 1) ;
	for (int i = 1 ; i <= n ; ++i)
		change(root[i - 1] , root[i] , 0 , n + 1 , a[i] , i) ;

	///
	
	for (int i = 0 ; i < m ; ++i) {
		int x , y , res ;
		scanf("%d %d" , &x , &y) ;
		res = getans(root[y] , 0 , n + 1 , x) ;

		printf("%d\n" , res) ;
	}

	return 0 ;
}
