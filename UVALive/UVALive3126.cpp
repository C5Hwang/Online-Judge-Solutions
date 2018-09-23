#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAX_N = 500 + 10 ;

struct Link {
	int num ;
	Link *next ;
}list[MAX_N * MAX_N] ;
struct Query {
	int hour , minute , x1 , y1 , x2 , y2 ;
}que[MAX_N] ;

bool T[MAX_N] ;
Link *head[MAX_N] ;
int n , cur , left[MAX_N] ;

bool check(int x , int y) {
	int cost = abs(que[x].x1 - que[x].x2) + abs(que[x].y1 - que[x].y2) + abs(que[x].x2 - que[y].x1) + abs(que[x].y2 - que[y].y1) ;

	int hx = que[x].hour , mx = que[x].minute ,
	    hy = que[y].hour , my = que[y].minute ;

	mx += cost ; hx += (mx / 60) ; mx %= 60 ;

	if (hx > hy) return 0 ;
	else if (hx == hy && mx >= my) return 0 ;
	else return 1 ;
}

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
		for (int i = 1 ; i <= n ; ++i) {
			int h , m , x1 , y1 , x2 , y2 ;
			scanf("%d:%d %d %d %d %d" , &h , &m , &x1 , &y1 , &x2 , &y2) ;

			que[i].hour = h ; que[i].minute = m ;
			que[i].x1 = x1 ; que[i].y1 = y1 ; que[i].x2 = x2 ; que[i].y2 = y2 ;
		}
		for (int i = 1 ; i <= n ; ++i)
			for (int j = 1 ; j <= n ; ++j)
				if (i != j && check(i , j)) ins(i , j) ;

		///

		int res = 0 ;
		for (int i = 1 ; i <= n ; ++i) {
			for (int j = 1 ; j <= n ; ++j) T[j] = 0 ;

			if (match(i)) ++res ;
		}

		printf("%d\n" , n - res) ;
	}

	return 0 ;
}
