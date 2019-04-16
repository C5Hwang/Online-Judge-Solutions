#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 4e4 + 10 , MAX_K = 10 + 5 , INF = 0x7FFFFFFF ;

int BIT[MAX_N] ;
int n , k , L , R , sum , a[MAX_N] , f[MAX_K][MAX_N] ;

inline int lowbit(int x) {return x & (-x) ;}

inline void add(int x , int a) {
	for (; x <= n ; x += lowbit(x)) BIT[x] += a ;
}

inline int getsum(int x) {
	int sum = 0 ;
	for (; x ; x -= lowbit(x)) sum += BIT[x] ;

	return sum ;
}

void modify(int x , int y) {
	for (; R < y ; ++R , sum += getsum(n) - getsum(a[R]) , add(a[R] , 1)) ;
	for (; x < L ; --L , sum += getsum(a[L] - 1) , add(a[L] , 1)) ;

	for (; L < x ; sum -= getsum(a[L] - 1) , add(a[L] , -1) , ++L) ;
	for (; y < R ; sum -= getsum(n) - getsum(a[R]) , add(a[R] , -1) , --R) ;
}

void work(int ty , int x , int y , int fx , int fy) {
	if (x > y) return ;

	int mid = (x + y) >> 1 , res = INF , pl = -1 ;
	for (int i = std::min(fy , mid) ; i >= fx ; --i) {
		if (f[ty - 1][i - 1] == INF) continue ;

		modify(i , mid) ;
		int tmp = sum + f[ty - 1][i - 1] ;
		if (tmp < res) {res = tmp ; pl = i ;}
	}
	f[ty][mid] = res ;

	work(ty , x , mid - 1 , fx , pl) ;
	work(ty , mid + 1 , y , pl , fy) ;
}

int main() {
	scanf("%d %d" , &n , &k) ;
	for (int i = 1 ; i <= n ; ++i) scanf("%d" , &a[i]) ;
	for (int i = 1 ; i <= n ; ++i) f[0][i] = INF ;
	f[0][0] = 0 ;

	///

	L = 1 ; R = sum = 0 ;
	for (int i = 1 ; i <= k ; ++i) {
		for (int j = 0 ; j < i ; ++j) f[i][j] = INF ;
		work(i , i , n , 1 , n) ;
	}
	printf("%d\n" , f[k][n]) ;

	return 0 ;
}