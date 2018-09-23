#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 1e6 + 10 ;

struct Link {
	int num ;
	Link *next ;
}list[2 * MAX_N] ;
struct Edge {
	int x , y , l ;
}ed[MAX_N] ;

Link *head[MAX_N] ;
int n , cur , dep[MAX_N] , siz[MAX_N] ;

void dfs(int x , int fa) {
	siz[x] = 1 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa) continue ;

		dep[nx] = dep[x] + 1 ;
		dfs(nx , x) ; siz[x] += siz[nx] ;
	}
}

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

int main() {
	scanf("%d" , &n) ;
	for (int i = 1 ; i < n ; ++i) {
		int a , b , v ;
		scanf("%d %d %d" , &a , &b , &v) ;
		ins(a , b) ; ins(b , a) ;
		ed[i].x = a ; ed[i].y = b ; ed[i].l = v ;
	}

	///
	
	dfs(1 , 1) ;

	long long res = 0 ;
	for (int i = 1 ; i < n ; ++i) {
		int a = ed[i].x , b = ed[i].y ;
		if (dep[a] > dep[b]) std::swap(a , b) ;

		res += abs(siz[b] * 2 - n) * (long long)ed[i].l ;
	}
	printf("%lld\n" , res) ;

	return 0 ;
}
