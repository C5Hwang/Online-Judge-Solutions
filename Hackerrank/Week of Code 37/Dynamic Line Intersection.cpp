#include <stdio.h>
#include <stdlib.h>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int N = 1e5 , M = 320 , MAX_N = 1e5 + 10 , MAX_M = 320 + 10 ;

int n , cnt1[MAX_N] , cnt2[MAX_M][MAX_M] ;

void modify(int x , int y , int a) {
	y %= x ;

	if (x <= M) cnt2[x][y] += a ;
	else for (; y <= N ; y += x) cnt1[y] += a ;
}

int getans(int x) {
	int sum = cnt1[x] ;
	for (int i = 1 ; i <= M ; ++i) {
		int y = x % i ;
		sum += cnt2[i][y] ;
	}

	return sum ;
}

int main() {
	scanf("%d" , &n) ;
	for (int i = 0 ; i < n ; ++i) {
		getchar() ;

		char op ; int x , y ;
		scanf("%c %d" , &op , &x) ;
		if (op != '?') scanf("%d" , &y) ;

		///

		if (op == '+') modify(x , y , 1) ;
		else if (op == '-') modify(x , y , -1) ;
		else printf("%d\n" , getans(x)) ;
	}

	return 0 ;
}