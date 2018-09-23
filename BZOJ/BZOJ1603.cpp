#include <stdio.h>
#include <stdlib.h>

const int MAX_N = 1e3 + 10 ;

struct Link {
	int num , sta ;
	Link *next ;
}list[MAX_N] ;

Link *head[MAX_N] ;
int n , cur , rot[MAX_N] ;

void ins(int x , int y , int s) {
	list[cur].num = y ;
	list[cur].sta = s ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

void dfs(int x) {
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;

		rot[nx] = rot[x] ^ h->sta ;
		dfs(nx) ;
	}
}

int main() {
	scanf("%d" , &n) ;
	for (int i = 1 ; i < n ; ++i) {
		int x , y , s ;
		scanf("%d %d %d" , &x , &y , &s) ;
		ins(x , y , s) ;
	}

	///
	
	dfs(1) ;

	printf("%d\n" , rot[n]) ;

	return 0 ;
}
