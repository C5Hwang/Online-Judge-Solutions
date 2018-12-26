#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 ;

struct Link {
	int num , val ;
	Link *next ;
}list[MAX_N << 1] ;

ll ans ;
bool vis[MAX_N] ;
Link *head[MAX_N] ;
int n , root , msiz , tot , cur , siz[MAX_N] , dis[MAX_N << 1] , cnt[2][MAX_N << 1] ;

void findroot(int x , int fa) {
	int mx = 0 ; siz[x] = 1 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa || vis[nx]) continue ;

		findroot(nx , x) ;
		siz[x] += siz[nx] ; mx = std::max(mx , siz[nx]) ;
	}
	mx = std::max(mx , tot - siz[x]) ;

	if (msiz > mx) msiz = mx , root = x ;
}

void ins(int x , int y , int v) {
	list[cur].num = y ;
	list[cur].val = v ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

void update(int x , int fa , int d , int ty) {
	++dis[d + n] ;
	int t = dis[d + n] > 1 ? 1 : 0 ;

	if (ty == 0) {
		if (t) ans += cnt[0][-d + n] + cnt[1][-d + n] ;
		else ans += cnt[1][-d + n] ;
	}
	else {
		if (!d) t = 1 ;
		if (ty == 1) ++cnt[t][d + n] ;
		else cnt[t][d + n] = 0 ;
	}

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa || vis[nx]) continue ;

		update(nx , x , d + h->val , ty) ;
	}

	--dis[d + n] ;
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
		findroot(nx , nx) ;	work(root) ;
	}
}

int main() {
	scanf("%d" , &n) ;
	for (int i = 1 ; i < n ; ++i) {
		int x , y , v ;
		scanf("%d %d %d" , &x , &y , &v) ;

		if (!v) v = -1 ;
		ins(x , y , v) ; ins(y , x , v) ;
	}

	///

	root = 0 ; msiz = tot = n ;
	findroot(1 , 1) ;

	cnt[0][n] = 1 ; work(root) ;

	printf("%lld\n" , ans) ;

	return 0 ;
}