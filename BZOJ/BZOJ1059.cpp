#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAX_N = 200 + 10 ;

struct Link {
	int num ;
	Link *next ;
}list[MAX_N * MAX_N] ;

bool T[MAX_N] ;
Link *head[MAX_N] ;
int n , cur , left[MAX_N] ;

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

void init() {
	cur = 0 ;
	memset(head , 0 , sizeof(head)) ;
	memset(left , 0 , sizeof(left)) ;
}

int main() {
	int Q ; scanf("%d" , &Q) ;
	while (Q--) {
		init() ;
		
		scanf("%d" , &n) ;
		for (int i = 1 ; i <= n ; ++i)
			for (int j = 1 ; j <= n ; ++j) {
				int num ; scanf("%d" , &num) ;

				if (num) ins(i , j) ;
			}

		///

		int res = 0 ;
		for (int i = 1 ; i <= n ; ++i) {
			for (int j = 1 ; j <= n ; ++j) T[j] = 0 ;
			if (match(i)) ++res ;
		}

		if (res == n) printf("Yes\n") ;
		else printf("No\n") ;
	}

	return 0 ;
}
