#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 2e5 + 10 , lgN = 20 + 5 , INF = 0x3f3f3f3f ;

struct Chair {
	int num ;
	Chair *left , *right ;

	void init() {
		int num = 0 ;
		left = right = NULL ;
	}
	void update() {
		num = INF ;
		if (left) num = std::min(left->num , num) ;
		if (right) num = std::min(right->num , num) ;
		if (num == INF) num = 0 ;
	}
}tree[MAX_N * lgN] ;

Chair *root[MAX_N] ;
int n , m , cur , maxa , a[MAX_N] ;

void build(Chair *&rt , int x , int y) {
	rt = &tree[cur++] ; rt->init() ;
	if (x == y) return ;

	int mid = (x + y) >> 1 ;
	build(rt->left , x , mid) ;
	build(rt->right , mid + 1 , y) ;
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
	else change(ort->left , rt->left , x , mid , f , a) ;

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
	for (int i = 1 ; i <= n ; ++i) scanf("%d" , &a[i]) , maxa = std::max(maxa , a[i]) ;
	++maxa ;

	///

	build(root[0] , 0 , maxa) ;
	for (int i = 1 ; i <= n ; ++i) change(root[i - 1] , root[i] , 0 , maxa , a[i] , i) ;

	///
	
	for (int i = 0 ; i < m ; ++i) {
		int x , y ; scanf("%d %d" , &x , &y)  ;
		
		int res = getans(root[y] , 0 , maxa , x) ;
		printf("%d\n" , res) ;
	}

	return 0 ;
}
