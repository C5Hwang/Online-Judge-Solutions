#include <stdio.h>
#include <stdlib.h>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e3 + 10 ;

bool ap[MAX_N] ;
int n , len , eg[MAX_N] ;

int gcd(int a , int b) {return b ? gcd(b , a % b) : a ;}

void dfs(int x) {
	if (ap[x]) return ;
	ap[x] = 1 ; ++len ;
	dfs(eg[x]) ;
}

int main() {
	scanf("%d" , &n) ;
	for (int i = 1 ; i <= n ; ++i) scanf("%d" , &eg[i]) ;

	///

	int ans = 1 ;
	for (int i = 1 ; i <= n ; ++i) {
		if (ap[i]) continue ;
		len = 0 ; dfs(i) ;

		ans = ans / gcd(ans , len) * len ;
	}

	printf("%d\n" , ans) ;

	return 0 ;
}