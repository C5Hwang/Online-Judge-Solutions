#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 2e5 + 10 , MAX_K = 1e6 + 10 ;

struct Link {
	int num , val ;
	Link *next ;
}list[MAX_N << 1] ;

bool vis[MAX_N] ;
Link *head[MAX_N] ;
int n , k , root , msiz , tot , cur , ans , siz[MAX_N] , dis[MAX_K] ;

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

void update(int x , int fa , int d , int dep , int ty) {
	if (d <= k) {
		if (!ty) ans = std::min(ans , dis[k - d] + dep) ;
		else if (ty == 1) dis[d] = std::min(dis[d] , dep) ;
		else if (d) dis[d] = n ;
	}

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa || vis[nx]) continue ;

		if (d > k) update(nx , x , d , dep + 1 , ty) ;
		else update(nx , x , d + h->val , dep + 1 , ty) ;
	}
}

void work(int x) {
	vis[x] = 1 ;

	for (Link *h = head[x] ; h ; h = h->next)
		if (!vis[h->num]) {
			update(h->num , h->num , h->val , 1 , 0) ;
			update(h->num , h->num , h->val , 1 , 1) ;
		}
	for (Link *h = head[x] ; h ; h = h->next)
		if (!vis[h->num]) update(h->num , h->num , h->val , 1 , 2) ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (vis[nx]) continue ;

		root = -1 ; msiz = n ; tot = siz[nx] ;
		findroot(nx , nx) ;	work(root) ;
	}
}

int main() {
	scanf("%d %d" , &n , &k) ;
	if (!k) ans = 0 ;

	for (int i = 1 ; i < n ; ++i) {
		int x , y , v ;
		scanf("%d %d %d" , &x , &y , &v) ;

		ins(x , y , v) ; ins(y , x , v) ;
	}

	///

	for (int i = 1 ; i <= k ; ++i) dis[i] = n ;

	root = -1 ; msiz = tot = ans = n ;
	findroot(0 , 0) ; work(root) ;

	if (ans == n) printf("-1\n") ;
	else printf("%d\n" , ans) ;

	return 0 ;
}