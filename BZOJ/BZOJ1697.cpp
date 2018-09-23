#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e4 + 10 , INF = 0x3f3f3f3f ;

struct data{int num , bh ;}t[MAX_N] ;

bool ap[MAX_N] ;
int n , mn , len , ans , MN , eg[MAX_N] ;

bool cmp(data x , data y) {return x.num < y.num ;}

void dfs(int x) {
	if (ap[x]) return ;
	ap[x] = 1 ;
	++len ; mn = std::min(t[x].num , mn) ;
	dfs(eg[x]) ;
}

int main() {
	scanf("%d" , &n) ;

	ans = 0 ; MN = INF ;
	for (int i = 1 ; i <= n ; ++i) {
		scanf("%d" , &t[i].num) ;
		t[i].bh = i ; MN = std::min(MN , t[i].num) ; ans += t[i].num ;
	}

	///

	std::sort(t + 1 , t + 1 + n , cmp) ;
	for (int i = 1 ; i <= n ; ++i) eg[i] = t[i].bh ;

	for (int i = 1 ; i <= n ; ++i) {
		if (ap[i]) continue ;
		len = 0 ; mn = INF ; dfs(i) ;

		int tmp = std::min(mn * (len - 2) , MN * (len + 1) + mn) ;
		ans += tmp ;
	}

	printf("%d\n" , ans) ;

	return 0 ;
}