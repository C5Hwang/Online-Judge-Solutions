#include <queue>
#include <math.h>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

#define db double
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const db eps = 1e-6 ;
const int MAX_N = 50 + 5 , MAX_M = 500 + 10 , MAX_E = 3e3 + 10 , INF = 0x3f3f3f3f ;

struct limit {int x , y ;} ;
struct data {int num , idx ;} ;
struct Link {
	int num ; db cap ;
	Link *next , *reg ;
}list[MAX_E << 1] ;

std::queue<int> que ;
std::vector<data> eg[MAX_N] ;
std::vector<limit> lim[MAX_N] ;

db f[MAX_N] ;
Link *head[MAX_M] ;
int T , ti , cur , dep[MAX_M] , ap[MAX_M] ;
int n , m , k , prt[MAX_M] , in[MAX_N] , tl[MAX_N] ;

///

void ins(int x , int y , db v) {
	list[cur].num = y ;
	list[cur].cap = v ;
	list[cur].next = head[x] ;
	list[cur].reg = &list[cur^1] ;
	head[x] = &list[cur++] ;

	list[cur].num = x ;
	list[cur].cap = 0 ;
	list[cur].next = head[y] ;
	list[cur].reg = &list[cur^1] ;
	head[y] = &list[cur++] ;
}

void init() {
	ti = cur = 0 ; T = m + 1 ;
	memset(ap , 0 , sizeof(ap)) ;
	memset(head , 0 , sizeof(head)) ;
}

db dfs(int x , db f) {
	if (x == T || f < eps) return f ;

	db sum = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (dep[nx] != dep[x] + 1) continue ;

		db nf = dfs(nx , std::min(f , h->cap)) ;
		sum += nf ; h->reg->cap += nf ;
		f -= nf ; h->cap -= nf ;
	}
	if (f > eps) dep[x] = -1 ;

	return sum ;
}

bool bfs() {
	que.push(0) ;
	dep[0] = 1 ; ap[0] = ++ti ;

	for (; !que.empty() ;) {
		int x = que.front() ; que.pop() ;

		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (ap[nx] == ti || h->cap < eps) continue ;

			que.push(nx) ;
			dep[nx] = dep[x] + 1 ; ap[nx] = ti ;
		}
	}

	return ap[T] == ti ;
}

db dinic() {
	db sum = 0 ;
	for (; bfs() ; sum += dfs(0 , INF)) ;

	return sum ;
}

///

db build(int x , db k) {
	init() ;

	db sum = 0 ;
	int s1 = eg[x].size() , s2 = lim[x].size() ;

	for (int i = 0 ; i < s1 ; ++i) {
		int nx = eg[x][i].num ;
		db tmp = k - f[nx] ;

		if (tmp > eps) ins(0 , eg[x][i].idx , tmp) , sum += tmp ;
		else ins(eg[x][i].idx , T , -tmp) ;
	}

	for (int i = 0 ; i < s2 ; ++i) {
		limit *p = &lim[x][i] ;

		ins(p->y , p->x , INF) ;
	}

	return sum ;
}

bool check(int x , db k) {
	db sum = 0 ;
	int siz = eg[x].size() ;

	for (int i = 0 ; i < siz ; ++i) {
		int nx = eg[x][i].num ;
		sum += f[nx] - k ;
	}
	sum += build(x , k) ;

	return sum - dinic() > eps ;
}

void work(int x) {
	int siz = eg[x].size() ;
	if (!siz) {f[x] = 0 ; return ;}

	db L = 0 , R = 0 ;
	for (int i = 0 ; i < siz ; ++i) R = std::max(R , f[eg[x][i].num] + 1) ;

	for (; fabs(L - R) > eps ;) {
		db mid = (L + R) / 2 ;
		if (check(x , mid)) L = mid ;
		else R = mid ;
	}

	f[x] = L + 1 ;
}

void topo() {
	for (int i = 1 ; i <= n ; ++i) if (!in[i]) que.push(i) ;

	int tot = 0 ;
	for (; !que.empty() ;) {
		int x = que.front() , siz = eg[x].size() ;
		que.pop() ; tl[++tot] = x ;

		for (int i = 0 ; i < siz ; ++i) {
			int nx = eg[x][i].num ;

			--in[nx] ;
			if (!in[nx]) que.push(nx) ;
		}
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
	n = read() ; m = read() ; k = read() ;
	for (int i = 1 ; i <= m ; ++i) {
		int x , y ; x = read() ; y = read() ;

		eg[x].push_back((data){y , i}) ; prt[i] = x ; ++in[y] ;
	}
	for (int i = 0 ; i < k ; ++i) {
		int x , y ; x = read() ; y = read() ;

		lim[prt[x]].push_back((limit){x , y}) ;
	}

	///

	topo() ;

	for (int i = n ; i ; --i) work(tl[i]) ;
	printf("%0.3lf\n" , f[1]) ;

	return 0 ;
}