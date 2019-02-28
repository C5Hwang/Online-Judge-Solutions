#include <queue>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const ll INF = 1e16 ;
const int MAX_N = 1e3 + 10 ;

struct data {int num , reg ; ll cap ;} ;

std::queue<int> que ;
std::vector<data> eg[MAX_N] ;

ll sum , b[MAX_N] ;
int n , T , ti , cur , ap[MAX_N] , dep[MAX_N] ;

ll dfs(int x , ll f) {
	if (!f || x == T) return f ;

	ll s = 0 ; int siz = eg[x].size() ;
	for (int i = 0 ; i < siz ; ++i) {
		int nx = eg[x][i].num ;
		if (dep[nx] != dep[x] + 1) continue ;

		ll nf = dfs(nx , std::min(f , eg[x][i].cap)) ;
		s += nf ; eg[nx][eg[x][i].reg].cap += nf ;
		f -= nf ; eg[x][i].cap -= nf ;

		if (!f) return s ;
	}
	if (f) dep[x] = -1 ;

	return s ;
}

bool bfs() {
	que.push(0) ;
	dep[0] = 1 ; ap[0] = ++ti ;

	for (; !que.empty() ;) {
		int x = que.front() , s = eg[x].size() ; que.pop() ;

		for (int i = 0 ; i < s ; ++i) {
			int nx = eg[x][i].num ;
			if (!eg[x][i].cap || ap[nx] == ti) continue ;

			que.push(nx) ;
			dep[nx] = dep[x] + 1 ; ap[nx] = ti ;
		}
	}

	return ap[T] == ti ;
}

ll dinic() {
	ll sum = 0 ;
	for (; bfs() ; sum += dfs(0 , INF)) ;

	return sum ;
}

void ins(int x , int y , ll v) {
	int p1 = eg[x].size() , p2 = eg[y].size() ;
	eg[x].push_back((data){y , p2 , v}) ;
	eg[y].push_back((data){x , p1 , 0}) ;
}

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

int main() {
	n = read() ; T = n + 1 ;
	for (int i = 1 ; i <= n ; ++i) {
		int x = read() ;
		ins(0 , i , x) ;
	}

	sum = 0 ;
	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= n ; ++j) {
			int x = read() ;
			
			ins(i , j , x << 1) ; b[i] += x ;
		}
	for (int i = 1 ; i <= n ; ++i) ins(i , T , b[i]) , sum += b[i] ;

	printf("%lld\n" , sum - dinic()) ;

	return 0 ;
}