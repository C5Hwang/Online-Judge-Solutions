#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 5e3 + 10 , MAX_P = 2e5 + 10 , MAX_M = 5e5 + 10 , INF = 0x3f3f3f3f ;

struct Link {
	int num , cap ;
	Link *next , *reg ;
}list[MAX_M << 1] ;
struct Node {
	int idx ;
	Node *ch[2] ;

	void init() {idx = 0 ; ch[0] = ch[1] = NULL ;}
}tre[MAX_P] ;

std::queue<int> que ;

Link *head[MAX_P] ;
Node *root[MAX_N] ;
int T , ti , tot , cnt , ap[MAX_P] , dep[MAX_P] ;
int n , sum , cur , ma , a[MAX_N] , b[MAX_N] , w[MAX_N] , l[MAX_N] , r[MAX_N] , p[MAX_N] , bh[MAX_N][2] ;

///

void ins(int x , int y , int v) {
	if (x == -1 || y == -1) return ;

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

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

///

int dfs(int x , int f) {
	if (x == T || !f) return f ;

	int s = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (dep[nx] != dep[x] + 1) continue ;

		int nf = dfs(nx , std::min(f , h->cap)) ;
		s += nf ; h->reg->cap += nf ;
		f -= nf ; h->cap -= nf ;
	}
	if (f) dep[x] = -1 ;

	return s ;
}

bool bfs() {
	que.push(0) ;
	ap[0] = ++ti ; dep[0] = 1 ;

	for (; !que.empty() ;) {
		int x = que.front() ; que.pop() ;

		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (ap[nx] == ti || !h->cap) continue ;

			que.push(nx) ;
			ap[nx] = ti ; dep[nx] = dep[x] + 1 ;
		}
	}

	return ap[T] == ti ;
}

int dinic() {
	int sum = 0 ;
	for (; bfs() ; sum += dfs(0 , INF)) ;

	return sum ;
}

///

void build(Node *ort , Node *&rt , int x , int y , int f , int p) {
	if (f < x || y < f) return ;

	rt = &tre[cnt++] ; *rt = *ort ; rt->idx = ++tot ;
	if (x == y) {
		ins(rt->idx , ort->idx , INF) ; ins(rt->idx , p , INF) ;
		return ;
	}

	int mid = (x + y) >> 1 ;
	build(ort->ch[0] , rt->ch[0] , x , mid , f , p) ;
	build(ort->ch[1] , rt->ch[1] , mid + 1 , y , f , p) ;

	ins(rt->idx , rt->ch[0]->idx , INF) ; ins(rt->idx , rt->ch[1]->idx , INF) ;
}

void find(Node *rt , int x , int y , int fx , int fy , int p) {
	if (y < fx || fy < x) return ;
	if (fx <= x && y <= fy) {ins(p , rt->idx , INF) ; return ;}

	int mid = (x + y) >> 1 ;
	find(rt->ch[0] , x , mid , fx , fy , p) ; find(rt->ch[1] , mid + 1 , y , fx , fy , p) ;
}

///

int main() {
	n = read() ;
	for (int i = 1 ; i <= n ; ++i) {
		a[i] = read() ; b[i] = read() ; w[i] = read() ; l[i] = read() ; r[i] = read() ; p[i] = read() ;
		bh[i][0] = ++tot ; bh[i][1] = ++tot ; sum += b[i] ; sum += w[i] ; ma = std::max(ma , a[i]) ;
	}
	T = ++tot ;

	///

	for (int i = 1 ; i <= n ; ++i) 
		ins(0 , bh[i][0] , b[i]) , ins(bh[i][0] , bh[i][1] , p[i]) , ins(bh[i][0] , T , w[i]) ;

	(root[0] = &tre[cnt++])->init() ;
	root[0]->ch[0] = root[0]->ch[1] = root[0] ; root[0]->idx = -1 ;
	for (int i = 1 ; i <= n ; ++i) build(root[i - 1] , root[i] , 0 , ma , a[i] , bh[i][0]) ;
	for (int i = 1 ; i <= n ; ++i) find(root[i - 1] , 0 , ma , l[i] , r[i] , bh[i][1]) ;

	printf("%d\n" , sum - dinic()) ;

	return 0 ;
}