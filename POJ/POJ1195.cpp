#include <stdio.h>
#include <stdlib.h>
using namespace std ;

const int MAX_N = 1100 + 10 ;

int n , q , tree[MAX_N][MAX_N] ;

int lowbit(int x) {
	return x & (-x) ;
}

void update(int x , int y , int a) {
	while (x <= n) {
		int ny = y ;
		while (ny <= n) {
			tree[x][ny] += a ;
			
			ny += lowbit(ny) ;
		}
		
		x += lowbit(x) ;
	}
}

int find(int x , int y) {
	if (x <= 0 || y <= 0) return 0 ;
	
	int sum = 0 ;
	while (x > 0) {
		int ny = y ;
		while (ny > 0) {
			sum += tree[x][ny] ;
			
			ny -= lowbit(ny) ;
		}
		
		x -= lowbit(x) ;
	}
	
	return sum ;
}

int sum(int lx , int ly , int rx , int ry) {
	return find(rx , ry) - find(lx - 1 , ry) - find(rx , ly - 1) + find(lx - 1 , ly - 1) ;
}

int main() {
	scanf("%d %d" , &q , &n) ;
	scanf("%d" , &q) ;
	while (q != 3) {
		if (q == 1) {
			int x , y , a ;
			scanf("%d %d %d", &x , &y , &a) ;
			++x ; ++y ;
			
			update(x , y , a) ;
		}
		else if (q == 2) {
			int l , b , r , t ;
			scanf("%d %d %d %d" , &l , &b , &r , &t) ;
			++l ; ++b ; ++r ; ++t ;
		
			printf("%d\n" , sum(l , b , r , t)) ;
		}
		
		scanf("%d" , &q) ;
	}
	
	return 0 ;
}
