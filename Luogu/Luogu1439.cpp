#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 ;

int n , a[MAX_N] , BIT[MAX_N] , idx[MAX_N] , f[MAX_N] ;

inline int lowbit(int x) {return x & (-x) ;}

void update(int x , int a) {
	for (; x <= n ; x += lowbit(x)) BIT[x] = std::max(BIT[x] , a) ;
}

int find(int x) {
	int s = BIT[x] ;
	for (; x ; x -= lowbit(x)) s = std::max(s , BIT[x]) ;

	return s ;
}

int main() {
	scanf("%d" , &n) ;
	for (int i = 1 ; i <= n ; ++i) {
		int t ;
		scanf("%d" , &t) ;
		idx[t] = i ;
	}
	for (int i = 1 ; i <= n ; ++i) scanf("%d" , &a[i]) , a[i] = idx[a[i]] ;

	///

	int ans = 0 ;
	for (int i = 1 ; i <= n ; ++i) {
		f[i] = find(a[i]) + 1 ;
		update(a[i] , f[i]) ;

		ans = std::max(ans , f[i]) ;
	}

	printf("%d\n" , ans) ;

	return 0 ;
}