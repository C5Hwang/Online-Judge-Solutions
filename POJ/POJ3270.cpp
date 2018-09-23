#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e4 + 10 , INF = 0x3f3f3f3f ;

struct data {int num , bh ;}t[MAX_N] ;

bool ap[MAX_N] ;
int n , ans , len , mn , MN , eg[MAX_N] ;

void dfs(int x) {
	if (ap[x]) return ;
	++len ; mn = std::min(mn , t[x].num) ; ap[x] = 1 ;
	dfs(eg[x]) ;
}

bool cmp(data x , data y) {return x.num < y.num ;}

int main() {
	scanf("%d" , &n) ; MN = INF ;
	for (int i = 1 ; i <= n ; ++i) {
		scanf("%d" , &t[i].num) ;
		t[i].bh = i ; ans += t[i].num ; MN = std::min(MN , t[i].num) ;
	}

	///

	std::sort(t + 1 , t + 1 + n , cmp) ;
	for (int i = 1 ; i <= n ; ++i) eg[t[i].bh] = i ;

	for (int i = 1 ; i <= n ; ++i) {
		if (ap[i]) continue ;
		len = 0 ; mn = INF ;
		dfs(i) ;

		int tmp = std::min(mn * (len - 2) , mn + MN * (len + 1)) ;
		ans += tmp ;
	}

	printf("%d\n" , ans) ;

	return 0 ;
}