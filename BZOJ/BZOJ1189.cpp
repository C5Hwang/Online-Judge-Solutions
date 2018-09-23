#include <queue>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 20 + 10 , MAX_TOT = 400 + 10 , MAX_E = 4e6 + 10 , MAX_V = 1e5 + 10 , INF = 0x3f3f3f3f ,
		  dx[4] = {0 , 0 , 1 , -1} ,
		  dy[4] = {1 , -1 , 0 , 0} ;

struct Link {
	int num , cap ;
	Link *next , *reg ;
}list[MAX_E] ;

struct data {int x , y ;} ;

std::queue<data> q ;
std::queue<int> dq ;

Link *head[MAX_V] ;
bool vis[MAX_N][MAX_N] ;
char map[MAX_N][MAX_N] ;
int nti[MAX_TOT][MAX_TOT] , dis[MAX_N][MAX_N] ;
int n , m , tot , t1 , t2 , bh[MAX_N][MAX_N] , peo[MAX_TOT] , dor[MAX_TOT] ;
int S , T , tv , ti , cur , pv[MAX_TOT] , dv[MAX_TOT][MAX_TOT] , dep[MAX_V] , ap[MAX_V] ;

///

void bfs(int S , int x , int y) {
	memset(vis , 0 , sizeof(vis)) ;
	memset(dis , 0 , sizeof(dis)) ;
	
	q.push((data){x , y}) ; dis[x][y] = 0 ; vis[x][y] = 1 ;
	while (!q.empty()) {
		data p = q.front() ; q.pop() ;
		if (map[p.x][p.y] == 'D') continue ;
		
		for (int i = 0 ; i < 4 ; ++i) {
			data np = (data){p.x + dx[i] , p.y + dy[i]} ;
			if (np.x < 0 || np.x >= n || np.y < 0 || np.y >= m) continue ;
			if (vis[np.x][np.y] || map[np.x][np.y] == 'X') continue ;
			
			vis[np.x][np.y] = 1 ;
			dis[np.x][np.y] = dis[p.x][p.y] + 1 ;
			q.push(np) ;
			
			if (map[np.x][np.y] == 'D') {
				int T = bh[np.x][np.y] ;
				nti[S][T] = dis[np.x][np.y] ;
			}
		}
	}
}

///

bool CheckLink() {
	dq.push(S) ;
	ap[S] = ++ti ; dep[S] = 1 ;
	
	while (!dq.empty()) {
		int x = dq.front() ; dq.pop() ;
		
		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (ap[nx] == ti || !h->cap) continue ;
			
			dq.push(nx) ;
			ap[nx] = ti ; dep[nx] = dep[x] + 1 ;
		}
	}
	
	return ap[T] == ti ;
}

int dfs(int x , int flow) {
	if (x == T || !flow) return flow ;
	
	int sum = 0 ; 
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (dep[nx] != dep[x] + 1) continue ;
		
		int nf = dfs(nx , std::min(flow , h->cap)) ;
		flow -= nf ; h->cap -= nf ;
		sum += nf ; h->reg->cap += nf ;
	}
	
	if (!flow) dep[x] = -1 ;
	return sum ;
}

int Dinic() {
	int sum = 0 ;
	while (CheckLink()) sum += dfs(S , INF) ;
	
	return sum ;
}

void ins(int x , int y , int v) {
	list[cur].num = y ;
	list[cur].cap = v ;
	list[cur].next = head[x] ;
	list[cur].reg = &list[cur + 1] ;
	head[x] = &list[cur++] ;
	
	list[cur].num = x ;
	list[cur].cap = 0 ;
	list[cur].next = head[y] ;
	list[cur].reg = &list[cur - 1] ;
	head[y] = &list[cur++] ;
}

void init() {
	cur = 0 ;
	memset(head , 0 , sizeof(head)) ;
}

bool check(int x) {
	init() ;
	
	tv = 0 ;
	for (int i = 0 ; i < t1 ; ++i) pv[peo[i]] = ++tv ;
	for (int i = 0 ; i < t2 ; ++i)
		for (int j = 1 ; j <= x ; ++j)
			dv[dor[i]][j] = ++tv ;
			
	S = 0 ; T = ++tv ;
	
	///
	
	for (int i = 0 ; i < t1 ; ++i)
		for (int j = 0 ; j < t2 ; ++j) {
			int pi = peo[i] , dj = dor[j] , t = nti[pi][dj] ;
			if (!t) continue ;
			
			if (t <= x) ins(pv[pi] , dv[dj][t] , 1) ;
		}
		
	for (int i = 0 ; i < t1 ; ++i) ins(S , pv[peo[i]] , 1) ;
	for (int i = 0 ; i < t2 ; ++i)
		for (int j = 1 ; j <= x ; ++j) {
			if (j < x) ins(dv[dor[i]][j] , dv[dor[i]][j + 1] , INF) ;
			ins(dv[dor[i]][j] , T , 1) ;
		}
	
	int sum = Dinic() ;
	
	return sum == t1 ;
}

///

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 0 ; i < n ; ++i)
		scanf("%s" , map[i]) ;
	for (int i = 0 ; i < n ; ++i)
		for (int j = 0 ; j < m ; ++j)
			bh[i][j] = ++tot ;
	
	///
	
	for (int i = 0 ; i < n ; ++i)
		for (int j = 0 ; j < m ; ++j)
			if (map[i][j] == '.') peo[t1++] = bh[i][j] ;
			else if (map[i][j] == 'D') dor[t2++] = bh[i][j] ;
	for (int i = 0 ; i < n ; ++i)
		for (int j = 0 ; j < m ; ++j)
			if (map[i][j] == '.') bfs(bh[i][j] , i , j) ;
	
	///
	
	bool ans = 0 ;
	int L = -1 , R = n * m ;
	while (L + 1 < R) {
		int mid = (L + R) >> 1 ;
		
		if (check(mid)) R = mid , ans = 1 ;
		else L = mid ;
	}
	
	if (ans) printf("%d\n" , R) ;
	else printf("impossible\n") ;
	
	return 0 ;
}
