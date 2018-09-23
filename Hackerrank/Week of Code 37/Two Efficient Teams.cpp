#include <queue>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const ll INF = 1e15 ;
const int MAX_M = 500 + 10 , MAX_V = 1100 + 10 , MAX_E = 1e4 + 10 ;

struct Link {
	int num ; ll cap ;
	Link *next , *reg ;
}list[MAX_E] ;

std::queue<int> que ;
std::vector<int> st[MAX_M] ;

Link *head[MAX_V] ;
int ti , ap[MAX_V] , dep[MAX_V] ;
int S , T , n , m , tot , cur , f[MAX_M] , id[2][MAX_M] , c[2][MAX_M] ;

///

void ins(int x , int y , ll v) {
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

bool bfs() {
	dep[S] = 1 ; ap[S] = ++ti ; que.push(S) ;

	for (; !que.empty() ;) {
		int x = que.front() ; que.pop() ;

		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (!h->cap || ap[nx] == ti) continue ;

			ap[nx] = ti ; dep[nx] = dep[x] + 1 ;
			que.push(nx) ;
		}
	}

	return ap[T] == ti ;
}

ll dfs(int x , ll flow) {
	if (x == T || !flow) return flow ;

	ll sum = 0 ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (dep[nx] != dep[x] + 1) continue ;

		ll nf = dfs(nx , std::min(flow , h->cap)) ;
		h->cap -= nf ; flow -= nf ;
		h->reg->cap += nf ; sum += nf ;
	}
	if (flow) dep[x] = -1 ;

	return sum ;
}

ll dinic() {
	ll sum = 0 ;
	for (; bfs() ; sum += dfs(S , INF)) ;

	return sum ;
}

///

void init(int x , int y) {
	for (int i = 0 ; i < m ; ++i) {
		int siz = st[i].size() , area = -1 ;

		for (int j = 0 ; j < siz && area != 2 ; ++j) {
			int t = st[i][j] ;

			if (t == x || t == y) {
				if (area != -1) area = 2 ;
				else if (t == x) area = 0 ;
				else area = 1 ;
			}
		}

		c[0][i] = c[1][i] = 0 ;
		if (area == -1) c[0][i] = c[1][i] = f[i] ;
		else if (area != 2) c[area][i] = f[i] ;
	}
}

ll addedge(int x , int y) {
	cur = 0 ;
	memset(head , 0 , sizeof(head)) ;

	ll sum = 0 ;

	for (int i = 0 ; i < m ; ++i) {
		int siz = st[i].size() ;

		if (c[0][i]) {
			ins(id[0][i] , T , c[0][i]) ;

			for (int j = 0 ; j < siz ; ++j) {
				int t = st[i][j] ;
				if (t == x || t == y) continue ;

				ins(t , id[0][i] , INF) ;
			}
		}

		if (c[1][i]) {
			sum += c[1][i] ;
			ins(S , id[1][i] , c[1][i]) ;

			for (int j = 0 ; j < siz ; ++j) {
				int t = st[i][j] ;
				if (t == x || t == y) continue ;

				ins(id[1][i] , t , INF) ;
			}
		}
	}

	return sum ;
}

ll getans(int x , int y) {
	init(x , y) ; ll sum = addedge(x , y) ;

	for (int i = 0 ; i < m ; ++i) sum += c[0][i] ;
	sum -= dinic() ;

	return sum ;
}

///

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 0 ; i < m ; ++i) {
		int siz ; scanf("%d %d" , &siz , &f[i]) ;

		for (int j = 0 ; j < siz ; ++j) {
			int x ; scanf("%d" , &x) ;
			st[i].push_back(x) ;
		}
	}

	///

	S = 0 ; tot = n ;
	for (int i = 0 ; i < m ; ++i) {id[0][i] = ++tot ; id[1][i] = ++tot ;}
	T = ++tot ;

	///

	ll ans = 0 ;
	for (int i = 1 ; i <= n ; ++i)
		for (int j = i + 1 ; j <= n ; ++j) {
			ll tmp = getans(i , j) ;
			ans = std::max(ans , tmp) ;
		}

	printf("%lld\n" , ans) ;

	return 0 ;
}