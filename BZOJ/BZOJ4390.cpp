#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 5e4 + 10 , lgN = 25 ;

struct Link {
	int num ;
	Link *next ;
}list[2 * MAX_N] ;

Link *head[MAX_N] ;
int n , k , cur , res ;
int dep[MAX_N] , sum[MAX_N] , f[MAX_N][lgN] ;

///

void dfs(int x , int fa) {
	f[x][0] = fa ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa) continue ;

		dep[nx] = dep[x] + 1 ;
		dfs(nx , x) ;
	}
}

int GetLca(int x , int y) {
	if (dep[x] > dep[y]) std::swap(x , y) ;

	for (int i = 20 ; i >= 0 ; --i) {
		if ((1 << i) > n) continue ;

		int k = f[y][i] ;
		if (dep[k] >= dep[x]) y = k ;
	}
	if (x == y) return x ;

	for (int i = 20 ; i >= 0 ; --i) {
		if ((1 << i) > n) continue ;

		int tx = f[x][i] , ty = f[y][i] ;
		if (tx != ty) x = tx , y = ty ;
	}

	return f[x][0] ;
}

int FindAns(int x) {
	int s = sum[x] ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == f[x][0]) continue ;

		s += FindAns(nx) ;
	}

	res = std::max(res , s) ;
	return s ;
}

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

///

int main() {
	scanf("%d %d" , &n , &k) ;
	for (int i = 1; i < n ; ++i) {
		int x , y ; scanf("%d %d" , &x , &y) ;
		ins(x , y) ; ins(y , x) ;
	}

	///
	
	dep[1] = 1 ;
	dfs(1 , 1) ;
	for (int j = 1 ; (1 << j) <= n ; ++j)
		for (int i = 1 ; i <= n ; ++i) {
			int k = f[i][j - 1] ;
			f[i][j] = f[k][j - 1] ;
		}

	///
	
	for (int i = 0 ; i < k ; ++i) {
		int x , y , fa ;
		scanf("%d %d" , &x , &y) ;

		fa = GetLca(x , y) ;
		++sum[x] ; ++sum[y] ; --sum[fa] ;
		if (fa != 1) --sum[f[fa][0]] ;
	}

	res = 0 ;
	FindAns(1) ;

	printf("%d\n" , res) ;

	return 0 ;
}
