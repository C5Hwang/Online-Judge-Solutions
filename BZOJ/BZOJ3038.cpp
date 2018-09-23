#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 ;

struct Node {
	ll man , sum ;
}tree[MAX_N << 2] ;

int n , q ;
ll a[MAX_N] ;

void update(int t) {
	int L = t << 1 , R = L | 1 ;
	tree[t].man = std::max(tree[L].man , tree[R].man) ;
	tree[t].sum = tree[L].sum + tree[R].sum ;
}

void modify(int t , int x , int y , int fx , int fy) {
	if (y < fx || fy < x) return ;
	if (fx <= x && y <= fy) {
		if (tree[t].man <= 1) return ;

		if (x == y) {
			Node *p = &tree[t] ;
			p->man = (int)sqrt(p->man) ;
			p->sum = p->man ;

			return ;
		}

		int mid = (x + y) >> 1 ;
		modify(t << 1 , x , mid , fx , fy) ;
		modify(t << 1 | 1 , mid + 1 , y , fx , fy) ;

		update(t) ;

		return ;
	}

	int mid = (x + y) >> 1 ;
	modify(t << 1 , x , mid , fx , fy) ;
	modify(t << 1 | 1 , mid + 1 , y , fx , fy) ;

	update(t) ;
}

ll getans(int t , int x , int y , int fx , int fy) {
	if (y < fx || fy < x) return 0 ;
	if (fx <= x && y <= fy) return tree[t].sum ;

	int mid = (x + y) >> 1 ;
	ll s1 = getans(t << 1 , x , mid , fx , fy) ,
	   s2 = getans(t << 1 | 1 , mid + 1 , y , fx , fy) ;

	return s1 + s2 ;
}

void build(int t , int x , int y) {
	if (x == y) {
		tree[t].man = tree[t].sum = a[x] ;

		return ;
	}

	int mid = (x + y) >> 1 ;
	build(t << 1 , x , mid) ; build(t << 1 | 1 , mid + 1 , y) ;

	update(t) ;
}

int main() {
	scanf("%d" , &n) ;
	for (int i = 1 ; i <= n ; ++i) scanf("%lld",  &a[i]) ;
	build(1 , 1 , n) ;

	///

	int Q ; scanf("%d" , &Q) ;
	for (; Q-- ;) {
		int op , x , y ;
		scanf("%d %d %d" , &op , &x , &y) ;

		if (x > y) std::swap(x , y) ;

		if (!op) modify(1 , 1 , n , x , y) ;
		else printf("%lld\n" , getans(1 , 1 , n , x , y)) ;
	}

	return 0 ;
}