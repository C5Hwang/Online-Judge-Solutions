#include <queue>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 200 + 10 , MAX_M = 40000 + 10 , INF = 0x3f3f3f3f ;

struct Edge {
	int x , y , v ;
}e[MAX_M] ;
struct Link {
	int num , f ;
	Link *next , *reg ;
}list[2 * MAX_M] ;

std::queue<int> q ;

Link *head[MAX_N] ;
int n , m , T , cur ;
int time , bft[MAX_N] , dep[MAX_N] ;

///

bool bfs() {
	q.push(1) ;
	bft[1] = ++time ; dep[1] = 1 ;
	while (!q.empty()) {
		int x = q.front() ; q.pop() ;
		
		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;

			if (bft[nx] == time || !h->f) continue ;

			q.push(nx) ; bft[nx] = time ; dep[nx] = dep[x] + 1 ;
		}
	}

	return bft[n] == time ;
}

int dfs(int x , int flow) {
	if (x == n || !flow) return flow ;

	int sum = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;

		if (dep[nx] != dep[x] + 1) continue ;

		int nf = dfs(nx , std::min(flow , h->f)) ;

		flow -= nf ; sum += nf ;
		h->f -= nf ; h->reg->f += nf ;
	}
	if(flow) dep[x] = -1 ;

	return sum ;
}

int dinic() {
	int sum = 0 ;
	while (bfs())
		sum += dfs(1 , INF) ;

	return sum ;
}

///

void ins(int x , int y) {
	list[cur].f = 1 ;
	list[cur].num = y ;
	list[cur].next = head[x] ;
	list[cur].reg = &list[cur + 1] ;
	head[x] = &list[cur++] ;

	list[cur].f = 1 ;
	list[cur].num = x ;
	list[cur].next = head[y] ;
	list[cur].reg = &list[cur - 1] ;
	head[y] = &list[cur++] ;
}

void init() {
	cur = 0 ;
	memset(head , 0 , sizeof(head)) ;
}

bool check(int x) {
	init() ;

	for (int i = 0 ; i < m ; ++i) {
		if (e[i].v > x) continue ;
		int a = e[i].x , b = e[i].y ;
		ins(a , b) ;
	}

	return dinic() >= T ;
}

///

int read() {
	int x = 0 , F = 1 ; char c = getchar() ;
	while (c < '0' || c > '9') {if (c == '-') F = -F ; c = getchar() ;}
	while (c >= '0' && c <= '9') {x = x * 10 - '0' + c ; c = getchar() ;}

	return x * F ;
}

int main() {
	int L = INF , R = 0 ;

	n = read() ; m = read() ; T = read() ;
	for (int i = 0 ; i < m ; ++i) {
		e[i].x = read() ; e[i].y = read() ; e[i].v = read() ;
		L = std::min(L , e[i].v) ;
		R = std::max(R , e[i].v) ;
	}

	///
	
	--L ;
	while (L + 1 < R) {
		int mid = (L + R) >> 1 ;

		if (check(mid)) R = mid ;
		else L = mid ;
	}

	printf("%d\n" , R) ;

	return 0 ;
}
