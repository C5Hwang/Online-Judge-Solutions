#include <map>
#include <stdio.h>
#include <stdlib.h>

#define u64 unsigned long long

const int MAX_N = 2e5 + 10 ;

std::map<u64 , bool> ap ;

int n , tot , a[MAX_N] , ans[MAX_N] ;
u64 base , hash[2][MAX_N] , pow[MAX_N] ;

u64 gethash(int p , int l , int r , int x) {
	if (l <= 0 || l > n) return hash[p][r] ;

	return hash[p][r] - hash[p][l] * pow[x] ;
}

int getans(int x) {
	ap.clear() ;
	int sum = 0 ;
	for (int l = 1 ; l + x - 1 <= n ; l += x) {
		int r = l + x - 1 ;

		u64 h = gethash(0 , l - 1 , r , x) * gethash(1 , r + 1 , l , x) ;
		if (!ap[h]) {++sum ; ap[h] = 1 ;}
	}

	return sum ;
}

int main() {
	base = rand() ;
	scanf("%d" , &n) ;
	for (int i = 1 ; i <= n ; ++i) scanf("%d" , &a[i]) ;

	///
	
	pow[0] = 1 ; pow[1] = base ;
	for (int i = 2 ; i <= n ; ++i) pow[i] = pow[i - 1] * base ;

	hash[0][1] = a[1] ;
	for (int i = 2 ; i <= n ; ++i) hash[0][i] = hash[0][i - 1] * base + a[i] ;
	hash[1][n] = a[n] ;
	for (int i = n - 1 ; i ; --i) hash[1][i] = hash[1][i + 1] * base + a[i] ;

	///
	
	int res = 0 ;
	for (int i = 1 ; i <= n ; ++i) {
		int tmp = getans(i) ;
		if (tmp > res) {
			res = tmp ;
			ans[(tot = 0)++] = i ;
		}
		else if (tmp == res) ans[tot++] = i ;
	}

	printf("%d %d\n" , res , tot) ;
	for (int i = 0 ; i < tot ; ++i) {
		printf("%d" , ans[i]) ;
		if (i + 1 != tot) printf(" ") ;
	}

	return 0 ;
}
