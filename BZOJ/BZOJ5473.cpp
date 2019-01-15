#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e6 + 10 , MAX_M = 2e6 + 10 , mod = 1e9 + 7 ;

struct Link {
	int num ;
	Link *next ;
}list[MAX_M << 1] ;

Link *head[MAX_N] ;
int n , m , ti , cur , ans , dep[MAX_N] , pw[MAX_M] , deg[MAX_N] ;

void dfs(int x , int fa) {
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa) continue ;

		if (!dep[nx]) {dep[nx] = dep[x] + 1 ; dfs(nx , x) ;}
		else {
			int len = dep[x] - dep[nx] + 1 ;
			(ans += pw[m - len]) %= mod ;
		}
	}
}

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

int main() {
	scanf("%d %d" , &n , &m) ;

	pw[0] = 1 ;
	for (int i = 1 ; i <= m ; ++i) pw[i] = (pw[i - 1] << 1) % mod ;
	for (int i = 0 ; i < m ; ++i) {
		int x , y ;
		scanf("%d %d" , &x , &y) ;
		ins(x , y) ; ins(y , x) ; ++deg[x] ; ++deg[y] ;
	}

	///

	dep[1] = 1 ; dfs(1 , 1) ;

	ans = (ans + (ll)n * pw[m]) % mod ;
	ans = (ans - ((ll)m * pw[m - 1] % mod) + mod) % mod ;
	for (int i = 1 ; i <= n ; ++i) ans = (ans - pw[m - deg[i]] + mod) % mod ;

	printf("%d\n" , ans) ;

	return 0 ;
}