#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 5e4 + 10 ;

int n , siz , a[MAX_N] , ad[MAX_N] , bk[MAX_N] ;

void modify(int x , int y , int c) {
	for (int i = bk[x] + 1 ; i < bk[y] ; ++i) ad[i] += c ;

	for (int i = x ; i <= std::min(bk[x] * siz , y) ; ++i) a[i] += c ;
	if (bk[x] != bk[y]) for (int i = (bk[y] - 1) * siz + 1 ; i <= y ; ++i) a[i] += c ;
}

int main() {
	scanf("%d" , &n) ; siz = (int)sqrt(n) ;

	for (int i = 1 ; i <= n ; ++i) scanf("%d" , &a[i]) ;
	for (int i = 1 ; i <= n ; ++i) bk[i] = (i - 1) / siz + 1 ;

	///

	for (int i = 1 ; i <= n ; ++i) {
		int op , x , y , c ;
		scanf("%d %d %d %d" , &op , &x , &y , &c) ;

		if (op == 1) printf("%d\n" , a[y] + ad[bk[y]]) ;
		else modify(x , y , c) ;
	}

	return 0 ;
}