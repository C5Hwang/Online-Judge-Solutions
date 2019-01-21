#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e4 + 10 , MAX_M = 2e4 + 10 ;

struct Link {
	int num ;
	Link *next ;
}list[MAX_M << 1] ;

Link *head[MAX_N] ;
bool ans , pt[MAX_N] ;
int T , n , m , cur , tot , len[2] , cir[2][MAX_N] , dep[MAX_N] , fa[MAX_N] , col[MAX_N] ;

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

void init() {
	ans = 1 ; cur = tot = 0 ;
	memset(pt , 0 , sizeof(pt)) ;
	memset(col , 0 , sizeof(col)) ;
	memset(dep , 0 , sizeof(dep)) ;
	memset(head , 0 , sizeof(head)) ;
}

void dfs(int x , int f) {
	fa[x] = f ;
	for (Link *h = head[x] ; h && ans ; h = h->next) {
		int nx = h->num ;
		if (nx == f) continue ;

		if (!dep[nx]) {
			dep[nx] = dep[x] + 1 ; col[nx] = col[x] ^ 1 ;
			dfs(nx , x) ;
		}
		else if (dep[nx] < dep[x]) {
			if (tot == 2) {ans = 0 ; return ;}
			if (col[nx] == col[x]) {ans = 0 ; return ;}

			for (int i = x ; i != nx ; i = fa[i]) cir[tot][len[tot]++] = i ;
			cir[tot][len[tot]++] = nx ; ++tot ;
		}
	}
}

int main() {
	scanf("%d" , &T) ;
	for (; T-- ;) {
		init() ;

		scanf("%d %d" , &n , &m) ;
		for (int i = 0 ; i < m ; ++i) {
			int x , y ;
			scanf("%d %d" , &x , &y) ;
			ins(x , y) ; ins(y , x) ;
		}

		///

		for (int i = 1 ; i <= n && ans ; ++i)
			if (!dep[i]) {
				dep[1] = 1 ; tot = len[0] = len[1] = 0 ;
				dfs(1 , 1) ;

				if (ans && tot > 1) {
					int p = len[0] > len[1] ? 1 : 0 , cnt = 0 ;
					for (int i = 0 ; i < len[p^1] ; ++i) pt[cir[p^1][i]] = 1 ;
					for (int i = 0 ; i < len[p] ; ++i) if (!pt[cir[p][i]]) ++cnt ;

					if (!(cnt == 1 && (len[p] == 4 || len[p^1] == len[p]))) ans = 0 ;
				}
			}

		if (ans) printf("YES\n") ;
		else printf("NO\n") ;
	}

	return 0 ;
}