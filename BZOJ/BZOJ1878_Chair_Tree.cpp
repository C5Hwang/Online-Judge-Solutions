#include <stdio.h>
#include <stdlib.h>

const int MAX_N = 50000 + 10 , MAX_NUM = 1000000 + 10 , lgN = 20 + 5 ;

struct Node {
	int num ;
	Node *ch[2] ;
}tree[MAX_N * lgN] ;

Node *root[MAX_N] ;
int n , m , cur , ap[MAX_NUM] , last[MAX_N] ;

Node *build(int x , int y) {
	Node *rt = &tree[cur++] ;
	rt->num = 0 ;
	rt->ch[0] = rt->ch[1] = NULL ;

	if (x == y) return rt ;

	int mid = (x + y) >> 1 ;
	rt->ch[0] = build(x , mid) ;
	rt->ch[1] = build(mid + 1 , y) ;

	return rt ;
}

Node *update(Node *rt , int x , int y , int p) {
	Node *ret = &tree[cur++] ;
	*ret = *rt ; ++ret->num ;

	if (x == y) return ret ;

	int mid = (x + y) >> 1 ;
	if (p <= mid) ret->ch[0] = update(rt->ch[0] , x , mid , p) ;
	else ret->ch[1] = update(rt->ch[1] , mid + 1 , y , p) ;

	return ret ;
}

int query(Node *r1 , Node *r2 , int x , int y , int fx , int fy) {
	if (fy < x || y < fx) return 0 ;
	if (fx <= x && y <= fy) return r1->num - r2->num ;

	int mid = (x + y) >> 1 ,
		s1 = query(r1->ch[0] , r2->ch[0] , x , mid , fx , fy) ,
		s2 = query(r1->ch[1] , r2->ch[1] , mid + 1 , y , fx , fy) ;

	return s1 + s2 ;
}

int main() {
	scanf("%d" , &n) ;
	for (int i = 1 ; i <= n ; ++i) {
		int a ;
		scanf("%d" , &a) ;
		last[i] = ap[a] + 1 ;
		ap[a] = i ;
	}

	///
	
	root[0] = build(1 , n) ;
	for (int i = 1 ; i <= n ; ++i) root[i] = update(root[i - 1] , 1 , n , last[i]) ;

	///
	
	scanf("%d" , &m) ;
	for (int i = 0 ; i < m ; ++i) {
		int x , y ;
		scanf("%d %d" , &x , &y) ;

		int res = query(root[y] , root[x - 1] , 1 , n , 1 , x) ;

		printf("%d\n" , res) ;
	}

	return 0 ;
}
