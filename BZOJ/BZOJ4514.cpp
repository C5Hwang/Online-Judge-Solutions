#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const ll MAX_DIS = 1e18 ;
const int MAX_N = 200 + 10 , MAX_M = 41e3 + 10 , LIM = 32e3 , INF = 0x3f3f3f3f ;

struct Link {
	int num , cap ; ll val ;
	Link *next , *reg ;
}list[MAX_M << 1] ;

std::queue<int> que ;

ll dis[MAX_N] ;
bool vis[MAX_N] ;
Link *head[MAX_N] , *id[MAX_N] ;
int T , cur , pre[MAX_N] , flow[MAX_N] ;
int tot , pri[LIM + 10] , ap[LIM + 10] ;
int n , a[MAX_N] , b[MAX_N] , c[MAX_N] , ty[MAX_N] ;

///

bool bfs() {
	for (int i = 0 ; i <= T ; ++i) dis[i] = -MAX_DIS ;

	que.push(0) ;
	dis[0] = 0 ; vis[0] = 1 ; flow[0] = INF ;

	for (; !que.empty() ;) {
		int x = que.front() ;
		vis[x] = 0 ; que.pop() ;

		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (!h->cap || dis[nx] >= dis[x] + h->val) continue ;

			dis[nx] = dis[x] + h->val ;
			flow[nx] = std::min(flow[x] , h->cap) ; id[nx] = h ; pre[nx] = x ;

			if (!vis[nx]) vis[nx] = 1 , que.push(nx) ;
		}
	}

	return dis[T] > -MAX_DIS ;
}

int work() {
	ll sum = 0 , ts = 0 ;
	for (; bfs() ;) {
		ll ns = flow[T] * dis[T] ;
		if (sum + ns < 0) {
			ts += sum / (-dis[T]) ;
			break ;
		}

		sum += ns ; ts += flow[T] ;
		for (int x = T ; x ; x = pre[x])
			id[x]->cap -= flow[T] , id[x]->reg->cap += flow[T] ;
	}

	return ts ;
}

void ins(int x , int y , int f , ll v) {
	list[cur].num = y ;
	list[cur].cap = f ;
	list[cur].val = v ;
	list[cur].next = head[x] ;
	list[cur].reg = &list[cur^1] ;
	head[x] = &list[cur++] ;

	list[cur].num = x ;
	list[cur].cap = 0 ;
	list[cur].val = -v ;
	list[cur].next = head[y] ;
	list[cur].reg = &list[cur^1] ;
	head[y] = &list[cur++] ;
}

///

void init() {
	for (int i = 2 ; i <= LIM ; ++i) {
		if (!ap[i]) pri[tot++] = i ;

		for (int j = 0 ; j < tot ; ++j) {
			int tmp = i * pri[j] ;
			if (tmp > LIM) break ;

			ap[tmp] = 1 ;
			if (!(i % pri[j])) break ;
		}
	}
}

bool check(int a , int b) {
	if (a > b) std::swap(a , b) ;
	if (b % a) return 0 ;

	b /= a ;
	for (int i = 0 ; i < tot ; ++i) {
		int P = pri[i] ;

		if (P * P > b) break ;
		else if (!(b % P)) return 0 ;
	}

	return 1 ;
}

int gettype(int x) {
	int cnt = 0 ;
	for (int i = 0 ; i < tot ; ++i) {
		int P = pri[i] ;
		if (P * P > x) break ;

		for (; !(x % P) ; x /= P , ++cnt) ;
	}
	if (x > 1) ++cnt ;

	return cnt % 2 ;
}

///

int main() {
	init() ; scanf("%d" , &n) ; T = n + 1 ;
	for (int i = 1 ; i <= n ; ++i) {
		scanf("%d" , &a[i]) ;
		ty[i] = gettype(a[i]) ;
	}
	for (int i = 1 ; i <= n ; ++i) scanf("%d" , &b[i]) ;
	for (int i = 1 ; i <= n ; ++i) scanf("%d" , &c[i]) ;

	///

	for (int i = 1 ; i <= n ; ++i) {
		if (!ty[i]) ins(0 , i , b[i] , 0) ;
		else {ins(i , T , b[i] , 0) ; continue ;}

		for (int j = 1 ; j <= n ; ++j)
			if (ty[j] && check(a[i] , a[j])) ins(i , j , INF , (ll)c[i] * c[j]) ;
	}

	printf("%d\n" , work()) ;

	return 0 ;
}