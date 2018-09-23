#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std ;

const int MAX_N = 40000 + 10 ;

struct Linked_List {
	int num , cost , next ;
}list[2 * MAX_N] ;

bool ap[MAX_N] ;
int Q , n , m , cur , dis[MAX_N] , dep[MAX_N] , fa[MAX_N][20] , head[MAX_N] ;

void dfs(int t) {
	ap[t] = 1 ;
	int h = head[t] ;
	for (; h != -1 ; h = list[h].next) {
		int nt = list[h].num ;
		if (ap[nt]) continue ;
		
		dis[nt] = dis[t] + list[h].cost ;
		dep[nt] = dep[t] + 1 ;
		fa[nt][0] = t ;
		
		dfs(nt) ;
	}
}

int getfather(int x , int y) {
	int MAXd = log(n) / log(2) ;
	
	for (int i = MAXd ; i >= 0 ; --i)
		if (fa[x][i] != fa[y][i]) {
			x = fa[x][i] ; y = fa[y][i] ;
		}
	
	return fa[x][0] ;
}

int lca(int x , int y) {
	if (dep[x] < dep[y]) swap(x , y) ;
	
	int jump = dep[x] - dep[y] , fac = 0 ;
	for (; jump != 0 ; ++fac) {
		if (jump % 2 == 0) {
			jump /= 2 ;
			continue ;
		}
		
		x = fa[x][fac] ;
		jump /= 2 ;
	}
	
	if (x == y) return x ;
	else return getfather(x , y) ;
}

void ins(int x , int y , int v) {
	list[cur].num = y ;
	list[cur].cost = v ;
	list[cur].next = head[x] ;
	head[x] = cur ;
	
	++cur ;
}

int main() {
	scanf("%d" , &Q) ;
	while (Q--) {
		cur = 0 ;
		memset(ap , 0 , sizeof(ap)) ;
		memset(head , -1 , sizeof(head)) ;
		
		scanf("%d %d" , &n ,&m) ;
		for (int i = 1 ; i < n ; ++i) {
			int a , b , v ;
			scanf("%d %d %d" , &a , &b , &v) ;
			
			ins(a , b , v) ;
			ins(b , a , v) ;
		}
		
		///
		
		fa[1][0] = -1 ; dep[1] = 1 ;
		dfs(1) ;
		
		///
		
		int MAXd = log(n) / log(2) ;
		for (int j = 1 ; j <= MAXd ; ++j)
			for (int i = 1 ; i <= n ; ++i) {
				int nf = fa[i][j - 1] ;
				if (nf != -1) fa[i][j] = fa[nf][j - 1] ;
				else fa[i][j] = -1 ;
			}
		
		///
		
		for (int i = 0 ; i < m ; ++i) {
			int a , b ;
			scanf("%d %d" , &a , &b) ;
			
			int l = lca(a , b) ;
			
			printf("%d\n" , dis[a] + dis[b] - 2 * dis[l]) ;
		}
	}
	
	return 0 ;
}
