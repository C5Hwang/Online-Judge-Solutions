#include <math.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define vt std::vector<int>
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 2e5 + 10 ;

vt b[MAX_N] ;
int n , siz , a[MAX_N] ;

int find(int &x) {
	int res = 1 , tmp = 0 ;
	for (; x > (tmp = b[res].size()) ; x -= tmp , ++res) ;

	return res ;
}

void ins(int x , int c) {
	int pt = find(x) , n = b[pt].size() ;

	b[pt].push_back(c) ;
	for (int i = n ; i >= x ; --i) b[pt][i] = b[pt][i - 1] ;
	b[pt][x - 1] = c ;
}

void rebuild() {
	int m = 0 , tmp ;
	for (int i = 1 ; (tmp = b[i].size()) ; ++i) {
		for (int j = 0 ; j < tmp ; ++j) a[++m] = b[i][j] ;
		b[i].clear() ;
	}

	siz = (int)sqrt(m) ;
	for (int i = 1 ; i <= m ; ++i) {
		tmp = (i - 1) / siz + 1 ;
		b[tmp].push_back(a[i]) ;
	}
}

int main() {
	scanf("%d" , &n) ; siz = (int)sqrt(n) ;
	for (int i = 1 ; i <= n ; ++i) scanf("%d" , &a[i]) ;
	for (int i = 1 ; i <= n ; ++i) {
		int tmp = (i - 1) / siz + 1 ;
		b[tmp].push_back(a[i]) ;
	}

	///

	int rb = siz ;
	for (int i = 0 ; i < n ; ++i) {
		int op , x , y , c ;
		scanf("%d %d %d %d" , &op , &x , &y , &c) ;

		if (!op) ins(x , y) ;
		else {
			int pt = find(y) ; --y ;
			printf("%d\n" , b[pt][y]) ;
		}

		if (!(i % rb)) rebuild() ;
	}

	return 0 ;
}