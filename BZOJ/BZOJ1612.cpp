#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX_N = 100 + 10 , MAX_M = 4500 + 10 ;

struct Link {
	int num ;
	Link *next ;
}list[MAX_M][2] ;

bool ap[MAX_N] ;
int n , m , cur[2] ;
Link *head[MAX_N][2] ;

void ins(int x , int y) {
	list[cur[0]][0].num = y ;
	list[cur[0]][0].next = head[x][0] ;
	head[x][0] = &list[cur[0]++][0] ;

	list[cur[1]][1].num = x ;
	list[cur[1]][1].next = head[y][1] ;
	head[y][1] = &list[cur[1]++][1] ;
}

int dfs(int x , int st) {
	int sum = 1 ;
	ap[x] = 1 ;

	for (Link *h = head[x][st] ; h ; h = h->next) {
		int nx = h->num ;
		if (ap[nx]) continue ;

		sum += dfs(nx , st) ;
	}

	return sum ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 0 ; i < m ; ++i) {
		int x , y ;
		scanf("%d %d" , &x , &y) ;
		ins(x , y) ;
	}

	///

	int res = 0 ;
	for (int i = 1 ; i <= n ; ++i) {
		memset(ap , 0 , sizeof(ap)) ;

		int s1 = dfs(i , 0) , s2 = dfs(i , 1) ;
		if (s1 + s2 == n + 1) ++res ;
	}
	printf("%d\n" , res) ;

	return 0 ;
}
