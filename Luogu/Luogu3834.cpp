#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 2e5 + 10 , lgN = 30 + 5 , idf = 1e9 ;

struct Tree {
	int num ;
	Tree *left , *right ;

	void init() {num = 0 ; left = right = NULL ;}
}tre[MAX_N * lgN] ;

Tree *root[MAX_N] ;
int n , m , maxa , cur , a[MAX_N] ;

void change(Tree *&rt , Tree *ort , int x , int y , int f) {
	rt = &tre[cur++] ;
	*rt = *ort ; ++rt->num ;
	if (x == y) return ;

	int mid = (x + y) >> 1 ;
	if (f <= mid) change(rt->left , ort->left , x , mid , f) ;
	else change(rt->right , ort->right , mid + 1 , y , f) ;
}

int find(Tree *rt1 , Tree *rt2 , int x , int y , int k) {
	if (x == y) return x ;

	int r = rt1->left->num - rt2->left->num , mid = (x + y) >> 1 ;
	if (k <= r) return find(rt1->left , rt2->left , x , mid , k) ;
	else return find(rt1->right , rt2->right , mid + 1 , y , k - r) ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 1 ; i <= n ; ++i) {
		scanf("%d" , &a[i]) ;
		a[i] += idf ; maxa = std::max(maxa , a[i]) ;
	}

	///

	root[0] = &tre[cur++] ; root[0]->init() ;
	root[0]->left = root[0]->right = root[0] ;
	for (int i = 1 ; i <= n ; ++i) change(root[i] , root[i - 1] , 0 , maxa , a[i]) ;

	for (int i = 0 ; i < m ; ++i) {
		int x , y , k , ans ;
		scanf("%d %d %d" , &x , &y , &k) ;

		ans = find(root[y] , root[x - 1] , 0 , maxa , k) ;
		printf("%d\n" , ans - idf) ;
	}

	return 0 ;
}
