#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std ;

const int MAX_N = 30000 + 10 , lgN = 20 ;

struct Link {
	int num ;
	Link *next ;
}list[2 * MAX_N] ;

bool ap[MAX_N] ;
Link *head[MAX_N] ;
int n , cur , dep[MAX_N] , f[MAX_N][lgN] ;

void dfs(int t , int fa) {
	Link *h = head[t] ; dep[t] = dep[fa] + 1 ; f[t][0] = fa; 
	for (; h ; h = h->next) {
		int nt = h->num ;

		if (nt == fa) continue ;

		dfs(nt , t) ;
	}
}

int lca(int x , int y) {
	if (dep[x] > dep[y]) swap(x , y) ;

	for (int i = lgN - 1 ; i >= 0 ; --i) {
		int fa = f[y][i] ;
		if (dep[fa] < dep[x]) continue ;

		y = fa ;
	}

	if (x == y) return x ;

	for (int i = lgN - 1 ; i >= 0 ; --i) {
		int f1 = f[x][i] , f2 = f[y][i] ;

		if (f1 == f2) continue ;

		x = f1 ; y = f2 ;
	}

	return f[x][0] ;
}

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

int main() {
	int Q ;
	scanf("%d" , &Q) ;

	while (Q--) {
		cur = 0 ; n = 0 ;
		memset(f , 0 , sizeof(f)) ;
		memset(ap , 0 , sizeof(ap)) ;
		memset(head , 0 , sizeof(head)) ;

		scanf("%d" , &n) ;
		for (int i = 1 ; i < n ; ++i) {
			int x , y ;
			scanf("%d %d" , &x , &y) ;

			ins(x , y) ; ap[y] = 1 ;
		}

		///
		
		for (int i = 1 ; i <= n ; ++i)
			if (!ap[i]) {dfs(i , 0) ; break ;}
		for (int j = 1 ; j < lgN ; ++j)
			for (int i = 1 ; i <= n ; ++i)
				f[i][j] = f[f[i][j - 1]][j - 1] ;

		///

		int x , y ;
		scanf("%d %d" , &x , &y) ;
		printf("%d\n" , lca(x , y)) ;
	}

	return 0 ;
}
