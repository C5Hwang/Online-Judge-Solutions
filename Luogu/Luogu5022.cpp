#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 5e3 + 10 ;

struct Link {
	int num ;
	Link *next ;
}list[MAX_N << 1] ;
struct Edge {
	int x , y ;
}eg[MAX_N << 1] ;

bool flag[MAX_N] ;
Link *head[MAX_N] ;
int n , m , o , tot , len , cur , x1 , y1 , cir[MAX_N] , sta[MAX_N] , ans[MAX_N] , tmp[MAX_N] ;

bool cmp(Edge a , Edge b) {
	return a.y > b.y ;
}

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

bool find(int x , int fa) {
	flag[x] = 1 ;
	sta[++o] = x ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa) continue ;

		if (flag[nx]) {
			for (; sta[o] != nx ;) cir[len++] = sta[o--] ;
			cir[len++] = nx ; cir[len++] = x ;

			return 1 ;
		}

		if (find(nx , x)) return 1 ;
	}

	--o ; flag[x] = 0 ;
	return 0 ;
}

void dfs(int x , int fa) {
	tmp[o++] = x ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa) continue ;
		if ((x == x1 && nx == y1) || (x == y1 && nx == x1)) continue ;

		dfs(nx , x) ;
	}
}

void update() {
	bool ok = 1 ;
	for (int i = 0 ; i < n && ok ; ++i)
		if (tmp[i] > ans[i]) {ok = 0 ; break ;}
		else if (ans[i] > tmp[i]) {ok = 1 ; break ;}

	if (ok) for (int i = 0 ; i < n ; ++i) ans[i] = tmp[i] ;
}

int main() {
	n = read() ; m = read() ;
	for (int i = 0 ; i < m ; ++i) {
		int x , y ; x = read() ; y = read() ;

		eg[tot++] = (Edge){x , y} ; eg[tot++] = (Edge){y , x} ;
	}

	///

	std::sort(eg + 0 , eg + tot , cmp) ;

	for (int i = 0 ; i < tot ; ++i) {
		Edge *p = &eg[i] ;
		ins(p->x , p->y) ;
	}

	///

	for (int i = 0 ; i < n ; ++i) ans[i] = n + 1 ;

	if (n != m) {
		o = 0 ; dfs(1 , 1) ;
		update() ;
	}
	else {
		find(1 , 1) ;

		for (int i = 0 ; i < len - 1 ; ++i) {
			x1 = cir[i] ; y1 = cir[i + 1] ;
			o = 0 ; dfs(1 , 1) ; update() ;
		}
	}

	for (int i = 0 ; i < n ; ++i) printf("%d " , ans[i]) ;
	printf("\n") ;

	return 0 ;
}