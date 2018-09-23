#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 5e5 + 10 , INF = 0x3f3f3f3f ;

struct data {
	int sum , ls , rs , ms ;
}tree[MAX_N << 2] ;

int n , m ;
data empty ;

data merge(data x , data y) {
	if (x.sum == -INF) return y ;
	if (y.sum == -INF) return x ;

	data tmp ;
	tmp.ls = std::max(x.ls , x.sum + y.ls) ;
	tmp.rs = std::max(y.rs , y.sum + x.rs) ;

	tmp.ms = std::max(std::max(x.ms , y.ms) , x.rs + y.ls) ;
	tmp.ms = std::max(std::max(tmp.ls , tmp.rs) , tmp.ms) ;
	tmp.sum = x.sum + y.sum ;

	return tmp ;
}

void update(int t , int x , int y , int f , int a) {
	if (f < x || y < f) return ;
	if (x == f && y == f) {
		data *p = &tree[t] ;
		p->ls = p->rs = p->ms = p->sum = a ;
		return ;
	}

	int mid = (x + y) >> 1 ;
	update(t << 1 , x , mid , f , a) ;
	update(t << 1 | 1 , mid + 1 , y , f , a) ;
	tree[t] = merge(tree[t << 1] , tree[t << 1 | 1]) ;
}

data getans(int t , int x , int y , int fx , int fy) {
	if (y < fx || fy < x) return empty ;
	if (fx <= x && y <= fy) return tree[t] ;

	int mid = (x + y) >> 1 ;
	data s1 = getans(t << 1 , x , mid , fx , fy) , s2 = getans(t << 1 | 1 , mid + 1 , y , fx , fy) ;

	return merge(s1 , s2) ;
}

int main() {
	empty = (data){-INF , -INF , -INF , -INF} ;

	scanf("%d %d" , &n , &m) ;
	for (int i = 1 ; i <= n ; ++i) {
		int a ;
		scanf("%d" , &a) ;
		update(1 , 1 , n , i , a) ;
	}

	///

	for (int i = 0 ; i < m ; ++i) {
		int op , x , y ;
		scanf("%d %d %d" , &op , &x , &y) ;
		if (op == 1) {
			if (x > y) std::swap(x , y) ;
			printf("%d\n" , getans(1 , 1 , n , x , y).ms) ;
		}
		else update(1 , 1 , n , x , y) ;
	}

	return 0 ;
}
