#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e6 + 10 , INF = 0x3f3f3f3f ;

ll ans ;
bool ap[MAX_N] ;
int n , len , mn , MN , w[MAX_N] , a[MAX_N] , eg[MAX_N] ;

void dfs(int x) {
	if (ap[x]) return ;
	ap[x] = 1 ;
	++len ; mn = std::min(mn , w[x]) ;
	dfs(eg[x]) ;
}

int main() {
	scanf("%d" , &n) ;
	ans = 0 ; MN = INF ;
	for (int i = 1 ; i <= n ; ++i) {
		scanf("%d" , &w[i]) ;
		MN = std::min(MN , w[i]) ; ans += w[i] ;
	}
	for (int i = 1 ; i <= n ; ++i) scanf("%d" , &a[i]) ;
	for (int i = 1 ; i <= n ; ++i) {
		int x ; scanf("%d" , &x) ;
		eg[a[i]] = x ;
	}

	///

	for (int i = 1 ; i <= n ; ++i) {
		if (ap[i]) continue ;
		len = 0 ; mn = INF ; dfs(i) ;

		ll tmp = std::min((ll)mn * (len - 2) , mn + (ll)MN * (len + 1)) ;
		ans += tmp ;
	}

	printf("%lld\n" , ans) ;

	return 0 ;
}