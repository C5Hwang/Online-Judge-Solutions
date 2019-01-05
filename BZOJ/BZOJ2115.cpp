#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 5e4 + 10 , MAX_M = 1e5 + 10 ;

struct Link {
	bool use ;
	int num ; ll val ;
	Link *next , *reg ;
}list[MAX_M << 1] ;

bool ap[MAX_N] ;
Link *head[MAX_N] ;
int n , m , cur , tot , BASE ;
ll ans , xr[MAX_N] , a[MAX_M << 1] , b[MAX_M << 1] ;

void ins(int x , int y , ll v) {
	list[cur].use = 0 ;
	list[cur].num = y ;
	list[cur].val = v ;
	list[cur].next = head[x] ;
	list[cur].reg = &list[cur^1] ;
	head[x] = &list[cur++] ;
}

void dfs(int x) {
	ap[x] = 1 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (ap[nx]) continue ;

		h->use = h->reg->use = 1 ;
		xr[nx] = xr[x] ^ h->val ;
		dfs(nx) ;
	}
}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 0 ; i < m ; ++i) {
		int x , y ; ll v ;
		scanf("%d %d %lld" , &x , &y , &v) ;
		ins(x , y , v) ; ins(y , x , v) ;
	}

	///

	xr[1] = 0 ; dfs(1) ;
	for (int x = 1 ; x <= n ; ++x)
		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (h->use) continue ;

			a[tot++] = xr[x] ^ xr[nx] ^ h->val ;
		}

	///

	BASE = 60 ;
	for (int i = 0 ; i < tot ; ++i)
		for (int j = BASE ; j >= 0 ; --j)
			if (a[i] & (1LL << j)) {
				if (b[j]) a[i] ^= b[j] ;
				else {
					b[j] = a[i] ;
					for (int k = j - 1 ; k >= 0 ; --k) if (b[j] & (1LL << k)) b[j] ^= b[k] ;
					for (int k = BASE ; k > j ; --k) if (b[k] & (1LL << j)) b[k] ^= b[j] ;
					break ;
				}
			}

	ans = xr[n] ;
	for (int j = BASE ; j >= 0 ; --j)
		if (!(ans & (1LL << j))) ans ^= b[j] ;

	printf("%lld\n" , ans) ;

	return 0 ;
}