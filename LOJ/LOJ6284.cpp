#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ed(x) (x * siz)
#define st(x) ((x - 1) * siz + 1)
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 ;

bool flag[MAX_N] ;
int n , siz , a[MAX_N] , bk[MAX_N] , col[MAX_N] ;

void fillcol(int x) {
	if (!flag[x]) return ;

	for (int i = st(x) ; i <= std::min(ed(x) , n) ; ++i) a[i] = col[x] ;
	flag[x] = 0 ;
}

int find(int x , int y , int c) {
	int res = 0 ;

	fillcol(bk[x]) ;
	for (int i = x ; i <= std::min(ed(bk[x]) , y) ; ++i) {
		if (a[i] == c) ++res ;
		a[i] = c ;
	}

	if (bk[x] != bk[y]) {
		fillcol(bk[y]) ;
		for (int i = st(bk[y]) ; i <= y ; ++i) {
			if (a[i] == c) ++res ;
			a[i] = c ;
		}
	}

	for (int i = bk[x] + 1 ; i < bk[y] ; ++i)
		if (flag[i]) {
			if (col[i] == c) res += siz ;
			else col[i] = c ;
		}
		else {
			for (int j = st(i) ; j <= ed(i) ; ++j) if (a[j] == c) ++res ;
			flag[i] = 1 ; col[i] = c ;
		}

	return res ;
}

int main() {
	scanf("%d" , &n) ; siz = (int)sqrt(n) ;
	for (int i = 1 ; i <= n ; ++i) scanf("%d" , &a[i]) ;
	for (int i = 1 ; i <= n ; ++i) bk[i] = (i - 1) / siz + 1 ;

	///

	for (int i = 0 ; i < n ; ++i) {
		int x , y , c ;
		scanf("%d %d %d" , &x , &y , &c) ;

		printf("%d\n" , find(x , y , c)) ;
	}

	return 0 ;
}