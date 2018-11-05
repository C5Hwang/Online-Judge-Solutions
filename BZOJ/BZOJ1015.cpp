#include <stdio.h>
#include <stdlib.h>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 4e5 + 10 ;

struct Link {
	int num ;
	Link *next ;
}list[MAX_N] ;
struct Edge {
	int x , y ;
}eg[MAX_N] ;

bool flag[MAX_N] ;
Link *head[MAX_N] ;
int n , m , q , cur , tot , ans[MAX_N] , del[MAX_N] , fa[MAX_N] ;

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

int findroot(int x) {return fa[x] == -1 ? x : (fa[x] = findroot(fa[x])) ;}

void merge(int x , int y) {
	if (flag[x] || flag[y]) return ;

	int fx = findroot(x) , fy = findroot(y) ;
	if (fx == fy) return ;

	--tot ; fa[fx] = fy ;
}

int main() {
	n = read() ; m = read() ;
	for (int i = 0 ; i < m ; ++i) {
		int a , b ; a = read() ; b = read() ;

		ins(a , b) ; ins(b , a) ;
		eg[i] = (Edge){a , b} ;
	}

	q = read() ;
	for (int i = 1 ; i <= q ; ++i) del[i] = read() , flag[del[i]] = 1 ;

	///

	for (int i = 0 ; i < n ; ++i) fa[i] = -1 ;

	tot = n - q ;
	for (int i = 0 ; i < m ; ++i) {
		Edge *p = &eg[i] ;
		merge(p->x , p->y) ;
	}

	ans[q] = tot ;
	for (int i = q ; i ; --i) {
		int x = del[i] ; ++tot ;

		flag[x] = 0 ;
		for (Link *h = head[x] ; h ; h = h->next) merge(x , h->num) ;
		ans[i - 1] = tot ;
	}

	for (int i = 0 ; i <= q ; ++i) printf("%d\n" , ans[i]) ;

	return 0 ;
}