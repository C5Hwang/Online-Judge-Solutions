#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 5e5 + 10 , lgN = 20 + 3 ;

struct Link {
	int num ;
	Link *next ;
}list[MAX_N << 1] ;

Link *head[MAX_N] ;
ll BIT[MAX_N] , a[MAX_N] ;
int f[MAX_N][lgN] , dep[MAX_N] ;
int n , m , cur , st[MAX_N] , ed[MAX_N] ;

int lowbit(int x) {return x & (-x) ;}

ll find(int x) {
	ll sum = 0 ;
	for (; x ; x -= lowbit(x)) sum ^= BIT[x] ;

	return sum ;
}

void change(int x , ll a) {
	for (; x <= n ; x += lowbit(x)) BIT[x] ^= a ;
}

void update(int u , int v , ll a) {
	change(u , a) ; change(v + 1 , a) ;
}

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

int lca(int x , int y) {
	if (dep[x] < dep[y]) std::swap(x , y) ;

	for (int i = 20 ; i >= 0 ; --i) {
		if ((1 << i) > n) continue ;

		int tmp = f[x][i] ;
		if (dep[tmp] >= dep[y]) x = tmp ;
	}

	if (x == y) return x ;

	for (int i = 20 ; i >= 0 ; --i) {
		if ((1 << i) > n) continue ;

		int tx = f[x][i] , ty = f[y][i] ;
		if (tx != ty) x = tx , y = ty ;
	}

	return f[x][0] ;
}

void dfs(int x , int fa) {
	st[x] = ++m ;
	f[x][0] = fa ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa) continue ;

		dep[nx] = dep[x] + 1 ; dfs(nx , x) ;
	}

	ed[x] = m ;
}

int main() {
	scanf("%d" , &n) ;
	for (int i = 1 ; i <= n ; ++i) scanf("%lld" , &a[i]) ;
	for (int i = 1 ; i < n ; ++i) {
		int u , v ; scanf("%d %d" , &u , &v) ;
		ins(u , v) ; ins(v , u) ;
	}

	///

	dep[1] = 1 ; dfs(1 , 1) ;

	for (int j = 1 ; (1 << j) <= n ; ++j)
		for (int i = 1 ; i <= n ; ++i) f[i][j] = f[f[i][j - 1]][j - 1] ;

	for (int i = 1 ; i <= n ; ++i) update(st[i] , ed[i] , a[i]) ;

	///

	int Q ; scanf("%d" , &Q) ;
	for (; Q-- ;) {
		char op[2] ; int u , v ;
		scanf("%s %d %d" , op , &u , &v) ;

		if (op[0] == 'Q') {
			ll tu = find(st[u]) , tv = find(st[v]) , t = a[lca(u , v)] ;
			ll res = tu ^ tv ^ t ;

			if (res) printf("Yes\n") ;
			else printf("No\n") ;
		}
		else {
			update(st[u] , ed[u] , a[u] ^ v) ;
			a[u] = v ;
		}
	}

	return 0 ;
}