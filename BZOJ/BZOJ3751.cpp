#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 100 + 10 , MAX_M = 1e6 + 10 , MAX_L = 1e4 + 10 ,
	  	  prime[6] = {10253 , 20507 , 30011 , 30253 , 30703 , 40063} ;

short fh[MAX_N] ;
char num[MAX_N][MAX_L] ;
int n , m , mnum[MAX_N] , vis[MAX_M];

void GetModNum(int p) {
	for (int i = 0 ; i <= n ; ++i) {
		int t = 1 , L = fh[i] == -1 ? 1 : 0 , R = strlen(num[i]) , ans = 0 ;

		for (int j = R - 1 ; j >= L ; --j) {
			int temp = (num[i][j] - '0') * t % p ;
			ans = (ans + temp) % p ;
			t = (t * 10) % p ;
		}

		mnum[i] = ans ;
	}
}

int GetSum(int xn , int p) {
	int ans = 0 , x = 1 ;
	for (int i = 0 ; i <= n ; ++i) {
		int temp = mnum[i] * x % p ;

		ans = (ans + p + temp * fh[i]) % p ;
		x = (x * xn) % p ;
	}

	return ans ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 0 ; i <= n ; ++i) {
		scanf("%s" , num[i]) ;
		if (num[i][0] == '-') fh[i] = -1 ;
		else fh[i] = 1 ;
	}

	///
	
	for (int i = 0 ; i < 6 ; ++i) {
		int p = prime[i] ;
		GetModNum(p) ;

		for (int j = 1 ; j <= std::min(p , m) ; ++j)
			if (!GetSum(j , p))
				for (int k = j ; k <= m ; k += p) ++vis[k] ;
	}

	int tot = 0 ;
	for (int i = 1 ; i <= m ; ++i) if (vis[i] == 6) ++tot ;
	printf("%d\n" , tot) ;
	for (int i = 1 ; i <= m ; ++i) if (vis[i] == 6) printf("%d\n" , i) ;

	return 0 ;
}
