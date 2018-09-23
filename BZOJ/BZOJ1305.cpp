#include <queue>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAX_N = 50 + 10 , MAX_E = 3000 + 10 , INF = 0x3f3f3f3f ;

struct Link {
	int num , f ;
	Link *next , *reg ;
}list[2 * MAX_E] ;

std::queue<int> q ;

char c[MAX_N][MAX_N] ;
Link *head[4 * MAX_N] ;
int n , k , cur , S , T ;
int time , bft[4 * MAX_N] , dep[4 * MAX_N] ;

///

void init() {
	cur = 0 ;
	memset(head , 0 , sizeof(head)) ;
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

void addedge(int al) {
	init() ;

	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= n ; ++j) {
			int b = i , g = j + 2 * n ;
			if (c[i][j] == 'Y') ins(b , g , 1) ;
			else ins(b + n , g + n , 1) ;
		}

	for (int i = 1 ; i <= n ; ++i) {
		int b = i , g = i + 2 * n ;
		ins(b , b + n , k) ; ins(g + n , g , k) ;

		ins(S , b , al) ; ins(g , T , al) ;
	}
}

///

bool bfs() {
	q.push(S) ;
	bft[S] = ++time ; dep[S] = 0 ;

	while (!q.empty()) {
		int x = q.front() ;
		q.pop() ;

		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (!h->f || bft[nx] == time) continue ;

			bft[nx] = time ; dep[nx] = dep[x] + 1 ;
			q.push(nx) ;
		}
	}

	return bft[T] == time ;
}

int dfs(int x , int flow) {
	if (x == T || !flow) return flow ;

	int sum = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (dep[nx] != dep[x] + 1) continue ;

		int nf = dfs(nx , std::min(flow , h->f)) ;
		flow -= nf ; sum += nf ;
		h->f -= nf ; h->reg->f += nf ;
	}
	if (flow) dep[x] = -1 ;

	return sum ;
}

int dinic() {
	int sum = 0 ;
	while (bfs())
		sum += dfs(S , INF) ;

	return sum ;
}

///

bool check(int x) {
	addedge(x) ;

	int res = dinic() ;

	return res == x * n ;
}

char read() {
	int c = getchar() ;
	while (c < 'A') c = getchar() ;

	return c ;
}

int main() {
	scanf("%d %d" , &n , &k) ;
	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= n ; ++j)
			c[i][j] = read() ;
	S = 0 ; T = 4 * n + 1 ;

	///

	int L = 0 , R = n + 1 ;
	while (L + 1 < R) {
		int mid = (L + R) >> 1 ;

		if (check(mid)) L = mid ;
		else R = mid ;
	}

	printf("%d\n" , L) ;

	return 0 ;
}
