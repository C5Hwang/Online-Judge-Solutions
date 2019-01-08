#include <map>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 2e5 + 10 ;

std::map<int , int> p1 , p2 ;

int T , n , a[MAX_N] , pre[MAX_N] , last[MAX_N] ;

bool check(int p , int x , int y) {
	return pre[p] < x && y < last[p] ;
}

bool solve(int x , int y) {
	if (x > y) return 1 ;

	int p = -1 ;
	for (int i = x ; i <= y ; ++i) {
		int j = y - i + x ;
		if (i > j) break ;

		if (check(i , x , y)) {p = i ; break ;}
		else if (check(j , x , y)) {p = j ; break ;}
	}

	if (p == -1) return 0 ;
	return solve(x , p - 1) && solve(p + 1 , y) ;
}

int main() {
	scanf("%d" , &T) ;
	for (; T-- ;) {
		scanf("%d" , &n) ;
		for (int i = 1 ; i <= n ; ++i) scanf("%d" , &a[i]) ;

		p1.clear() ; p2.clear() ;
		for (int i = 1 ; i <= n ; ++i) {
			if (!p1.count(a[i])) pre[i] = 0 ;
			else pre[i] = p1[a[i]] ;
			p1[a[i]] = i ;
		}
		for (int i = n ; i >= 1 ; --i) {
			if (!p2.count(a[i])) last[i] = n + 1 ;
			else last[i] = p2[a[i]] ;
			p2[a[i]] = i ;
		}

		bool ans = solve(1 , n) ;
		if (ans) printf("non-boring\n") ;
		else printf("boring\n") ;
	}

	return 0 ;
}