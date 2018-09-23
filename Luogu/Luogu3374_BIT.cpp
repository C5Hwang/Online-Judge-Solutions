#include <stdio.h>
#include <stdlib.h>

const int MAX_N = 5e5 + 10 ;

int n , m , BIT[MAX_N] ;

int lowbit(int x) {return x & (-x) ;}

void add(int x , int y) {
	for (; x <= n ; x += lowbit(x)) BIT[x] += y ;
}

int sum(int x) {
	int s = 0 ;
	for (; x ; x -= lowbit(x)) s += BIT[x] ;

	return s ;
}

int GetSum(int x , int y) {
	if (!(x - 1)) return sum(y) ;
	else return sum(y) - sum(x - 1) ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 1 ; i <= n ; ++i) {
		int a ; scanf("%d" , &a) ;
		add(i , a) ;
	}

	///

	for (int i = 0 ; i < m ; ++i) {
		int ty , x , y ;
		scanf("%d %d %d" , &ty , &x , &y) ;

		if (ty == 1) add(x , y) ;
		else printf("%d\n" , GetSum(x , y)) ;
	}

	return 0 ;
}
