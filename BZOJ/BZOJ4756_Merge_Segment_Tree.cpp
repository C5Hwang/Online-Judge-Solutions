#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 1e5 + 10 , MAX_A = 30 + 5 ;

struct STree {
	int num ;
	STree *left , *right ;

	void init() {num = 0 ;left = right = NULL ;}
	void update() {
		if (left) num += left->num ;
		if (right) num += right->num ;
	}
}*root[MAX_N] ;
struct Link {
	int num ;
	Link *next ;
}list[MAX_N] ;

Link *head[MAX_N] ;
int n , cur , maxa , a[MAX_N] , ans[MAX_N] ;

///

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

///

STree *merge(STree *rt , STree *ort) {
	if (!rt) return ort ;
	if (!ort) return rt ;

	rt->num += ort->num ;
	rt->left = merge(rt->left , ort->left) ;
	rt->right = merge(rt->right , ort->right) ;

	return rt ;
}

void add(STree *&rt , int x , int y , int f) {
	if (f < x || y < f) return ;

	if (!rt) {rt = new STree() ; rt->init() ;}
	if (x == y) {
		++rt->num ;
		return ;
	}

	int mid = (x + y) >> 1 ;
	add(rt->left , x , mid , f) ;
	add(rt->right , mid + 1 , y , f) ;

	rt->update() ;
}

int getans(STree *rt , int x , int y , int fx , int fy) {
	if (!rt) return 0 ;
	if (y < fx || fy < x) return 0 ;
	if (fx <= x && y <= fy) return rt->num ;

	int mid = (x + y) >> 1 ,
		s1 = getans(rt->left , x , mid , fx , fy) ,
		s2 = getans(rt->right , mid + 1 , y , fx , fy) ;

	return s1 + s2 ;
}

///

void dfs(int x) {
	add(root[x] , 1 , maxa , a[x]) ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		dfs(nx) ;

		root[x] = merge(root[x] , root[nx]) ;
	}

	if (a[x] < maxa) ans[x] = getans(root[x] , 1 , maxa , a[x] + 1 , maxa) ;
	else ans[x] = 0 ;
}

///

int main() {
	scanf("%d" , &n) ;
	for (int i = 1 ; i <= n ; ++i)
		scanf("%d" , &a[i]) , maxa = std::max(maxa , a[i]) ;
	for (int i = 2 ; i <= n ; ++i) {
		int x ; scanf("%d" , &x) ;
		ins(x , i) ;
	}

	///
	
	dfs(1) ;
	for (int i = 1 ; i <= n ; ++i)
		printf("%d\n" , ans[i]) ;

	return 0 ;
}
