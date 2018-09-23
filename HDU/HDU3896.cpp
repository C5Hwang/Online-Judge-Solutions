#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 1e5 + 10 , MAX_M = 5e5 + 10 , lgN = 30 ;

struct Link {
	int num ;
	Link *next ;
}list[2 * MAX_M] ;

Link *head[MAX_N] ;
int n , m , q , cur , time ;
int dfn[MAX_N] , low[MAX_N] , dep[MAX_N] , fa[MAX_N][lgN] ;

///

void dfs(int x , int f) {
	dfn[x] = low[x] = ++time ;
	fa[x][0] = f ;

	bool mf = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;

		if (nx == f && !mf) {mf = 1 ; continue ;}

		if (!dfn[nx]) {
			dep[nx] = dep[x] + 1 ; dfs(nx , x) ;
			low[x] = std::min(low[x] , low[nx]) ;
		}
		else low[x] = std::min(low[x] , dfn[nx]) ;
	}
}

///

int GetLca(int x , int y) {
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
		if (tx == ty) continue ;

		x = tx ; y = ty ;
	}

	return fa[x][0] ;
}

int Jump(int x , int y) {
	for (int i = 20 ; i >= 0 ; --i) {
		if ((1 << i) > n) continue ;

		int temp = fa[x][i] ;
		if (dep[temp] > dep[y]) x = temp ;
	}

	return x ;
}

///

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

///

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 0 ; i < m ; ++i) {
		int x , y ; 
		scanf("%d %d" , &x , &y) ;
		ins(x , y) ; ins(y , x) ;
	}

	///
	
	dep[1] = 1 ; dfs(1 , 1) ;
	for (int j = 1 ; (1 << j) <= n ; ++j)
		for (int i = 1 ; i <= n ; ++i) {
			int k = fa[i][j - 1] ;
			fa[i][j] = fa[k][j - 1] ;
		}

	///
	
	scanf("%d" , &q) ;
	for (int i = 0 ; i < q ; ++i) {
		int ca , a , b , c , d ;
		scanf("%d" , &ca) ;

		if (ca == 1) {
			scanf("%d %d %d %d" , &a , &b , &c , &d) ;
			if (abs(dep[c] - dep[d]) > 1) {printf("yes\n") ; continue ;}

			if (dep[c] > dep[d]) std::swap(c , d) ;
			int la = GetLca(a , d) , lb = GetLca(b , d) ;
			if (lb == d) {std::swap(a , b) ; std::swap(la , lb) ;}

			if (la != d) printf("yes\n") ;
			else if (lb != d) {
				if (low[d] <= dfn[c]) printf("yes\n") ;
				else printf("no\n") ;
			}
			else printf("yes\n") ;
		}
		else {
			scanf("%d %d %d" , &a , &b , &c) ;

			int la = GetLca(a , c) , lb = GetLca(b , c) ;
			if (lb == c) {std::swap(a , b) ; std::swap(la , lb) ;}

			if (la != c) printf("yes\n") ;
			else if (lb != c) {
				int ta = Jump(a , c) ;
				if (low[ta] < dfn[c]) printf("yes\n") ;
				else printf("no\n") ;
			}
			else {
				int ta = Jump(a , c) , tb = Jump(b , c) , f = GetLca(a , b) ;
				if (f != c) printf("yes\n") ;
				else if (low[ta] < dfn[c] && low[tb] < dfn[c]) printf("yes\n") ;
				else printf("no\n") ;
			}	
		}
	}

	return 0 ;
}
