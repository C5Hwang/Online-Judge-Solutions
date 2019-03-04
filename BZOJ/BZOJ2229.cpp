#include <queue>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 150 + 10 , INF = 0x3f3f3f3f ;

struct data {int num , cap , reg ;} ;
struct Link {
	int num , val ;
	Link *next ;
}list[MAX_N << 1] ;

std::queue<int> que ;
std::vector<data> eg[MAX_N] ;

bool vis[MAX_N] ;
Link *head[MAX_N] ;
int S , T , ti , ap[MAX_N] , dep[MAX_N] ;
int CASE , n , m , cur , tot , ans[MAX_N] , vert[MAX_N] , t1[MAX_N] , t2[MAX_N] , c[MAX_N][MAX_N] ;

///

int dfs(int x , int f) {
	if (x == T || !f) return f ;

	int sum = 0 , siz = eg[x].size() ;
	for (int i = 0 ; i < siz ; ++i) {
		int nx = eg[x][i].num ;
		if (dep[nx] != dep[x] + 1) continue ;

		int nf = dfs(nx , std::min(f , eg[x][i].cap)) ;
		sum += nf ; eg[nx][eg[x][i].reg].cap += nf ;
		f -= nf ; eg[x][i].cap -= nf ;
	}
	if (f) dep[x] = -1 ;

	return sum ;
}

bool bfs() {
	que.push(S) ;
	ap[S] = ++ti ; dep[S] = 1 ;

	for (; !que.empty() ;) {
		int x = que.front() , siz = eg[x].size() ;
		que.pop() ;

		for (int i = 0 ; i < siz ; ++i) {
			int nx = eg[x][i].num ;
			if (!eg[x][i].cap || ap[nx] == ti) continue ;

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

///

void init() {
	for (int i = 1 ; i <= n ; ++i) {
		eg[i].clear() ;
		for (int j = 1 ; j <= n ; ++j) c[i][j] = 0 ;
	}

	cur = 0 ;
	memset(head , 0 , sizeof(head)) ;
}

void init_cap() {
	for (int i = 1 ; i <= n ; ++i) {
		int siz = eg[i].size() ;

		for (int j = 0 ; j < siz ; ++j) {
			int ni = eg[i][j].num ;
			eg[i][j].cap = c[i][ni] ;
		}
	}
}

void ins(int x , int y , int v) {
	int p1 = eg[x].size() , p2 = eg[y].size() ;

	eg[x].push_back((data){y , v , p2}) ;
	eg[y].push_back((data){x , v , p1}) ;
}

void add_edge(int x , int y , int v) {
	list[cur].num = y ;
	list[cur].val = v ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

///

void getans(int x , int f , int p , int v) {
	if (p < x) ans[tot++] = v ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == f) continue ;

		getans(nx , x , p , std::min(v , h->val)) ;
	}
}

void find(int x) {
	vis[x] = 1 ;

	int siz = eg[x].size() ;
	for (int i = 0 ; i < siz ; ++i) {
		int nx = eg[x][i].num ;
		if (!eg[x][i].cap || vis[nx]) continue ;

		find(nx) ;
	}
}

void work(int x , int y) {
	if (x == y) return ;

	init_cap() ;
	S = vert[x] ; T = vert[y] ; int v = dinic() ;
	add_edge(S , T , v) ; add_edge(T , S , v) ;

	///

	memset(vis , 0 , sizeof(vis)) ; find(S) ;

	int o1 = 0 , o2 = 0 ;
	for (int i = x ; i <= y ; ++i)
		if (vis[vert[i]]) t1[o1++] = vert[i] ;
		else t2[o2++] = vert[i] ;

	for (int i = 0 ; i < o1 ; ++i) vert[i + x] = t1[i] ;
	for (int i = 0 ; i < o2 ; ++i) vert[i + x + o1] = t2[i] ;

	work(x , x + o1 - 1) ; work(x + o1 , y) ;
}

///

int main() {
	CASE = read() ;
	for (; CASE-- ;) {
		n = read() ; m = read() ; init() ;
		for (int i = 0 ; i < m ; ++i) {
			int x , y , v ;
			x = read() ; y = read() ; v = read() ;

			c[x][y] += v ; c[y][x] += v ;
		}

		for (int i = 1 ; i <= n ; ++i)
			for (int j = i ; j <= n ; ++j)
				if (c[i][j]) ins(i , j , c[i][j]) ;

		///

		for (int i = 1 ; i <= n ; ++i) vert[i] = i ;
		work(1 , n) ;

		tot = 0 ;
		for (int i = 1 ; i <= n ; ++i)
			getans(i , i , i , INF) ;
		std::sort(ans + 0 , ans + tot) ;

		int Q = read() ;
		for (; Q-- ;) {
			int x = read() , res = 0 ;

			for (; res < tot && ans[res] <= x ; ++res) ;
			printf("%d\n" , res) ;
		}
		printf("\n") ;
	}

	return 0 ;
}