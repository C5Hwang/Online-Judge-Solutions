#include <map>
#include <queue>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 , INF = 0x3f3f3f3f ;
const int dx[4] = {0 , 0 , 1 , -1} , dy[4] = {-1 , 1 , 0 , 0} ;

struct data {int num , cap , reg ;} ;
struct Point {
	int x , y ;

	friend bool operator <(Point a , Point b) {return a.x < b.x || (a.x == b.x && a.y < b.y) ;}
}pt[MAX_N] ;

std::queue<int> que ;
std::map<Point , int> idx ;
std::vector<data> eg[MAX_N] ;

int R , C , n , v[MAX_N] ;
int T , ti , dep[MAX_N] , ap[MAX_N] ;

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
	que.push(0) ;
	ap[0] = ++ti ; dep[0] = 1 ;

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

///

void ins(int x , int y , int f) {
	int p1 = eg[x].size() , p2 = eg[y].size() ;

	eg[x].push_back((data){y , f , p2}) ;
	eg[y].push_back((data){x , 0 , p1}) ;
}

int gettype(int x) {
	int px = pt[x].x , py = pt[x].y ;
	px %= 4 ; py %= 2 ;

	if (py) return px + 1 ;
	else {
		if (!px) return 2 ;
		else if (px == 1) return 1 ;
		else if (px == 2) return 4 ;
		else return 3 ;
	}
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
	C = read() ; R = read() ; n = read() ;
	for (int i = 1 ; i <= n ; ++i) {
		Point *p = &pt[i] ;
		p->x = read() ; p->y = read() ; v[i] = read() ;

		idx[pt[i]] = i ;
	}

	///

	T = n + 1 ;
	for (int x = 1 ; x <= n ; ++x) {
		int ty = gettype(x) ;

		if (ty == 1) ins(0 , x , v[x]) ;
		else if (ty == 4) ins(x , T , v[x]) ;

		for (int i = 0 ; i < 4 ; ++i) {
			Point np = (Point){pt[x].x + dx[i] , pt[x].y + dy[i]} ;
			if (!idx.count(np)) continue ;
			int nx = idx[np] , nt = gettype(nx) ;

			if (ty + 1 != nt) continue ;
			else if (ty == 2) ins(x , nx , std::min(v[x] , v[nx])) ;
			else ins(x , nx , INF) ;
		}
	}

	printf("%d\n" , dinic()) ;

	return 0 ;
}