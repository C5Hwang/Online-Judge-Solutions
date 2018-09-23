#include <stdio.h>
#include <stdlib.h>

const int MAX_N = 3e5 + 10 ;

struct Link {
	int num ;
	Link *next ;
}list[MAX_N << 1] ;
struct WithVal {
	int num , idx ;
	WithVal *next ;
}qry[MAX_N << 1] , dif[2][MAX_N << 1] ;
struct Query {
	int x , y , lca ;
}query[MAX_N] ;

///

bool ap[MAX_N] ;
Link *head[MAX_N] ;
WithVal *qh[MAX_N] , *dh[2][MAX_N] ;
int n , m , cur , tot , cnt[2] , w[MAX_N] , ans[MAX_N] ;
int dep[MAX_N] , fa[MAX_N] , front[MAX_N] , k1[MAX_N] , k2[MAX_N] , sum[2][MAX_N << 1] ;

///

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;	
}

void insq(int x , int y , int p) {
	qry[tot].num = y ;
	qry[tot].idx = p ;
	qry[tot].next = qh[x] ;
	qh[x] = &qry[tot++] ;
}

void insdif(int ty , int x , int p , int val) {
	dif[ty][cnt[ty]].num = val ;
	dif[ty][cnt[ty]].idx = p ;
	dif[ty][cnt[ty]].next = dh[ty][x] ;
	dh[ty][x] = &dif[ty][cnt[ty]++] ;
}

///

int findset(int x) {return x == fa[x] ? x : (fa[x] = findset(fa[x])) ;}

void dfs(int x) {
	fa[x] = x ; ap[x] = 1 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (ap[nx]) continue ;
		dep[nx] = dep[x] + 1 ; front[nx] = x ;

		dfs(nx) ; fa[nx] = x ;
	}

	for (WithVal *h = qh[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (ap[nx]) query[h->idx].lca = findset(nx) ;
	}
}

void getans(int x) {
	int s1 = sum[0][k1[x]] + sum[1][k2[x]] ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == front[x]) continue ;
		getans(nx) ;
	}
	for (int i = 0 ; i < 2 ; ++i)
		for (WithVal *h = dh[i][x] ; h ; h = h->next) sum[i][h->idx] += h->num ;

	int s2 = sum[0][k1[x]] + sum[1][k2[x]] ;
	ans[x] = s2 - s1 ;
}

///

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 1 ; i < n ; ++i) {
		int x , y ; scanf("%d %d" , &x , &y) ;
		ins(x , y) ; ins(y , x) ;
	}
	for (int i = 1 ; i <= n ; ++i) scanf("%d" , &w[i]) ;
	for (int i = 0 ; i < m ; ++i) {
		int x , y ; scanf("%d %d" , &x , &y) ;
		insq(x , y , i) ; insq(y , x , i) ;
		query[i] = (Query){x , y , 0} ;
	}

	///
	
	dep[1] = 1 ; front[1] = 0 ; dfs(1) ;
	for (int i = 1 ; i <= n ; ++i)
		k1[i] = dep[i] + w[i] , k2[i] = w[i] - dep[i] + n ;
	for (int i = 0 ; i < m ; ++i) {
		Query *p = &query[i] ;
		int s1 = dep[p->x] , s2 = dep[p->x] - (dep[p->lca] << 1) + n ;

		insdif(0 , p->x , s1 , 1) ; insdif(0 , p->lca , s1 , -1) ;
		insdif(1 , p->y , s2 , 1) ; insdif(1 , front[p->lca] , s2 , -1) ;
	}
	getans(1) ;

	for (int i = 1 ; i <= n ; ++i) printf("%d " , ans[i]) ;
	printf("\n") ;

	return 0 ;
}
