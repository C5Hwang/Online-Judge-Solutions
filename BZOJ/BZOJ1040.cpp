#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 1000000 + 10 ;

struct Link {
	int num ; Link *next ;
}list[2 * MAX_N] ;
struct Forest {
	int x , y ;
}fr[MAX_N] ;

Link *head[MAX_N] ;
long long res , v[MAX_N] , f[MAX_N][2] ;
int n , cur , tot , id , fa[MAX_N] , ap[MAX_N] , start[2 * MAX_N] ;

int findset(int f) {return fa[f] == -1 ? f : (fa[f] = findset(fa[f])) ;}

void dfs(int x) {
	ap[x] = id ;

	long long s1 = 0 , s2 = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (ap[nx] == id) continue ;

		dfs(nx) ;
		s1 += f[nx][0] ;
		s2 += std::max(f[nx][1] , f[nx][0]) ;
	}

	f[x][1] = s1 + v[x] ;
	f[x][0] = s2 ;
}

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

int main() {
	memset(fa , -1 , sizeof(fa)) ;

	scanf("%d" , &n) ;
	for (int i = 1 ; i <= n ; ++i) {
		int c ;
		scanf("%lld %d" , &v[i] , &c) ;

		int fx = findset(i) , fy = findset(c) ;
		if (fx != fy) fa[fx] = fy , ins(i , c) , ins(c , i) ;
		else fr[tot].x = i , fr[tot++].y = c ;
	}

	///
	
	for (int i = 0 ; i < tot ; ++i)	{
		long long ans ;
		int x = fr[i].x , y = fr[i].y ;

		++id ; dfs(x) ; ans = f[x][0] ;
		++id ; dfs(y) ; ans = std::max(f[y][0] , ans) ;

		res += ans ;
	}

	printf("%lld\n" , res) ;

	return 0 ;
}
