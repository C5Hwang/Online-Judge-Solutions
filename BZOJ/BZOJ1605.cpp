#include <stdio.h>
#include <stdlib.h>

#define f(q , i , j) f[q][i + MAX_K][j + MAX_K]
#define g(q , i , j) g[q][i + MAX_K][j + MAX_K]

const char oper[4] = {'E' , 'N' , 'S' , 'W'} ;
const int MAX_N = 1000 + 10 , MAX_K = 30 + 10 , INF = 0x3f3f3f3f ,
	  	  dx[4] = {1 , 0 , 0 , -1} , dy[4] = {0 , 1 , -1 , 0} ;

struct data {
	int x , y ;
}t[MAX_N] ;

char path[MAX_K] ;
bool mow[MAX_N][MAX_N] ;
int n , m , k , f[MAX_K][2 * MAX_K][2 * MAX_K] ;
long long g[MAX_K][2 * MAX_K][2 * MAX_K] , fac[MAX_K] ;

void GetPath(long long pt) {
	for (int i = 0 ; i < k ; ++i , pt /= 4)
		path[i] = oper[pt % 4] ;
}

int main() {
	scanf("%d %d %d" , &n , &m , &k) ;
	for (int i = 0 ; i < n ; ++i)
		scanf("%d %d" , &t[i].x , &t[i].y) ;
	for (int i = 0 ; i < m ; ++i) {
		int x , y ;
		scanf("%d %d" , &x , &y) ;
		mow[x][y] = 1 ;
	}

	///
	
	fac[0] = 1 ;
	for (int i = 1 ; i <= k ; ++i) fac[i] = fac[i - 1] * 4 ;

	for (int i = -k ; i <= k ; ++i)
		for (int j = -k ; j <= k ; ++j)
			f(0 , i , j) = -INF ;

	///

	f(0 , 0 , 0) = 0 ;
	for (int q = 1 ; q <= k ; ++q)
		for (int i = -k ; i <= k ; ++i)
			for (int j = -k ; j <= k ; ++j) {
				int cow = 0 ;
				for (int p = 0 ; p < n ; ++p) {
					int nx = t[p].x + i , ny = t[p].y + j ;
					if (nx < 0 || ny < 0) continue ;

					if (mow[nx][ny]) ++cow ;
				}

				long long ng = 0 ;
				int nf = -INF , s = 0 ;
				for (int p = 0 ; p < 4 ; ++p) {
					int oi = i - dx[p] , oj = j - dy[p] ;
					if (oi > k || oj > k || oi < -k || oj < -k) continue ;

					int of = f(q - 1 , oi , oj) ;
					long long og = g(q - 1 , oi , oj) ;

					if (nf == -1 || nf < of) {nf = of ; ng = og ; s = p ;}
					else if (nf == of && ng > og) ng = og , s = p ;
				}

				f(q , i , j) = nf + cow ;
				g(q , i , j) = ng + fac[k - q] * s ;
			}

	///

	int res = -1 ;
	long long pt = 0 ;
	for (int i = -k ; i <= k ; ++i)
		for (int j = -k ; j <= k ; ++j) {
			int nf = f(k , i , j) ;
			long long ng = g(k , i , j) ;
			if (res < nf) res = nf , pt = ng ;
			else if (res == nf && pt > ng) pt = ng ;
		}

	GetPath(pt) ;
	printf("%d\n" , res) ;
	for (int i = k - 1 ; i >= 0 ; --i) printf("%c" , path[i]) ;
	printf("\n") ;

	return 0 ;
}
