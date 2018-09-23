#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 200 + 10 , INF = 0x3f3f3f3f ;

struct Queue {
	int num , bh ;
}qe[MAX_N] ;

char ch[MAX_N][MAX_N] ;
int f[MAX_N][MAX_N][MAX_N] , L , R ;
int n , m , x , y , p , op[MAX_N] , ti[MAX_N] ;

int adn(int x , int y) {return abs(x - y) ;}

void push(int x , int y) {
	qe[++R].num = x ; qe[R].bh = y ;

	while (R > L && qe[R - 1].num + adn(y , qe[R - 1].bh) < qe[R].num + adn(y , qe[R].bh))
		std::swap(qe[R] , qe[R - 1]) , --R ;
}

void pop(int y) {if (qe[L].bh == y) ++L ;}

int main() {
	scanf("%d %d %d %d %d" , &n , &m , &x , &y , &p) ;
	for (int i = 1 ; i <= n ; ++i) {
		getchar() ;
		for (int j = 1 ; j <= m ; ++j) scanf("%c" , &ch[i][j]) ;
	}
	for (int i = 1 ; i <= p ; ++i) {
		int x , y , o ;
		scanf("%d %d %d" , &x , &y , &o) ;
		ti[i] = y - x + 1 ; op[i] = o ;
	}

	///
	
	for (int k = 0 ; k <= p ; ++k)
		for (int i = 1 ; i <= n ; ++i)
			for (int j = 1 ; j <= m ; ++j)
				f[k][i][j] = -INF ;

	///
	
	int res = 0 ;
	f[0][x][y] = 0 ;
	for (int k = 1 ; k <= p ; ++k) {
		int st , ed , ind ;
		if (op[k] <= 2)	{
			if (op[k] == 1) st = n , ed = 0 , ind = -1 ;
			else st = 1 , ed = n + 1 , ind = 1 ;
			
			///
			
			for (int j = 1 ; j <= m ; ++j) {
				int start = st ;
				L = 1 ; R = 0 ;
	
				for (int i = st ; i != ed ; i += ind) {
					if (ch[i][j] == 'x') {L = 1 ; R = 0 ; start = i ; continue ;}
					if (abs(i - start) > ti[k]) pop(i - ti[k] * ind - 1 * ind) ;
					push(f[k - 1][i][j] , i) ;
	
					f[k][i][j] = qe[L].num + adn(i , qe[L].bh) ;
	
					res = std::max(res , f[k][i][j]) ;
				}
			}
		}
		else {
			if (op[k] == 3) st = m , ed = 0 , ind = -1 ;
			else st = 1 , ed = m + 1 , ind = 1 ;
			
			///
			
			for (int i = 1 ; i <= n ; ++i) {
				int start = st ;
				L = 1 ; R = 0 ;
	
				for (int j = st ; j != ed ; j += ind) {
					if (ch[i][j] == 'x') {L = 1 ; R = 0 ; start = j ; continue ;}
					if (abs(j - start) > ti[k]) pop(j - ti[k] * ind - 1 * ind) ;
					push(f[k - 1][i][j] , j) ;
	
					f[k][i][j] = qe[L].num + adn(j , qe[L].bh) ;
	
					res = std::max(res , f[k][i][j]) ;
				}
			}
		}	
	}

	printf("%d\n" , res) ;

	return 0 ;
}
