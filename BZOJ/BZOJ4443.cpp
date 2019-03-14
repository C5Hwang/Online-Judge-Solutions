#include <queue>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 250 + 10 , MAX_P = 500 + 10 , INF = 0x3f3f3f3f ;

struct data {int num , cap , reg ;} ;

std::queue<int> que ;
std::vector<data> eg[MAX_P] ;

int n , m , k , a[MAX_N][MAX_N] ;
int T , ti , dep[MAX_P] , ap[MAX_P] ;

int dfs(int x , int f) {
	if (x == T || !f) return f ;

	int sum = 0 , siz = eg[x].size() ;
	for (int i = 0 ; i < siz ; ++i) {
		int nx = eg[x][i].num ;
		if (dep[nx] != dep[x] + 1) continue ;

		int nf = dfs(nx , std::min(f ,eg[x][i].cap)) ;
		sum += nf ; eg[nx][eg[x][i].reg].cap += nf ;
		f -= nf ; eg[x][i].cap -= nf ;
	}
	if (f) dep[x] = -1 ;

	return sum ;
}

bool bfs() {
	que.push(0) ;
	dep[0] = 1 ; ap[0] = ++ti ;

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

	return ap[T] == ti ;
}

inline int dinic() {
	int sum = 0 ;
	for (; bfs() ; sum += dfs(0 , INF)) ;

	return sum ;
}

void ins(int x , int y , int v) {
	int p1 = eg[x].size() , p2 = eg[y].size() ;

	eg[x].push_back((data){y , v , p2}) ;
	eg[y].push_back((data){x , 0 , p1}) ;
}

void build(int x) {
	for (int i = 0 ; i <= n + m + 1 ; ++i) eg[i].clear() ;

	for (int i = 1 ; i <= n ; ++i) ins(0 , i , 1) ;
	for (int i = 1 ; i <= m ; ++i) ins(i + n , T , 1) ;

	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= m ; ++j)
			if (a[i][j] <= x) ins(i , j + n , 1) ;
}

bool check(int x) {
	build(x) ;

	return dinic() >= n - k + 1 ;
}

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;
	
	return num * f ;
}

int main() {
	int L = 0 , R = 0 ;

	n = read() ; m = read() ; k = read() ; T = n + m + 1 ;
	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= m ; ++j)
			a[i][j] = read() , R = std::max(R , a[i][j] + 1) ;

	///

	for (; L + 1 < R ;) {
		int mid = (L + R) >> 1 ;

		if (check(mid)) R = mid ;
		else L = mid ;
	}

	printf("%d\n" , R) ;

	return 0 ;
}