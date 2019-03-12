#include <queue>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 200 + 10 , MAX_P = 4e4 + 10 , INF = 0x3f3f3f3f ;

struct data {int num , cap , reg ;} ;

std::queue<int> que ;
std::vector<data> eg[MAX_P] ;

int S , T , SS , TT , ti , ap[MAX_P] , dep[MAX_P] ;
int n , m , tot , le , ri , r[MAX_N] , c[MAX_N] , tr[MAX_N] , tc[MAX_N] , a[MAX_N][MAX_N] ;

///

bool bfs() {
	que.push(SS) ;
	ap[SS] = ++ti ; dep[SS] = 1 ;

	for (; !que.empty() ;) {
		int x = que.front() , siz = eg[x].size() ;
		que.pop() ;

		for (int i = 0 ; i < siz ; ++i) {
			int nx = eg[x][i].num ;
			if (!eg[x][i].cap || ap[nx] == ti) continue ;

			que.push(nx) ;
			dep[nx] = dep[x] + 1 ; ap[nx] = ti ;
		}
	}

	return ap[TT] == ti ;
}

int dfs(int x , int f) {
	if (x == TT || !f) return f ;

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

inline int dinic() {
	int sum = 0 ;
	for (; bfs() ; sum += dfs(SS , INF)) ;

	return sum ;
}

///

void ins(int x , int y , int v) {
	if (!v) return ;
	int p1 = eg[x].size() , p2 = eg[y].size() ;

	eg[x].push_back((data){y , v , p2}) ;
	eg[y].push_back((data){x , 0 , p1}) ;
}

int add(int x , int y , int L , int R) {
	L = std::max(L , 0) ;

	ins(SS , y , L) ; ins(x , TT , L) ; ins(x , y , R - L) ;
	return L ;
}

void init() {
	for (int i = 0 ; i <= tot ; ++i) eg[i].clear() ;
}

int build(int x) {
	int sum = 0 ;
	ins(T , S , INF) ;
	for (int i = 1 ; i <= n ; ++i) sum += add(S , r[i] , tr[i] - x , tr[i] + x) ;
	for (int i = 1 ; i <= m ; ++i) sum += add(c[i] , T , tc[i] - x , tc[i] + x) ;

	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= m ; ++j) sum += add(r[i] , c[j] , le , ri) ;

	return sum ;
}

bool check(int x) {
	init() ;
	int sum = build(x) ;

	return dinic() == sum ;
}

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

///

int main() {
	n = read() ; m = read() ;

	S = 0 ; T = ++tot ;
	for (int i = 1 ; i <= n ; ++i) r[i] = ++tot ;
	for (int i = 1 ; i <= m ; ++i) c[i] = ++tot ;
	SS = ++tot ; TT = ++tot ;

	int L = -1 , R = 0 ;
	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= m ; ++j) {
			a[i][j] = read() ;
			tr[i] += a[i][j] ; tc[j] += a[i][j] ;
			R = std::max(tr[i] , R) ; R = std::max(tc[j] , R) ;
		}
	le = read() ; ri = read() ;

	///

	for (; L + 1 < R ;) {
		int mid = (L + R) >> 1 ;

		if (check(mid)) R = mid ;
		else L = mid ;
	}

	printf("%d\n" , R) ;

	return 0 ;
}