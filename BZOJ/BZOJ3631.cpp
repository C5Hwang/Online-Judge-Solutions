#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 3e5 + 10 , lgN = 25 ;

struct Link {
	int num ;
	Link *next ;
}list[2 * MAX_N] ;

Link *head[MAX_N] ;
int n , cur , a[MAX_N] , res[MAX_N] , dep[MAX_N] , f[MAX_N][lgN] ;

void dfs(int x , int fa) {
	f[x][0] = fa ; dep[x] = dep[fa] + 1 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa) continue ;

		dfs(nx , x) ;
	}
}

void find(int x , int fa) {
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa) continue ;

		find(nx , x) ; res[x] += res[nx] ;
	}
}

int GetLca(int x , int y) {
	if (dep[x] > dep[y]) std::swap(x , y) ;
	for (int i = 20 ; i >= 0 ; --i) {
		if ((1 << i) > n) continue ;

		int temp = f[y][i] ;
		if (dep[temp] >= dep[x]) y = temp ;
	}

	if (x == y) return x ;

	for (int i = 20 ; i >= 0 ; --i) {
		if ((1 << i) > n) continue ;

		int tx = f[x][i] , ty = f[y][i] ;
		if (tx != ty) x = tx , y = ty ;
	}

	return f[x][0] ;
}

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

int main() {
	scanf("%d" , &n) ;
	for (int i = 1 ; i <= n ; ++i) scanf("%d" , &a[i]) ;
	for (int i = 1 ; i < n ; ++i) {
		int x , y ;
		scanf("%d %d" , &x , &y) ;
		ins(x , y) ; ins(y , x) ;
	}

	///
	
	dfs(1 , 1) ;
	for (int i = 1 ; (1 << i) <= n ; ++i)
		for (int j = 1 ; j <= n ; ++j)
			f[j][i] = f[f[j][i - 1]][i - 1] ;

	///
	
	for (int i = 2 ; i <= n ; ++i) {
		int x = a[i - 1] , y = a[i] , fa = GetLca(x , y) ;

		++res[x] ; ++res[y] ; --res[fa] ;
		if (f[fa][0] != fa) --res[f[fa][0]] ;
	}
	find(1 , 1) ;
	for (int i = 2 ; i <= n ; ++i) --res[a[i]] ;
	for (int i = 1 ; i <= n ; ++i) printf("%d\n" , res[i]) ;

	return 0 ;
}
