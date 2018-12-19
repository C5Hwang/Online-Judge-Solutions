#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e4 + 10 , MAX_P = 100 + 10 , MAX_L = 1e6 + 10 ;

struct Link {
	int num , val ;
	Link *next ;
}list[MAX_N << 1] ;

Link *head[MAX_N] ;
bool ans[MAX_P] , ap[MAX_L] , vis[MAX_N] ;
int n , m , root , msiz , tot , cur , mL , qry[MAX_P] , siz[MAX_N] ;

void ins(int x , int y , int v) {
	list[cur].num = y ;
	list[cur].val = v ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

void findroot(int x , int fa) {
	int mx = 0 ; siz[x] = 1 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa || vis[nx]) continue ;

		findroot(nx , x) ;
		siz[x] += siz[nx] ; mx = std::max(mx , siz[nx]) ;
	}
	mx = std::max(mx , tot - siz[x]) ;

	if (mx < msiz) msiz = mx , root = x ;
}

void update(int x , int fa , int d , int ty) {
	if (d <= mL) {
		if (!ty) for (int i = 0 ; i < m ; ++i) {if (qry[i] >= d) ans[i] |= ap[qry[i] - d] ;}
		else if (ty == 1) ap[d] = 1 ;
		else if (d > 0) ap[d] = 0 ;
	}
	else return ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa || vis[nx]) continue ;

		update(nx , x , d + h->val , ty) ;
	}
}

void work(int x) {
	vis[x] = 1 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (vis[nx]) continue ;

		update(nx , nx , h->val , 0) ;
		update(nx , nx , h->val , 1) ;
	}

	for (Link *h = head[x] ; h ; h = h->next)
		if (!vis[h->num]) update(h->num , h->num , h->val , 2) ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (vis[nx]) continue ;

		root = 0 ; msiz = tot = siz[nx] ;
		findroot(nx , nx) ;

		work(root) ;
	}
}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 1 ; i < n ; ++i) {
		int x , y , v ;
		scanf("%d %d %d" , &x , &y , &v) ;

		ins(x , y , v) ; ins(y , x , v) ;
	}

	for (int i = 0 ; i < m ; ++i) scanf("%d" , &qry[i]) , mL = std::max(mL , qry[i]) ;

	///

	root = 0 ; msiz = tot = n ;
	findroot(1 , 1) ;

	ap[0] = 1 ; work(root) ;

	for (int i = 0 ; i < m ; ++i)
		if (ans[i] || !qry[i]) printf("Yes\n") ;
		else printf("No\n") ;

	return 0 ;
}