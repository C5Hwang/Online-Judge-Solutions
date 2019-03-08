#include <queue>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

#define db double
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const db eps = 1e-5 ;
const int MAX_N = 50 + 5 , MAX_P = 15e3 + 10 , INF = 0x3f3f3f3f ;

struct data {int num , reg ; db cap ;} ;

std::queue<int> que ;
std::vector<data> eg[MAX_P] ;

db sum ;
int T , ti , cur , dep[MAX_P] , ap[MAX_P] ;
int n , m , bh[MAX_N][MAX_N] , v[MAX_N][MAX_N] , c1[MAX_N][MAX_N] , c2[MAX_N][MAX_N] ;

///

db dfs(int x , db f) {
	if (x == T || f < eps) return f ;

	db sum = 0 ; int siz = eg[x].size() ;
	for (int i = 0 ; i < siz ; ++i) {
		int nx = eg[x][i].num ;
		if (dep[nx] != dep[x] + 1) continue ;

		db nf = dfs(nx , std::min(f , eg[x][i].cap)) ;
		sum += nf ; eg[nx][eg[x][i].reg].cap += nf ;
		f -= nf ; eg[x][i].cap -= nf ;
	}
	if (eps < f) dep[x] = -1 ;

	return sum ;
}

bool bfs() {
	que.push(0) ;
	dep[0] = 1 ; ap[0] = ++ti ;

	for (; !que.empty() ;) {
		int x = que.front() , siz = eg[x].size() ; que.pop() ;

		for (int i = 0 ; i < siz ; ++i) {
			int nx = eg[x][i].num ;
			if (ap[nx] == ti || eg[x][i].cap < eps) continue ;

			que.push(nx) ;
			dep[nx] = dep[x] + 1 ; ap[nx] = ti ;
		}
	}

	return ap[T] == ti ;
}

inline db dinic() {
	db sum = 0 ;
	for (; bfs() ; sum += dfs(0 , INF)) ;

	return sum ;
}

///

void init() {
	ti = 0 ;
	for (int i = 0 ; i < MAX_P ; ++i)
		ap[i] = 0 , eg[i].clear() ;
}

void ins(int x , int y , db v) {
	int p1 = eg[x].size() , p2 = eg[y].size() ;

	eg[x].push_back((data){y , p2 , v}) ;
	eg[y].push_back((data){x , p1 , 0}) ;
}

void build(db k) {
	sum = 0 ; T = n * m + 1 ; init() ;

	int tot = T ;
	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= m ; ++j)
			ins(0 , bh[i][j] , v[i][j]) , sum += v[i][j] ;

	for (int i = 1 ; i <= n + 1 ; ++i)
		for (int j = 1 ; j <= m ; ++j)
			if (i == 1 || i == n + 1) {
				int ni = i == n + 1 ? i - 1 : i , idx = ++tot ; db val = c1[i][j] * k ;

				ins(idx , T , val) ; ins(bh[ni][j] , idx , INF) ;
			}
			else {
				int id1 = ++tot , id2 = ++tot ; db val = c1[i][j] * k ;

				ins(0 , id2 , val) ; ins(id1 , T , val) ; sum += val ;
				ins(bh[i][j] , id1 , INF) ; ins(bh[i - 1][j] , id1 , INF) ;
				ins(id2 , bh[i][j] , INF) ; ins(id2 , bh[i - 1][j] , INF) ;
			}

	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= m + 1 ; ++j)
			if (j == 1 || j == m + 1) {
				int nj = j == m + 1 ? j - 1 : j , idx = ++tot ; db val = c2[i][j] * k ;

				ins(idx , T , val) ; ins(bh[i][nj] , idx , INF) ;
			}
			else {
				int id1 = ++tot , id2 = ++tot ; db val = c2[i][j] * k ;

				ins(0 , id2 , val) ; ins(id1 , T , val) ; sum += val ;
				ins(bh[i][j] , id1 , INF) ; ins(bh[i][j - 1] , id1 , INF) ;
				ins(id2 , bh[i][j] , INF) ; ins(id2 , bh[i][j - 1] , INF) ;
			}
}

bool check(db x) {
	build(x) ;

	return sum - dinic() > eps ;
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
	db L = 0 , R = 0 ;
	n = read() ; m = read() ;

	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= m ; ++j) {
			v[i][j] = read() ;
			bh[i][j] = (i - 1) * m + j ; R = std::max(R , v[i][j] + 1.0) ;
		}
	for (int i = 1 ; i <= n + 1 ; ++i)
		for (int j = 1 ; j <= m ; ++j) c1[i][j] = read() ;
	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= m + 1 ; ++j) c2[i][j] = read() ;

	///

	for (; fabs(L - R) > eps ;) {
		db mid = (L + R) / 2 ;

		if (check(mid)) L = mid ;
		else R = mid ;
	}

	printf("%0.3lf\n" , L) ;

	return 0 ;
}