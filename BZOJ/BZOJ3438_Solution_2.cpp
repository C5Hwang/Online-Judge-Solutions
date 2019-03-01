#include <queue>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e3 + 10 , MAX_P = 3e3 + 10 , INF = 0x7FFFFFFF ;

struct data {int num , cap , reg ;} ;

std::queue<int> que ;
std::vector<data> eg[MAX_P] ;

int T , ti , dep[MAX_P] , ap[MAX_P] ;
int n , m , tot , sum , A[MAX_N] , B[MAX_N] ;

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
	que.push(0) ;
	ap[0] = ++ti ; dep[0] = 1 ;

	for (; !que.empty() ;) {
		int x = que.front() , siz = eg[x].size() ; que.pop() ;

		for (int i = 0 ; i < siz ; ++i) {
			int nx = eg[x][i].num ;
			if (ap[nx] == ti || !eg[x][i].cap) continue ;

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

void ins(int x , int y , int f) {
	int p1 = eg[x].size() , p2 = eg[y].size() ;

	eg[x].push_back((data){y , f , p2}) ;
	eg[y].push_back((data){x , 0 , p1}) ;
}

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

int main() {
	n = read() ;
	for (int i = 1 ; i <= n ; ++i) A[i] = read() , sum += A[i] ;
	for (int i = 1 ; i <= n ; ++i) B[i] = read() ;

	T = tot = n + 1 ;
	for (int i = 1 ; i <= n ; ++i) {
		int t = B[i] - A[i] ;

		if (t > 0) ins(0 , i , t) , sum += t ;
		else ins(i , T , -t) ;
	}

	///

	m = read() ;
	for (int i = 0 ; i < m ; ++i) {
		int c1 , c2 , id1 , id2 , t ;
		t = read() ; c1 = read() ; c2 = read() ; id1 = ++tot ; id2 = ++tot ;

		ins(id1 , T , c1) ; ins(0 , id2 , c2) ; sum += c1 ; sum += c2 ;
		for (; t-- ;) {int x = read() ; ins(id2 , x , INF) ; ins(x , id1 , INF) ;}
	}

	printf("%d\n" , sum - dinic()) ;

	return 0 ;
}