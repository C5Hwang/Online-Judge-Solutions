#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAX_N = 500 + 10 ;

struct Link {
	int num ;
	Link *next ;
}list[MAX_N * MAX_N] ;
struct Query {
	char cd1 , cd2 ;
	int n1 , n2 ;
}cat[MAX_N] , dog[MAX_N] ;

bool T[MAX_N] ;
Link *head[MAX_N] ;
int n , m , t , cur , c1 , c2 , left[MAX_N] ;

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

void init() {
	cur = c1 = c2 = 0 ;
	memset(head , 0 , sizeof(head)) ;
	memset(left , 0 , sizeof(left)) ;
}

int match(int x) {
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (T[nx]) continue ;

		T[nx] = 1 ;
		if (!left[nx] || match(left[nx])) {left[nx] = x ; return 1 ;}
	}

	return 0 ;
}

int main() {
	int Q ; scanf("%d" , &Q) ;
	while (Q--) {
		init() ;

		scanf("%d %d %d" , &n , &m , &t) ;
		for (int i = 1 ; i <= t ; ++i) {
			getchar() ; char cd ;
			scanf("%c" , &cd) ;

			if (cd == 'C') cat[++c1].cd1 = cd , scanf("%d %c%d" , &cat[c1].n1 , &cat[c1].cd2 , &cat[c1].n2) ;
			else dog[++c2].cd1 = cd , scanf("%d %c%d" , &dog[c2].n1 , &dog[c2].cd2 , &dog[c2].n2) ;
		}

		for (int i = 1 ; i <= c1 ; ++i)
			for (int j = 1 ; j <= c2 ; ++j)
				if (cat[i].cd1 == dog[j].cd2 && cat[i].n1 == dog[j].n2) ins(i , j) ;
				else if (cat[i].cd2 == dog[j].cd1 && cat[i].n2 == dog[j].n1) ins(i , j) ;

		///
		
		int res = 0 ;
		for (int i = 1 ; i <= c1 ; ++i) {
			for (int j = 1 ; j <= c2 ; ++j) T[j] = 0 ;

			if (match(i)) ++res ;
		}

		printf("%d\n" , t - res) ;
	}

	return 0 ;
}
