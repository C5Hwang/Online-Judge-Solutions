#include <stdio.h>
#include <stdlib.h>

const int MAX_N = 1000 + 10 , MAX_E = 1000000 + 10 ;

struct Link {
	int num ;
	Link *next ;
}list[MAX_E] ;

bool T[MAX_E] ;
Link *head[MAX_E] ;
int n , m , e , cur , left[MAX_N] ;

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

bool match(int x) {
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (T[nx]) continue ;

		T[nx] = 1 ;
		if (!left[nx] || match(left[nx])) {left[nx] = x ; return 1 ;}
	}

	return 0 ;
}

int main() {
	scanf("%d %d %d" , &n , &m , &e) ;
	for (int i = 0 ; i < e ; ++i) {
		int x , y ;
		scanf("%d %d" , &x , &y) ;
		if (x > n || y > m) continue ;
		ins(x , y) ;
	}

	///
	
	int res = 0 ;
	for (int i = 1 ; i <= n ; ++i) {
		for (int j = 1 ; j <= m ; ++j) T[j] = 0 ;

		if (match(i)) ++res ;
	}

	printf("%d\n" , res) ;

	return 0 ;
}
