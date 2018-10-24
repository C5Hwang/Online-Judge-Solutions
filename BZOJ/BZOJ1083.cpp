#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 300 + 10 , MAX_E = 1e5 + 10 ;

struct data {
	int x , y , c ;
}list[MAX_E] ;

int n , m , fa[MAX_N] ;

int findroot(int x) {return fa[x] == -1 ? x : (fa[x] = findroot(fa[x])) ;}

bool check(int x) {
	for (int i = 1 ; i <= n ; ++i) fa[i] = -1 ;

	for (int i = 0 ; i < m ; ++i) {
		data *p = &list[i] ;
		if (p->c > x) continue ;

		int fx = findroot(p->x) , fy = findroot(p->y) ;
		if (fx != fy) fa[fx] = fy ;
	}

	int f = findroot(1) ;
	for (int i = 2 ; i <= n ; ++i)
		if (findroot(i) != f) return 0 ;

	return 1 ;
}

int main() {
	int L = 0 , R = 0 ;
	scanf("%d %d" , &n , &m) ;
	for (int i = 0 ; i < m ; ++i) {
		scanf("%d %d %d" , &list[i].x , &list[i].y , &list[i].c) ;
		R = std::max(R , list[i].c) ;
	}

	///

	++R ;
	for (; L + 1 < R ;) {
		int mid = (L + R) >> 1 ;
		if (check(mid)) R = mid ;
		else L = mid ;
	}

	printf("%d %d\n" , n - 1 , R) ;

	return 0 ;
}