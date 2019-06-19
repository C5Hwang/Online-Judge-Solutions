#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e4 + 10 ;

struct Link {
	int num ;
	Link *next ;
}list[MAX_N << 1] ;

Link *head[MAX_N] ;
int T , n , X , cur , c[MAX_N] ;
ll k , ans , f[MAX_N] , g[MAX_N] ;

void init() {
	cur = 0 ; ans = 0 ;
	memset(head , 0 , sizeof(head)) ;
}

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

void dfs(int x , int fa , ll dis) {
	dis += c[x] ; f[x] = g[x] = dis ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa) continue ;

		dfs(nx , x , dis) ;
		g[x] = std::max(g[x] , g[nx]) ;
	}
}

void work(int x , int fa , ll ad) {
	g[x] -= ad ;
	ll ned = std::max((ll)0 , g[x] - k) , cost = std::min(ned , (ll)c[x]) ;

	ad += cost ; ans += cost << 1 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa) continue ;

		work(nx , x , ad) ;
	}
}

int main() {
	scanf("%d" , &T) ;
	for (; T-- ;) {
		init() ;

		scanf("%d %d %lld" , &n , &X , &k) ;
		for (int i = 1 ; i <= n ; ++i) scanf("%d" , &c[i]) ;
		for (int i = 1 ; i < n ; ++i) {
			int x , y ;
			scanf("%d %d" , &x , &y) ;

			ins(x , y) ; ins(y , x) ;
		}

		///

		dfs(X , X , 0) ;
		work(X , X , 0) ;

		printf("%lld\n" , ans) ;
	}

	return 0 ;
}