#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 1000000 + 10 ;

struct Link {
	int num ; Link *next ;
}list[2 * MAX_N] ;

Link *head[MAX_N] ;
int n , a , id , cur , T[MAX_N] , left[MAX_N] ;

bool match(int x) {
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (T[nx] == id) continue ;

		T[nx] = id ;
		if (!left[nx] || match(left[nx])) {left[nx] = x ; return 1 ;}
	}

	return 0 ;
}

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

int main() {
	scanf("%d" , &n) ; a = 1 ;
	for (int i = 0 ; i < n ; ++i) {
		int x , y ;
		scanf("%d %d" , &x , &y) ;
		ins(x , i) ; ins(y , i) ;
		a = std::max(a , std::max(x , y)) ;
	}
	a = std::min(a , n) ;

	///
	
	int res = 0 ;
	for (int i = 1 ; i <= a ; ++i) {
		++id ;

		if (match(i)) ++res ;
		else break ;
	}

	printf("%d\n" , res) ;

	return 0 ;
}
