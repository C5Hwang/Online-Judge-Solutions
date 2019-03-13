#include <queue>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1200 + 10 , MAX_P = 2400 + 10 , INF = 0x3f3f3f3f ;

struct data {int num , cap , reg ;} ;

std::queue<int> que ;
std::vector<data> eg[MAX_P] ;

int n , m , sum ;
int T , ti , dep[MAX_P] , ap[MAX_P] , cur[MAX_P] ;

int dfs(int x , int f) {
	if (x == T || !f) return f ;

	int sum = 0 , siz = eg[x].size() ;
	for (int i = cur[x] ; i < siz ; ++i) {
		cur[x] = i ;

		int nx = eg[x][i].num ;
		if (dep[nx] != dep[x] + 1) continue ;

		int nf = dfs(nx , std::min(f , eg[x][i].cap)) ;
		sum += nf ; eg[nx][eg[x][i].reg].cap += nf ;
		f -= nf ; eg[x][i].cap -= nf ;

		if (!f) return sum ;
	}

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
	for (; bfs() ;) {
		memset(cur , 0 , sizeof(cur)) ;
		sum += dfs(0 , INF) ;
	}

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
	n = read() ; m = read() ; T = n + m + 1 ;
	for (int i = 1 ; i <= n ; ++i) {
		int p = i + m , c , k ;
		c = read() ; k = read() ; sum += c ;

		ins(0 , p , c) ;
		for (; k-- ;) {
			int t , tc ;
			t = read() ; tc = read() ;
			ins(p , t , tc) ;
		}
	}
	for (int i = 1 ; i <= m ; ++i) {int v = read() ; ins(i , T , v) ;}

	printf("%d\n" , sum - dinic()) ;

	return 0 ;
}