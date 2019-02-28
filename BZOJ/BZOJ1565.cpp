#include <queue>
#include <stack>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 30 + 5 , MAX_P = 600 + 10 , MAX_M = 4e5 + 10 , INF = 0x3f3f3f3f ;

struct data {int num , cap , reg ;} ;

struct Link {
	int num ;
	Link *next ;
}list[MAX_M << 1] ;

std::queue<int> que ;
std::stack<int> sta ;
std::vector<data> eg[MAX_P] ;

bool ck[MAX_P] ;
Link *head[MAX_P] ;
int n , m , tot , cnt , cur , sum , bh[MAX_N][MAX_N] , v[MAX_P] ;
int T , ti , ap[MAX_P] , dfn[MAX_P] , low[MAX_P] , dep[MAX_P] , state[MAX_P] ;

///

int dfs(int x , int f) {
	if (x == T || !f) return f ;

	int siz = eg[x].size() , s = 0 ;
	for (int i = 0 ; i < siz ; ++i) {
		int nx = eg[x][i].num ;
		if (dep[nx] != dep[x] + 1) continue ;

		int nf = dfs(nx , std::min(f , eg[x][i].cap)) ;
		s += nf ; eg[nx][eg[x][i].reg].cap += nf ;
		f -= nf ; eg[x][i].cap -= nf ;
	}
	if (f) dep[x] = -1 ;

	return s ;
}

bool bfs() {
	que.push(0) ;
	dep[0] = 1 ; ap[0] = ++ti ;

	for (; !que.empty() ;) {
		int x = que.front() , siz = eg[x].size() ; que.pop() ;

		for (int i = 0 ; i < siz ; ++i) {
			int nx = eg[x][i].num ;
			if (!eg[x][i].cap || ap[nx] == ti) continue ;

			que.push(nx) ;
			ap[nx] = ti ; dep[nx] = dep[x] + 1 ;
		}
	}

	return ap[T] == ti ;
}

inline int dinic() {
	int sum = 0 ;
	for (; bfs() ; sum += dfs(0 , INF)) ;

	return sum ;
}

void tarjan(int x) {
	sta.push(x) ;
	dfn[x] = low[x] = ++ti ; state[x] = 1 ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;

		if (!state[nx]) tarjan(nx) , low[x] = std::min(low[x] , low[nx]) ;
		else if (state[nx] == 1) low[x] = std::min(low[x] , dfn[nx]) ;
	}

	if (dfn[x] <= low[x]) {
		bool a = sta.top() == x ? 1 : 0 ;

		for (; sta.top() != x ;) {
			int t = sta.top() ;
			sta.pop() ; ck[t] = a ; state[t] = 2 ;
		}
		sta.pop() ; ck[x] = a ; state[x] = 2 ;
	}
}

///

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

void ins(int x , int y , int v) {
	int p1 = eg[x].size() , p2 = eg[y].size() ;

	eg[x].push_back((data){y , v , p2}) ;
	eg[y].push_back((data){x , 0 , p1}) ;
}

void add_edge(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

///

int main() {
	n = read() ; m = read() ;
	for (int i = 0 ; i < n ; ++i)
		for (int j = 0 ; j < m ; ++j) bh[i][j] = ++tot ;
	T = ++tot ;

	for (int i = 0 ; i < n ; ++i)
		for (int j = 0 ; j < m ; ++j) {
			int t ;
			v[bh[i][j]] = read() ; t = read() ;

			if (j + 1 < m) add_edge(bh[i][j] , bh[i][j + 1]) , ins(bh[i][j] , bh[i][j + 1] , INF) ;

			for (; t-- ;) {
				int x , y ; x = read() ; y = read() ;
				add_edge(bh[x][y] , bh[i][j]) ; ins(bh[x][y] , bh[i][j] , INF) ;
			}
		}

	///

	for (int i = 1 ; i < tot ; ++i)
		if (!state[i]) tarjan(i) ;
	for (int i = 1 ; i < tot ; ++i) {
		if (!ck[i]) v[i] = -INF ;

		if (v[i] > 0) ins(0 , i , v[i]) , sum += v[i] ;
		else ins(i , T , -v[i]) ;
	}

	printf("%d\n" , sum - dinic()) ;

	return 0 ;
}