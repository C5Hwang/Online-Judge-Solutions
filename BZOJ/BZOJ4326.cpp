#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 3e5 + 10 , lgN = 20 + 5 ;

struct data {
	int x , y , val ;
}eg[MAX_N] , query[MAX_N] ;
struct Link {
	int num , val ;
	Link *next ;
}list[MAX_N << 1] ;

Link *head[MAX_N] ;
int n , m , cur , a[MAX_N] , pt[MAX_N] , dep[MAX_N] , dis[MAX_N] , f[MAX_N][lgN] ;

///

bool cmp(data a , data b) {return a.val < b.val ;}

void dfs(int x) {
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == f[x][0]) continue ;

		f[nx][0] = x ;
		dep[nx] = dep[x] + 1 ;
		dis[nx] = dis[x] + h->val ;
		dfs(nx) ;
	}
}

int lca(int x , int y) {
	if (dep[x] < dep[y]) std::swap(x , y) ;

	for (int i = 30 ; i >= 0 ; --i) {
		if ((1 << i) > n) continue ;
		int tmp = f[x][i] ;
		if (dep[tmp] >= dep[y]) x = tmp ;
	}

	if (x == y) return x ;

	for (int i = 30 ; i >= 0 ; --i) {
		if ((1 << i) > n) continue ;
		int tx = f[x][i] , ty = f[y][i] ;
		if (tx != ty) x = tx , y = ty ;
	}

	return f[x][0] ;
}

void ins(int x , int y , int v) {
	list[cur].num = y ;
	list[cur].val = v ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

///

bool find(int x , int cnt , int s) {
	bool ans = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == f[x][0]) continue ;
		ans |= find(nx , cnt , s) ;
		pt[x] += pt[nx] ;
	}

	if (pt[x] == cnt) ans |= (a[x] >= s) ;

	return ans ;
}

bool check(int x) {
	int cnt = 0 ;
	for (int i = 1 ; i <= n ; ++i) pt[i] = 0 ;
	for (int i = m - 1 ; i >= 0 ; --i) {
		data *p = &query[i] ;
		if (p->val <= x) break ;

		++cnt ;
		int d = lca(p->x , p->y) ;
		++pt[p->x] ; ++pt[p->y] ; pt[d] -= 2 ;
	}

	return find(1 , cnt , query[m - 1].val - x) ;
}

///

int main() {
	int L = 0 , R = 0 ;

	scanf("%d %d" , &n , &m) ;
	for (int i = 1 ; i < n ; ++i) {
		int x , y , v ;
		scanf("%d %d %d" , &x , &y , &v) ;
		eg[i] = (data){x , y , v} ; R += v ;
		ins(x , y , v) ; ins(y , x , v) ;
	}
	for (int i = 0 ; i < m ; ++i)
		scanf("%d %d" , &query[i].x , &query[i].y) ;

	///
	
	f[1][0] = 1 ; dep[1] = 1 ; dis[1] = 0 ;
	dfs(1) ;
	for (int j = 1 ; (1 << j) <= n ; ++j)
		for (int i = 1 ; i <= n ; ++i)
			f[i][j] = f[f[i][j - 1]][j - 1] ;
	for (int i = 1 ; i < n ; ++i) {
		data *p = &eg[i] ;
		if (dep[p->x] < dep[p->y]) std::swap(p->x , p->y) ;
		a[p->x] = p->val ;
	}
	for (int i = 0 ; i < m ; ++i) {
		data *p = &query[i] ;
		int d = lca(p->x , p->y) ;
		p->val = dis[p->x] + dis[p->y] - (dis[d] << 1) ;
	}

	std::sort(query + 0 , query + m , cmp) ;

	///
	
	--L ; ++R ;
	while (L + 1 < R) {
		int mid = (L + R) >> 1 ;
		if (check(mid)) R = mid ;
		else L = mid ;
	}
	printf("%d\n" , R) ;

	return 0 ;
}
