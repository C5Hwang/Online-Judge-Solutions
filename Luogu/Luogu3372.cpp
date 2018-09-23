#include <stdio.h>
#include <stdlib.h>

#define ll long long

const int MAX_N = 1e5 + 10 ;

struct TREE {
	ll num , lazy ;
}tree[MAX_N << 2] ;

int n , m ;
ll a[MAX_N] ;

void build(int t , int x , int y) {
	if (x == y) {
		tree[t].num = a[x] ;
		return ;
	}

	int mid = (x + y) >> 1 ;
	build(t << 1 , x , mid) ; build(t << 1 | 1 , mid + 1 , y) ;

	tree[t].num = tree[t << 1].num + tree[t << 1 | 1].num ;
}

void down(int t , int x , int y) {
	ll lz = tree[t].lazy ;
	int L = t << 1 , R = t << 1 | 1 , mid = (x + y) >> 1 ;

	tree[L].lazy += lz ; tree[R].lazy += lz ;
	tree[L].num += (mid - x + 1) * lz ; tree[R].num += (y - mid) * lz ;
	tree[t].lazy = 0 ;
}

void update(int t , int x , int y , int fx , int fy , ll a) {
	if (y < fx || fy < x) return ;
	if (fx <= x && y <= fy) {
		tree[t].num += (y - x + 1) * a ;
		tree[t].lazy += a ;

		return ;
	}

	down(t , x , y) ;
	int mid = (x + y) >> 1 ;
	update(t << 1 , x , mid , fx , fy , a) ;
	update(t << 1 | 1 , mid + 1 , y , fx , fy , a) ;

	tree[t].num = tree[t << 1].num + tree[t << 1 | 1].num ;
}

ll getans(int t , int x , int y , int fx , int fy) {
	if (y < fx || fy < x) return 0 ;
	if (fx <= x && y <= fy) return tree[t].num ;
	down(t , x , y) ;

	int mid = (x + y) >> 1 ;
	ll s1 = getans(t << 1 , x , mid , fx , fy) , s2 = getans(t << 1 | 1 , mid + 1 , y , fx , fy) ;
	return s1 + s2 ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 1 ; i <= n ; ++i) scanf("%lld" , &a[i]) ;
	build(1 , 1 , n) ;

	///

	for (int i = 0 ; i < m ; ++i) {
		int op , x , y ; ll k ;
		scanf("%d %d %d" , &op , &x , &y) ;
		if (op == 1) scanf("%lld" , &k) ;

		if (op == 1) update(1 , 1 , n , x , y , k) ;
		else printf("%lld\n" , getans(1 , 1 , n , x , y)) ;
	}

	return 0 ;
}
