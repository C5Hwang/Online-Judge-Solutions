#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 5e3 + 10 , MAX_M = 2e5 + 10 ;

struct Edge {
	int x , y , v ;
}eg[MAX_M] ;

int n , m , fa[MAX_N] ;

int findset(int x) {return fa[x] == x ? x : (fa[x] = findset(fa[x])) ;}

bool cmp(Edge a , Edge b) {return a.v < b.v ;}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 0 ; i < m ; ++i)
		scanf("%d %d %d" , &eg[i].x , &eg[i].y , &eg[i].v) ;

	///

	std::sort(eg + 0 , eg + m , cmp) ;
	for (int i = 1 ; i <= n ; ++i) fa[i] = i ;

	int ans = 0 , tot = 0 ;
	for (int i = 0 ; i < m ; ++i) {
		Edge *p = &eg[i] ;
		int fx = findset(p->x) , fy = findset(p->y) ;

		if (fx == fy) continue ;
		ans += p->v ; ++tot ; fa[fx] = fy ;
	}

	if (tot < n - 1) printf("orz\n") ;
	else printf("%d\n" , ans) ;

	return 0 ;
}
