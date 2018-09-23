#include <stdio.h>
#include <stdlib.h>

const int MAX_N = 10 + 5 , MAX_N2 = 2e3 + 10 , MAX_T = 1e7 + 20 , mod = 2004 ;

bool ap[MAX_T] ;
int lis[MAX_N] , ti[MAX_T] ;
int n , tot , a , b , mi[MAX_N] , num[MAX_N2] ;

void dfs(int x , int sum , int ty) {
	if (x == n) {
		if (!ap[sum]) num[tot++] = sum ;
		ap[sum] = 1 ; ti[sum] += ty ;

		return ;
	}

	dfs(x + 1 , sum , ty) ; dfs(x + 1 , sum + mi[x] + 1 , -ty) ;
}

int getf(int x) {
	if (x < 0) return 0 ;

	int dn = n , un = n + x , cs[MAX_N] ;

	for (int i = 2 ; i <= dn ; ++i) cs[i] = 0 ;
	cs[2] = dn / 2 + dn / 4 + dn / 8 ;
	cs[3] = dn / 3 + dn / 9 ; cs[5] = dn / 5 ; cs[7] = dn / 7 ;

	for (int i = un ; i > x ; --i) lis[i - x - 1] = i ;
	for (int i = 2 ; i <= dn ; ++i) {
		if (!cs[i]) continue ;

		for (int j = 0 ; j < dn && cs[i] ; ++j)
			for (; cs[i] && !(lis[j] % i) ; --cs[i] , lis[j] /= i) ;
	}

	int s = 1 ;
	for (int i = 0 ; i < dn ; ++i) (s *= (lis[i] % mod)) %= mod ;

	return s ;
}

int cal(int x) {
	int s = 0 ;
	for (int i = 0 ; i < tot ; ++i) {
		int m = num[i] ;
		if (m > x) continue ;

		int tmp = getf(x - m) * abs(ti[m]) % mod , f = ti[m] > 0 ? 1 : -1 ;

		s = (s + f * tmp + mod) % mod ;
	}

	return s ;
}

int main() {
	scanf("%d %d %d" , &n , &a, &b) ;
	for (int i = 0 ; i < n ; ++i) scanf("%d" , &mi[i]) ;
	dfs(0 , 0 , 1) ;

	///

	int ans = (cal(b) - cal(a - 1) + mod) % mod ;
	printf("%d\n" , ans) ;

	return 0 ;
}
