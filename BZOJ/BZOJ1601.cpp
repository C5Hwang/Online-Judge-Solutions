#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 300 + 10 ;

struct Edge {
	int x , y , cost ;
}list[MAX_N * MAX_N + MAX_N] ;

int n , cur , fa[MAX_N] ;

int FindSet(int x) {
	if (fa[x] == -1) return x ;
	fa[x] = FindSet(fa[x]) ;

	return fa[x] ;
}

bool cmp(Edge a , Edge b) {
	return a.cost < b.cost ;
}

void ins(int a , int b , int v) {
	list[cur].x = a ;
	list[cur].y = b ;
	list[cur++].cost = v ;
}

int main() {
	scanf("%d" , &n) ;
	for (int i = 1 ; i <= n ; ++i) {
		int v ; scanf("%d" , &v) ;
		ins(0 , i , v) ;
	}
	for (int i = 1 ; i <= n ; ++i) 
		for (int j = 1 ; j <= n ; ++j) {
			int v ; scanf("%d" , &v) ;
			if (i == j) continue ;
			ins(i , j , v) ;
		}

	///

	std::sort(list + 0 , list + cur , cmp) ;

	memset(fa , -1 , sizeof(fa)) ;

	int res = 0 ;
	for (int i = 0 ; i < cur ; ++i) {
		int fx = FindSet(list[i].x) , fy = FindSet(list[i].y) ;
		if (fx == fy) continue ;

		res += list[i].cost ;
		fa[fx] = fy ;
	}

	printf("%d\n" , res) ;

	return 0 ;
}
