#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 1e5 + 10 ;

std::map<int , int>  fa ;

int n , a[MAX_N] , b[MAX_N] ;

int findset(int x) {return (fa[x] == -1) ? x : (fa[x] = findset(fa[x])) ;}

void check(int x) {
	if (!fa.count(x)) fa[x] = -1 ;
}

int merge(int x , int y) {
	check(x) ; check(y) ;

	int fx = findset(x) , fy = findset(y) ;
	if (fx == fy) return 0 ;
	else {
		fa[fx] = fy ;
		return 1 ;
	}
}

bool checkans() {
	std::sort(a + 0 , a + n + 1) ;
	std::sort(b + 1 , b + n + 1) ;

	int p = 0 , i ;
	for (i = 1 ; i <= n ;) {
		for (; p <= n && a[p] != b[i] ; ++p) ;

		if (p > i) return 0 ;
		++p ; ++i ;
	}

	return 1 ;
}

int main() {
	scanf("%d" , &n) ;

	int s = 0 ;
	for (int i = 1 ; i <= n ; ++i) scanf("%d" , &a[i]) , s ^= a[i] ;
	for (int i = 1 ; i <= n ; ++i) scanf("%d" , &b[i]) ;
	a[0] = s ;

	///

	int c = 0 ;
	for (int i = 1 ; i <= n ; ++i) if (a[i] != b[i]) ++c ;
	for (int i = 1 ; i <= n ; ++i) {
		if (a[i] == b[i]) continue ;

		c -= merge(a[i] , b[i]) ;
	}
	if (fa.size()) c += fa.size() ;
	if (fa.count(s)) --c ;

	if (checkans()) printf("%d\n" , c) ;
	else printf("-1\n") ;

	return 0 ;
}