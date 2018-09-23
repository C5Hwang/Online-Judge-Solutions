#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 2e5 + 10 ;

struct Pair {
	int a , b ;
}cd[MAX_N] ;

int n , m ;
bool tree[MAX_N << 2][2][2] ;

void init(int t , int x , int y) {
	if (x == y) tree[t][0][0] = tree[t][0][1] = tree[t][1][0] = tree[t][1][1] = 1 ;
	else {
		for (int i = 0 ; i < 2 ; ++i)
			for (int j = 0 ; j < 2 ; ++j) {
				int numx , numy ;
				if (!i) numx = cd[x].a ; else numx = cd[x].b ;
				if (!j) numy = cd[y].a ; else numy = cd[y].b ;

				if (numx <= numy) tree[t][i][j] = 1 ;
				else tree[t][i][j] = 0 ;
			}
	}
}

void update(int t) {
	int L = t << 1 , R = t << 1 | 1 ;

	for (int i = 0 ; i < 2 ; ++i)
		for (int j = 0 ; j < 2 ; ++j)
			tree[t][i][j] = (tree[L][i][0] && tree[R][0][j]) || (tree[L][i][1] && tree[R][1][j]) ;
}

void build(int t , int x , int y) {
	if (y - x <= 1) {
		init(t , x , y) ;
		return ;
	}

	int mid = (x + y) >> 1 ;
	build(t << 1 , x , mid) ; build(t << 1 | 1 , mid , y) ;

	update(t) ;
}

void change(int t , int x , int y , int f) {
	if (f < x || y < f) return ;
	if (y - x <= 1) {
		init(t , x , y) ;
		return ;
	}

	int mid = (x + y) >> 1 ;
	change(t << 1 , x , mid , f) ; change(t << 1 | 1 , mid , y , f) ;

	update(t) ;
}

int main() {
	scanf("%d" , &n) ;
	for (int i = 1 ; i <= n ; ++i)
		scanf("%d %d" , &cd[i].a , &cd[i].b) ;

	///

	build(1 , 1 , n) ; scanf("%d" , &m) ;
	for (int i = 0 ; i < m ; ++i) {
		int x , y ; scanf("%d %d" , &x , &y) ;
		std::swap(cd[x] , cd[y]) ;

		change(1 , 1 , n , x) ; change(1 , 1 , n , y) ;
		bool ans = tree[1][0][0] || tree[1][0][1] || tree[1][1][0] || tree[1][1][1] ;
		if (ans) printf("TAK\n") ;
		else printf("NIE\n") ;
	}

	return 0 ;
}
