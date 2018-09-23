#include <stdio.h>
#include <stdlib.h>

const int MAX_N = 1000 + 10 ;

struct Link {
	int num ;
	Link *next ;
}list[2 * MAX_N] ;

bool T[MAX_N] ;
Link *head[MAX_N] ;
int n , m , cur , left[MAX_N] ;

bool match(int x) {
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (T[nx]) continue ;
		T[nx] = 1 ;

		if (!left[nx] || match(left[nx])) {
			left[nx] = x ;
			return 1 ;
		}
	}

	return 0 ;
}

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 1 ; i <= m ; ++i) {
		int x , y ;
		scanf("%d %d" , &x , &y) ; ++x ; ++y ;

		ins(i , x) ; ins(i , y) ;
	}

	///
	
	int res = 0 ;
	for (int i = 1 ; i <= m ; ++i) {
		for (int j = 1 ; j <= n ; ++j) T[j] = 0 ;
		if (match(i)) ++res ; else break;
	}

	printf("%d\n" , res) ;

	return 0 ;
}
