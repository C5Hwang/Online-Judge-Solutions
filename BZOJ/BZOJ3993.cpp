#include <queue>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

#define db double
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const db eps = 1e-5 ;
const int MAX_N = 50 + 5 , MAX_E = 6e3 + 10 , INF = 0x3f3f3f3f ;

struct Link {
	int num ; db cap ;
	Link *next , *reg ;
}list[MAX_E] ;

std::queue<int> que ;

bool u[MAX_N][MAX_N] ;
Link *head[MAX_N << 1] ;
int ti , ap[MAX_N << 1] , dep[MAX_N << 1] ;
int n , m , S , T , cur , a[MAX_N] , b[MAX_N] ;

bool bfs() {
	que.push(S) ;
	dep[S] = 1 ; ap[S] = ++ti ;

	for (; !que.empty() ;) {
		int x = que.front() ; que.pop() ;

		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (ap[nx] == ti || h->cap < eps) continue ;

			que.push(nx) ;
			ap[nx] = ti ; dep[nx] = dep[x] + 1 ;
		}
	}

	return ap[T] == ti ;
}

db dfs(int x , db flow) {
	if (x == T || flow < eps) return flow ;

	db sum = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (dep[nx] != dep[x] + 1 || h->cap < eps) continue ;

		db tf = dfs(nx , std::min(flow , h->cap)) ;
		flow -= tf ; h->cap -= tf ;
		sum += tf ; h->reg->cap += tf ;
	}
	if (flow > eps) dep[x] = -1 ;

	return sum ;
}

db dinic() {
	db sum = 0 ;
	for (; bfs() ; sum += dfs(S , INF)) ;

	return sum ;
}

void ins(int x , int y , db v) {
	list[cur].num = y ;
	list[cur].cap = v ;
	list[cur].next = head[x] ;
	list[cur].reg = &list[cur^1] ;
	head[x] = &list[cur++] ;

	list[cur].num = x ;
	list[cur].cap = 0 ;
	list[cur].next = head[y] ;
	list[cur].reg = &list[cur^1] ;
	head[y] = &list[cur++] ;
}

bool check(db t) {
	cur = ti = 0 ;
	memset(ap , 0 , sizeof(ap)) ;
	memset(head , 0 , sizeof(head)) ;

	db tot = 0 ;
	S = 0 ; T = n + m + 1 ;
	for (int i = 1 ; i <= m ; ++i) ins(S , i , b[i] * t) ;
	for (int i = 1 ; i <= n ; ++i) ins(i + m , T , a[i]) , tot += a[i] ;

	for (int i = 1 ; i <= m ; ++i)
		for (int j = 1 ; j <= n ; ++j)
			if (u[i][j]) ins(i , j + m , INF) ;

	return fabs(dinic() - tot) < eps ;
}

int main() {
	db L = 0 , R = 0 ;

	scanf("%d %d" , &n , &m) ;
	for (int i = 1 ; i <= n ; ++i) scanf("%d" , &a[i]) , R = std::max(R , (db)a[i]) ;
	for (int i = 1 ; i <= m ; ++i) scanf("%d" , &b[i]) ;
	for (int i = 1 ; i <= m ; ++i)
		for (int j = 1 ; j <= n ; ++j) {
			int a ; scanf("%d" , &a) ;
			u[i][j] = a ? 1 : 0 ;
		}

	///

	for (; fabs(L - R) > eps ;) {
		db mid = (L + R) * 0.5 ;

		if (check(mid)) R = mid ;
		else L = mid ;
	}

	printf("%0.4lf\n" , R) ;

	return 0 ;
}