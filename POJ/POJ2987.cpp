#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 5000 + 10 , MAX_M = 60000 + 10 , INF = 0x3f3f3f3f ;

std::queue<int> q ;

struct Link {
	int num , f ;
	Link *next , *reg ;
}list[2 * MAX_N + 2 * MAX_M] ;

bool ap[MAX_N] ;
Link *head[MAX_N] ;
int n , m , S , T , cur , time , bft[MAX_N] , dep[MAX_N] ;

///

bool bfs() {
	q.push(S) ; bft[S] = ++time ; dep[S] = 1 ;

	while (!q.empty()) {
		int x = q.front() ; q.pop() ;

		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (!h->f || bft[nx] == time) continue ;

			q.push(nx) ;
			bft[nx] = time ; dep[nx] = dep[x] + 1 ;
		}
	}

	return bft[T] == time ;
}

long long dfs(int x , int flow) {
	if (x == T || !flow) return flow ;

	long long sum = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (dep[nx] != dep[x] + 1) continue ;

		long long nf = dfs(nx , std::min(flow , h->f)) ;
		sum += nf ; flow -= nf ;
		h->f -= nf ; h->reg->f += nf ;
	}

	return sum ;
}

long long dinic() {
	long long sum = 0 ;
	while (bfs())
		sum += dfs(S , INF) ;

	return sum ;
}

///

void GetNum(int x) {
	if (ap[x]) return ;

	ap[x] = 1 ;
	for (Link *h = head[x] ; h ; h = h->next)
		if (h->f) GetNum(h->num) ;
}

void ins(int x , int y , int v) {
	list[cur].f = v ;
	list[cur].num = y ;
	list[cur].next = head[x] ;
	list[cur].reg = &list[cur + 1] ;
	head[x] = &list[cur++] ;

	list[cur].f = 0 ;
	list[cur].num = x ;
	list[cur].next = head[y] ;
	list[cur].reg = &list[cur - 1] ;
	head[y] = &list[cur++] ;
}

int main() {
	long long sum = 0 ;
	scanf("%d %d" , &n , &m) ; S = 0 ; T = n + 1 ;
	for (int i = 1 ; i <= n ; ++i) {
		long long a ; scanf("%lld" , &a) ;
		if (a > 0) ins(S , i , a) , sum += a ;
		else ins(i , T , -a) ;
	}
	for (int i = 0 ; i < m ; ++i) {
		int x , y ;
		scanf("%d %d" , &x , &y) ;
		ins(x , y , INF) ;
	}

	///

	long long res = dinic() ;

	int cutnum = 0 ; GetNum(S) ;
	for (int i = 1 ; i <= n ; ++i)
		if (ap[i]) ++cutnum ;

	printf("%d %lld\n" , cutnum , sum - res) ;

	return 0 ;
}
