#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 3e4 + 10 , INF = 3e4 + 10 ;

struct Link {
	int num ; Link *next ;
}list[2 * MAX_N] ;
struct Tree {
	int sum , maximum ;
}tre[4 * MAX_N] ;

///

Link *head[MAX_N] ;
int n , m , cur , v[MAX_N] ; char q[20] ;
int time , siz[MAX_N] , fa[MAX_N] , dep[MAX_N] , lifa[MAX_N] , hson[MAX_N] , bh[MAX_N] ;

///

void operate(int &x , int y , int op) {  //0->Sum,1->Max
	if (op) x = std::max(x , y) ;
	else x += y ;
}

///

void update(int t) {
	int lson = t * 2 , rson = t * 2 + 1 ;

	tre[t].sum = tre[lson].sum + tre[rson].sum ;
	tre[t].maximum = std::max(tre[lson].maximum , tre[rson].maximum) ;
}

void change(int t , int x , int y , int f , int v) {
	if (y < f || f < x) return ;
	if (x == f && y == f) {
		tre[t].sum = tre[t].maximum = v ;
		return ;
	}

	int mid = (x + y) >> 1 ;
	change(t * 2 , x , mid , f , v) ;
	change(t * 2 + 1 , mid + 1 , y , f , v) ;

	update(t) ;
}

int GetAns(int t , int x , int y , int fx , int fy , int op) {
	if (fx <= x && y <= fy) {
		if (op) return tre[t].maximum ;
		else return tre[t].sum ;
	}
	if (y < fx || fy < x) {
		if (op) return -INF ;
		else return 0 ;
	}

	int mid = (x + y) >> 1 ,
		s1 = GetAns(t * 2 , x , mid , fx , fy , op) ,
		s2 = GetAns(t * 2 + 1 , mid + 1 , y , fx , fy , op) ;

	operate(s1 , s2 , op) ;

	return s1 ;
}

///

int query(int x , int y , int op) {
	int res ;
	if (op) res = -INF ;
	else res = 0 ;

	while (lifa[x] != lifa[y]) {
		if (dep[lifa[x]] > dep[lifa[y]]) std::swap(x , y) ;

		operate(res , GetAns(1 , 1 , n , bh[lifa[y]] , bh[y] , op) , op) ;
		y = fa[lifa[y]] ;
	}

	if (dep[x] > dep[y]) std::swap(x , y) ;
	operate(res , GetAns(1 , 1 , n , bh[x] , bh[y] , op) , op) ;

	return res ;
}

///

void dfs1(int x , int f) {
	fa[x] = f ;

	long long Msiz = 0 , Mson = -1 , sum = 1 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == f) continue ;

		dep[nx] = dep[x] + 1 ; dfs1(nx , x) ;
		if (siz[nx] > Msiz) {Msiz = siz[nx] ; Mson = nx ;}
		sum += siz[nx] ;
	}

	hson[x] = Mson ; siz[x] = sum ;
}

void dfs2(int x , int f) {
	bh[x] = ++time ; lifa[x] = f ;
	change(1 , 1 , n , time , v[x]) ;
	if (hson[x] >= 0) dfs2(hson[x] , f) ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa[x] || nx == hson[x]) continue ;

		dfs2(nx , nx) ;
	}
}

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

///

int main() {
	scanf("%d" , &n) ;
	for (int i = 1 ; i < n ; ++i) {
		int x , y ;
		scanf("%d %d" , &x , &y) ;
		ins(x , y) ; ins(y , x) ;
	}
	for (int i = 1 ; i <= n ; ++i)
		scanf("%d" , &v[i]) ;

	///
	
	dep[1] = 0 ;
	dfs1(1 , -1) ;
	time = 0 ;
	dfs2(1 , 1) ;

	///

	scanf("%d" , &m) ;
	for (int i = 0 ; i < m ; ++i) {
		int x , y ;
		scanf("%s %d %d" , q , &x , &y) ;

		if (q[0] == 'C') change(1 , 1 , n , bh[x] , y) ;
		else if (q[1] == 'S') printf("%d\n" , query(x , y , 0)) ;
		else printf("%d\n" , query(x , y , 1)) ;
	}

	return 0 ;
}
