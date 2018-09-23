#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 100000 + 10 , lgN = 20 ;

struct Node {
	int sum ;
	Node *left , *right ;
}tree[MAX_N * lgN] ;

Node *rt[MAX_N] ;
int n , m , cur , siz , a[MAX_N] , b[MAX_N] ;

Node *build(int x , int y) {
	int p = ++cur , mid = (x + y) >> 1 ;

	tree[p].sum = 0 ;

	if (x == y) return &tree[p] ;

	tree[p].left = build(x , mid) ;
	tree[p].right = build(mid + 1 , y) ;

	return &tree[p] ;
}

Node *update(Node *p , int x , int y , int num) {
	int mid = (x + y) >> 1 ;

	Node *ret = &tree[++cur] ;
	*ret = *p ; ++ret->sum ;

	if (x == y) return ret ;

	if (num <= mid) ret->left = update(p->left , x , mid , num) ;
	else ret->right = update(p->right , mid + 1 , y , num) ;

	return ret ;
}

int query(Node *r1 , Node *r2 , int x , int y , int k) {
	if (x == y) return b[x] ;

	int sum = r2->left->sum - r1->left->sum , mid = (x + y) >> 1 ;

	if (sum >= k) return query(r1->left , r2->left , x , mid , k) ;
	else return query(r1->right , r2->right , mid + 1 , y , k - sum) ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 1 ; i <= n ; ++i)
		scanf("%d" , &a[i]) , b[i] = a[i] ;

	///
	
	std::sort(b + 1 , b + 1 + n) ;
	siz = std::unique(b + 1 , b + 1 + n) - (b + 1) ;

	rt[0] = build(1 , siz) ;
	for (int i = 1 ; i <= n ; ++i) {
		int p = std::lower_bound(b + 1 , b + 1 + siz , a[i]) - b ;

		rt[i] = update(rt[i - 1] , 1 , siz , p) ;
	}

	///
	
	for (int i = 0 ; i < m ; ++i) {
		int u , v , k , res ;
		scanf("%d %d %d" , &u , &v , &k) ;

		res = query(rt[u - 1] , rt[v] , 1 , siz , k) ;

		printf("%d\n" , res) ;
	}

	return 0 ;
}
