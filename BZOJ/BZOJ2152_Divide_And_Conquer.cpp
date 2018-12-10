#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 2e4 + 10 ;

struct Link {
	int num , val ;
	Link *next ;
}list[MAX_N << 1] ;

bool vis[MAX_N] ;
Link *head[MAX_N] ;
int n , cur , root , ms , ans , siz[MAX_N] , cnt[3] ;

int gcd(int x , int y) {return y ? gcd(y , x % y) : x ;}

void ins(int x , int y , int v) {
	list[cur].num = y ;
	list[cur].val = v ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

void getroot(int x , int fa , int sum) {
	int tmp = 0 ; siz[x] = 1 ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (vis[nx] || nx == fa) continue ;

		getroot(nx , x , sum) ;
		siz[x] += siz[nx] ; tmp = std::max(tmp , siz[nx]) ;
	}

	tmp = std::max(sum - siz[x] , tmp) ;

	if (ms > tmp) ms = tmp , root = x ;
}

void dfs(int x , int fa , int d) {
	++cnt[d] ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa || vis[nx]) continue ;

		dfs(nx , x , (d + h->val) % 3) ;
	}
}

int count(int x , int d) {
	cnt[0] = cnt[1] = cnt[2] = 0 ;
	dfs(x , x , d) ;

	return cnt[0] * cnt[0] + ((cnt[1] * cnt[2]) << 1) ;
}

void work(int x) {
	vis[x] = 1 ;
	ans += count(x , 0) ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (vis[nx]) continue ;

		ans -= count(nx , h->val % 3) ;
		root = 0 ; ms = n ;
		getroot(nx , nx , siz[nx]) ; work(root) ;
	}
}

int main() {
	scanf("%d" , &n) ;
	for (int i = 1 ; i < n ; ++i) {
		int x , y , v ;
		scanf("%d %d %d" , &x , &y , &v) ;

		ins(x , y , v) ; ins(y , x , v) ;
	}

	///

	ms = n ; root = -1 ;
	getroot(1 , 1 , n) ; work(root) ;

	int d = gcd(ans , n * n) ;
	printf("%d/%d\n" , ans / d , n * n / d) ;

	return 0 ;
}