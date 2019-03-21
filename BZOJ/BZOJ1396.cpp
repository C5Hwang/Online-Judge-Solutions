#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 ;

struct Node {
	int len , pl , cnt ;
	Node *ch[26] , *fail ;
}sam[MAX_N << 1] ;
struct Link {
	Node *p ;
	Link *next ;
}list[MAX_N << 1] ;

Node *last ;
char s[MAX_N] ;
Link *head[MAX_N] ;
int n , tot , cur , tre[2][MAX_N << 2] ;

void extend(int c , int idx) {
	Node *cur = &sam[tot++] , *p = last ;
	cur->len = last->len + 1 ; cur->pl = idx ; cur->cnt = 1 ;

	for (; p && !p->ch[c] ; p = p->fail) p->ch[c] = cur ;
	if (!p) cur->fail = &sam[0] ;
	else {
		Node *q = p->ch[c] ;

		if (p->len + 1 == q->len) cur->fail = q ;
		else {
			Node *clone = &sam[tot++] ;
			*clone = *q ; clone->len = p->len + 1 ;
			clone->cnt = 0 ; clone->pl = n << 1 ;

			for (; p && p->ch[c] == q ; p = p->fail) p->ch[c] = clone ;
			q->fail = cur->fail	= clone ;
		}
	}
	last = cur ;
}

void ins(int x , Node *y) {
	list[cur].p = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

void build(int t , int x , int y) {
	tre[0][t] = n << 1 ; tre[1][t] = n ;
	if (x == y) return ;

	int mid = (x + y) >> 1 ;
	build(t << 1 , x , mid) ; build(t << 1 | 1 , mid + 1 , y) ;
}

void modify(int ty , int t , int x , int y , int fx , int fy , int a) {
	if (y < fx || fy < x) return ;
	if (fx <= x && y <= fy) {tre[ty][t] = std::min(tre[ty][t] , a) ; return ;}

	int mid = (x + y) >> 1 ;
	modify(ty , t << 1 , x , mid , fx , fy , a) ;
	modify(ty , t << 1 | 1 , mid + 1 , y , fx , fy , a) ;
}

int find(int ty , int t , int x , int y , int f) {
	if (x == y) return tre[ty][t] ;

	int mid = (x + y) >> 1 ;
	if (f <= mid) return std::min(tre[ty][t] , find(ty , t << 1 , x , mid , f)) ;
	else return std::min(tre[ty][t] , find(ty , t << 1 | 1 , mid + 1 , y , f)) ;
}

int main() {
	scanf("%s" , s) ; n = strlen(s) ;

	last = &sam[tot++] ;
	for (int i = 0 ; i < n ; ++i) extend(s[i] - 'a' , i) ;

	///

	for (int i = 0 ; i < tot ; ++i) ins(sam[i].len , &sam[i]) ;
	for (int l = n ; l ; --l)
		for (Link *h = head[l] ; h ; h = h->next) h->p->fail->cnt += h->p->cnt ;

	build(1 , 0 , n - 1) ;
	Node *p = &sam[0] ;
	for (int i = 0 ; i < n ; ++i) {
		int c = s[i] - 'a' ; p = p->ch[c] ;

		if (p->cnt == 1) {
			int L = p->pl - p->len + 1 , R = p->pl - p->fail->len ;

			modify(0 , 1 , 0 , n - 1 , L , R , p->pl) ;
			modify(1 , 1 , 0 , n - 1 , R , p->pl , p->fail->len + 1) ;
		}
	}

	for (int i = 0 ; i < n ; ++i) {
		int s1 = find(0 , 1 , 0 , n - 1 , i) - i + 1 , s2 = find(1 , 1 , 0 , n - 1 , i) ;

		printf("%d\n" , std::min(s1 , s2)) ;
	}

	return 0 ;
}