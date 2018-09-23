#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 1e5 + 10 ;

struct data {
	int on , off ;
	bool lazy ;
}tree[4 * MAX_N] ;

int n , m ;

///

void update(int t) {
	tree[t].on = tree[t << 1].on + tree[(t << 1) + 1].on ;
	tree[t].off = tree[t << 1].off + tree[(t << 1) + 1].off ;
}

void down(int t) {
	if (!tree[t].lazy) return ;

	tree[t].lazy = 0 ;
	int Lson = t << 1 , Rson = (t << 1) + 1 ;
	tree[Lson].lazy ^= 1 ; tree[Rson].lazy ^= 1 ;

	std::swap(tree[Lson].on , tree[Lson].off) ;
	std::swap(tree[Rson].on , tree[Rson].off) ;
}

///

int query(int t , int x , int y , int fx , int fy) {
	if (y < fx || fy < x) return 0 ;
	if (fx <= x && y <= fy) return tree[t].on ;

	down(t) ;

	int mid = (x + y) >> 1 ,
		s1 = query(t << 1 , x , mid , fx , fy) ,
		s2 = query((t << 1) + 1 , mid + 1 , y , fx , fy) ;

	return s1 + s2 ;
}

void change(int t , int x , int y , int fx , int fy) {
	if (y < fx || fy < x) return ;
	if (fx <= x && y <= fy) {
		std::swap(tree[t].on , tree[t].off) ;
		tree[t].lazy ^= 1 ;

		return ;
	}
	down(t) ;

	int mid = (x + y) >> 1 ;
	change(t << 1 , x , mid , fx , fy) ;
	change((t << 1) + 1 , mid + 1 , y , fx , fy) ;

	update(t) ;
}

void build(int t , int x , int y) {
	if (x == y) {
		tree[t].off = 1 ;

		return ;
	}

	int mid = (x + y) >> 1 ;
	build(t << 1 , x , mid) ;
	build((t << 1) + 1 , mid + 1 , y) ;

	update(t) ;
}

///

int main() {
	scanf("%d %d" , &n , &m) ;

	build(1 , 1 , n) ;
	for (int i = 0 ; i < m ; ++i) {
		int op , x , y ;
		scanf("%d %d %d" , &op , &x , &y) ;

		if (op) printf("%d\n" , query(1 , 1 , n , x , y)) ;
		else change(1 , 1 , n , x , y) ;
	}

	return 0 ;
}
