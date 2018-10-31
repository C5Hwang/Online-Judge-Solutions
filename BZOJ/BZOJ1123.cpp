#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 , MAX_E = 1e6 + 10 ;

struct Link {
	int num ;
	Link *next ;
}list[MAX_E] ;

ll ans[MAX_N] ;
Link *head[MAX_N] ;
int n , m , cur , ti , low[MAX_N] , dfn[MAX_N] , siz[MAX_N] ;

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

void dfs(int x , int fa) {
	dfn[x] = low[x] = ++ti ;

	siz[x] = 1 ; ans[x] = n - 1 ;

	int tot = n - 1 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa) continue ;

		if (!dfn[nx]) {
			dfs(nx , x) ;
			siz[x] += siz[nx] ;
			low[x] = std::min(low[x] , low[nx]) ;

			if (low[nx] >= dfn[x]) ans[x] += (ll)siz[nx] * (n - siz[nx]) , tot -= siz[nx] ;
		}
		else low[x] = std::min(low[x] , dfn[nx]) ;
	}

	ans[x] += (ll)tot * (n - tot) ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 0 ; i < m ; ++i) {
		int a , b ; scanf("%d %d" , &a , &b) ;

		ins(a , b) ; ins(b , a) ;
	}

	///

	for (int i = 1 ; i <= n ; ++i)
		if (!dfn[i]) dfs(i , i) ;

	for (int i = 1 ; i <= n ; ++i) printf("%lld\n" , ans[i]) ;

	return 0 ;
}