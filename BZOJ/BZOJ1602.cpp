#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 1e3 + 10 , lgN = 25 ;

struct Link {
	int num , val ;
	Link *next ;
}list[2 * MAX_N] ;

int n , q , cur ;
Link *head[MAX_N] ;
int dis[MAX_N] , dep[MAX_N] , fa[MAX_N][lgN] ;

void dfs(int x , int f) {
	fa[x][0] = f ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == f) continue ;

		dep[nx] = dep[x] + 1 ; dis[nx] = dis[x] + h->val ;
		dfs(nx , x) ;
	}
}

int GetLCA(int x , int y) {
	if (dep[x] > dep[y]) std::swap(x , y) ;

	for (int i = 20 ; i >= 0 ; --i) {
		if ((1 << i) > n) continue ;

		int temp = fa[y][i] ;
		if (dep[temp] >= dep[x]) y = temp ;
	}

	if (x == y) return x ;

	for (int i = 20 ; i >= 0 ; --i) {
		if ((1 << i) > n) continue ;

		int tx = fa[x][i] , ty = fa[y][i] ;

		if (tx != ty) x = tx , y = ty ;
	}

	return fa[x][0] ;
}

void ins(int x , int y , int v) {
	list[cur].num = y ;
	list[cur].val = v ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

int main() {
	scanf("%d %d" , &n , &q) ;
	for (int i = 1 ; i < n ; ++i) {
		int x , y , v ; scanf("%d %d %d" , &x , &y , &v) ;
		ins(x , y , v) ; ins(y , x , v) ;
	}

	///
	
	dis[1] = 0 ; dep[1] = 1 ;
	dfs(1 , 1) ;

	for (int i = 1 ; (1 << i) <= n ; ++i)
		for (int j = 1 ; j <= n ; ++j) {
			int k = fa[j][i - 1] ;
			fa[j][i] = fa[k][i - 1] ;
		}

	///

	for (int i = 0 ; i < q ; ++i) {
		int x , y , f ;
		scanf("%d %d" , &x , &y) ;

		f = GetLCA(x , y) ;
		printf("%d\n" , dis[x] + dis[y] - 2 * dis[f]) ;
	}

	return 0 ;
}
