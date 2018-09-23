#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 200000 + 10 ;

int n , d , cur ;
long long res , tree[4 * MAX_N] ;

void ins(int t , int x , int y , int f , int a) {
	if (f < x || y < f) return ;
	if (x == f && y == f) {tree[t] = a ; return ;}

	int mid = (x + y) / 2 ;
	ins(t * 2 , x , mid , f , a) ;
	ins(t * 2 + 1 , mid + 1 , y , f , a) ;

	tree[t] = std::max(tree[t * 2] , tree[t * 2 + 1]) ;
}

long long find(int t , int x , int y , int fx , int fy) {
	if (y < fx || fy < x) return -1 ;
	if (fx <= x && y <= fy) return tree[t] ;

	int mid = (x + y) / 2 ;
	long long lm = find(t * 2 , x , mid , fx , fy) ,
		  rm = find(t * 2 + 1 , mid + 1 , y , fx , fy) ;

	return std::max(lm , rm) ;
}

int main() {
	res = 0 ;

	scanf("%d %d" , &n , &d) ;
	for (int i = 0 ; i < n ; ++i) {
		getchar() ;
		char q ; int m ;
		scanf("%c %d" , &q , &m) ;

		if (q == 'A') {
			long long num = (m + res) % d ;
			++cur ;
			ins(1 , 1 , n , cur , num) ;
		}
		else {
			res = find(1 , 1 , n , cur - m + 1 , cur) ;

			printf("%lld\n" , res) ;
		}
	}

	return 0 ;
}
