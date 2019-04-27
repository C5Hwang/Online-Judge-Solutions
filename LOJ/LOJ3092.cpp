#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 100 + 10 , MAX_M = 2e4 + 10 ;

struct data {int x , y ;} ;

std::queue<data> que ;

bool ap[MAX_N][MAX_M] ;
int n , m , s , ans , tmp[MAX_N] , num[MAX_N][MAX_N] , f[MAX_N][MAX_M] ;

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

void dp() {
	que.push((data){0 , m}) ;
	ap[0][m] = 1 ;

	for (; !que.empty() ;) {
		data pt = que.front() ; que.pop() ;
		if (pt.x == n) {ans = std::max(ans , f[pt.x][pt.y]) ; continue ;}

		int np = pt.x + 1 ;
		for (int i = 0 ; i <= s ; ++i) {
			if (num[np][i] > pt.y) break ;
			
			int nl = pt.y - num[np][i] ;
			f[np][nl] = std::max(f[np][nl] , f[pt.x][pt.y] + i * np) ;

			if (!ap[np][nl]) {ap[np][nl] = 1 ; que.push((data){np , nl}) ;}
		}
	}
}

int main() {
	s = read() ; n = read() ; m = read() ;
	for (int i = 1 ; i <= s ; ++i)
		for (int j = 1 ; j <= n ; ++j) num[j][i] = (read() << 1) + 1 ;

	for (int i = 1 ; i <= n ; ++i) {
		for (int j = 1 ; j <= s ; ++j) tmp[j] = num[i][j] ;

		std::sort(tmp + 1 , tmp + s + 1) ;
		for (int j = 1 ; j <= s ; ++j) num[i][j] = tmp[j] ;
	}

	///

	dp() ;

	printf("%d\n" , ans) ;

	return 0 ;
}