#include <queue>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 1e3 + 10 , MAX_M = 2e3 + 10 , MAX_E = 1e4 + 10 , INF = 0x3f3f3f3f ;

struct Edge {int x , y , cx , cy , d ;}eg[MAX_M] ;
struct Link {
	int num , cap ;
	Link *next , *reg ;
}list[MAX_E] ;

std::queue<int> que ;

Link *head[MAX_N] ;
int n , m , cur , L , R , ot[MAX_N] ;
int S , T , ti , ap[MAX_N] , dep[MAX_N] ;

int dfs(int x , int flow) {
	if (x == T || !flow) return flow ;

	int sum = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (dep[nx] != dep[x] + 1 || !h->cap) continue ;

		int tf = dfs(nx , std::min(flow , h->cap)) ;
		flow -= tf ; h->cap -= tf ;
		sum += tf ; h->reg->cap += tf ;
	}
	if (flow) dep[x] = -1 ;

	return sum ;
}

bool bfs() {
	que.push(S) ;
	ap[S] = ++ti ; dep[S] = 1 ;

	for (; !que.empty() ;) {
		int x = que.front() ; que.pop() ;

		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (!h->cap || ap[nx] == ti) continue ;

			que.push(nx) ;
			ap[nx] = ti ; dep[nx] = dep[x] + 1 ;
		}
	}

	return ap[T] == ti ;
}

int dinic() {
	int sum = 0 ;
	for (; bfs() ; sum += dfs(S , INF)) ;

	return sum ;
}

void ins(int x , int y , int v) {
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

bool check(int x) {
	ti = cur = 0 ;
	memset(ap , 0 , sizeof(ap)) ;
	memset(ot , 0 , sizeof(ot)) ;
	memset(head , 0 , sizeof(head)) ;

	///

	for (int i = 0 ; i < m ; ++i) {
		Edge *p = &eg[i] ; p->d = 0 ;
		if (p->cx <= x) ++p->d ;
		if (p->cy <= x) ++p->d ;

		if (p->d == 1) {
			if (p->cx <= x) ++ot[p->x] , --ot[p->y] ;
			else ++ot[p->y] , --ot[p->x] ;
		}
		else if (p->d == 2) ++ot[p->x] , --ot[p->y] ;
	}

	///

	int ms = 0 , ls = 0 ;
	S = 0 ; T = n + 1 ;
	for (int i = 1 ; i <= n ; ++i) if (abs(ot[i]) & 1) return 0 ;
	for (int i = 1 ; i <= n ; ++i)
		if (ot[i] > 0) ins(S , i , ot[i] >> 1) , ms += ot[i] >> 1 ;
		else if (ot[i] < 0) ins(i , T , (-ot[i]) >> 1) , ls += (-ot[i]) >> 1 ;

	if (ms != ls) return 0 ;

	for (int i = 0 ; i < m ; ++i) {
		Edge *p = &eg[i] ;
		if (p->d < 2) continue ;

		ins(p->x , p->y , 1) ;
	}

	return dinic() == ls ;
}

int main() {
	L = INF ; R = 0 ;
	scanf("%d %d" , &n , &m) ;
	for (int i = 0 ; i < m ; ++i) {
		int x , y , a , b ;
		scanf("%d %d %d %d" , &x , &y , &a , &b) ;
		L = std::min(L , a) ; L = std::min(L , b) ;
		R = std::max(R , a) ; R = std::max(R , b) ;

		eg[i] = (Edge){x , y , a , b , 0} ;
	}

	///

	bool ok = 0 ;
	
	--L ; ++R ;
	for (; L + 1 < R ;) {
		int mid = (L + R) >> 1 ;
		if (check(mid)) R = mid , ok = 1 ;
		else L = mid ;
	}

	if (ok) printf("%d\n" , R) ;
	else printf("NIE\n") ;

	return 0 ;
}