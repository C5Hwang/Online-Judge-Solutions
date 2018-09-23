#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 700 + 10 ,
	  	  dx[8] = {-1 , -1 , -1 , 1 , 1 , 1 , 0 , 0} ,
		  dy[8] = {0 , 1 , -1 , 0 , 1 , -1 , 1 , -1} ;

struct data {
	int h , x , y ;
}queue[MAX_N * MAX_N] ;

bool ap[MAX_N][MAX_N] ;
int n , m , cur , h[MAX_N][MAX_N] ;

void dfs(int x , int y) {
	ap[x][y] = 1 ;

	for (int i = 0 ; i < 8 ; ++i) {
		int nx = x + dx[i] , ny = y + dy[i] ;
		if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue ;
		if (ap[nx][ny] || h[x][y] < h[nx][ny]) continue ;

		dfs(nx , ny) ;
	}
}

bool cmp(data a , data b) {return a.h > b.h ;}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 0 ; i < n ; ++i)
		for (int j = 0 ; j < m ; ++j)
			scanf("%d" , &h[i][j]) , queue[cur++] = (data){h[i][j] , i , j} ;

	///

	int res = 0 ;
	std::sort(queue + 0 , queue + cur , cmp) ;	
	for (int i = 0 ; i < cur ; ++i) {
		int x = queue[i].x , y = queue[i].y ;
		if (ap[x][y]) continue ;
		dfs(x , y) , ++res ;
	}

	printf("%d\n" , res) ;

	return 0 ;
}
