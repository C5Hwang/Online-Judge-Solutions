#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 1e5 + 10 , MAX_M = 2e5 + 10 , MAX_K = 50 + 10 , INF = 0x3f3f3f3f ;

struct Edge {int x , y , v ;}eg[MAX_M] ;
struct Link {
	int num , val ;
	Link *next ;
}list[MAX_M] ;

Link *head[MAX_N] ;
int cnt , hp[MAX_N] , pl[MAX_N] ;
bool ap[MAX_N] , flag[MAX_N][MAX_K] ;
int Q , n , m , K , P , cur , dis[MAX_N] , f[MAX_N][MAX_K] ;

///

int cmp(int x) {
	int L = x << 1 , R = x << 1 | 1 ;
	if (R > cnt) return hp[L] ;
	else return dis[hp[L]] < dis[hp[R]] ? hp[L] : hp[R] ;
}

void change(int x , int y) {
	std::swap(hp[pl[x]] , hp[pl[y]]) ;
	std::swap(pl[x] , pl[y]) ;
}

void update(int x) {
	for (; pl[x] > 1 ;) {
		int fa = hp[pl[x] >> 1] ;
		if (dis[fa] > dis[x]) change(fa , x) ;
		else break ;
	}
}

void push(int x) {
	hp[++cnt] = x ; pl[x] = cnt ;
	update(x) ;
}

void pop() {
	int x = hp[cnt] ;
	hp[1] = hp[cnt--] ; pl[x] = 1 ;
	for (; (pl[x] << 1) <= cnt ;) {
		int d = cmp(pl[x]) ;

		if (dis[d] < dis[x]) change(d , x) ;
		else break ;
	}
}

void dijkstra() {
	for (int i = 1 ; i <= n ; ++i) dis[i] = INF ;

	dis[1] = 0 ; push(1) ; ap[1] = 1 ;
	
	for (; cnt ;) {
		int x = hp[1] ; pop() ;

		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (dis[nx] > dis[x] + h->val) {
				dis[nx] = dis[x] + h->val ;
				if (ap[nx]) update(nx) ;
				else ap[nx] = 1 , push(nx) ;
			}
		}
	}
}

///

void init() {
	cur = cnt = 0 ;
	memset(f , -1 , sizeof(f)) ;
	memset(ap , 0 , sizeof(ap)) ;
	memset(head , 0 , sizeof(head)) ;
}

void ins(int x , int y , int v) {
	list[cur].num = y ;
	list[cur].val = v ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

int dfs(int x , int K) {
	if (flag[x][K]) return -1 ;
	if (f[x][K] > -1) return f[x][K] ;

	int ans = 0 ;
	if (x == 1 && !K) ans = 1 ;
	flag[x][K] = 1 ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num , nk = dis[h->num] - dis[x] + h->val , tmp = 0 ;

		if (K >= nk) tmp = dfs(nx , K - nk) ;
		if (tmp == -1) {flag[x][K] = 0 ; return -1 ;}

		(ans += tmp) %= P ;
	}
	flag[x][K] = 0 ;

	return (f[x][K] = ans) ;
}

int main() {
	freopen("park.in" , "r" , stdin) ;
	freopen("park.out" , "w" , stdout) ;

	scanf("%d" , &Q) ;
	while (Q--) {
		init() ;

		scanf("%d %d %d %d" , &n , &m , &K , &P) ;
		for (int i = 0 ; i < m ; ++i) {
			int x , y , v ;
			scanf("%d %d %d" , &x , &y , &v) ;
			ins(x , y , v) ; eg[i] = (Edge){x , y , v} ;
		}

		///

		dijkstra() ;

		cur = 0 ; memset(head , 0 , sizeof(head)) ;
		for (int i = 0 ; i < m ; ++i) ins(eg[i].y , eg[i].x , eg[i].v) ;

		///

		int res = 0 ;
		for (int i = 0 ; i <= K && res >= 0 ; ++i) {
			int tmp = dfs(n , i) ;
			if (tmp == -1) {res = -1 ; continue ;}

			(res += tmp) %= P ;
		}

		printf("%d\n" , res) ;
	}

	fclose(stdin) ; fclose(stdout) ;

	return 0 ;
}