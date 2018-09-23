#include <queue>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAX_N = 300 + 10 , INF = 0x3f3f3f3f ,
	  	  dx[4] = {0 , 0 , 1 , -1} ,
		  dy[4] = {1 , -1 , 0 , 0} ;

///

struct data {
	int x , y , t ;
} ;

std::queue<data> que ;
bool ap[MAX_N][MAX_N] ;
int m , t[MAX_N][MAX_N] ;

///

int main() {
	for (int i = 0 ; i < MAX_N ; ++i)
		for (int j = 0 ; j < MAX_N ; ++j)
			t[i][j] = INF ;

	scanf("%d" , &m) ;
	for (int i = 0 ; i < m ; ++i) {
		int x , y , ti ;
		scanf("%d %d %d" , &x , &y , &ti) ;
		t[x][y] = std::min(t[x][y] , ti) ;

		for (int j = 0 ; j < 4 ; ++j) {
			int nx = x + dx[j] , ny = y + dy[j] ;
			if (nx < 0 || ny < 0) continue ;

			t[nx][ny] = std::min(t[nx][ny] , ti) ;
		}
	}

	///
	
	int res = -1 ;
	que.push((data){0 , 0 , 0}) ; ap[0][0] = 1 ;
	while (!que.empty()) {
		data st = que.front() ; que.pop() ;

		if (t[st.x][st.y] == INF) {res = st.t ; break ;}
		else if (st.t >= t[st.x][st.y]) continue ;

		for (int i = 0 ; i < 4 ; ++i) {
			int nx = st.x + dx[i] , ny = st.y + dy[i] ;
			if (nx < 0 || ny < 0) continue ;
			if (ap[nx][ny]) continue ;

			ap[nx][ny] = 1 ; que.push((data){nx , ny , st.t + 1}) ;
		}
	}

	printf("%d\n" , res) ;

	return 0 ;
}
