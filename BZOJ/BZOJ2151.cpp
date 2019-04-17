#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 2e5 + 10 , INF = 0x3f3f3f3f ;

struct data {
	int sum , cnt ;

	friend bool operator <(data a , data b) {return a.sum < b.sum || (a.sum == b.sum && a.cnt < b.cnt) ;}
}f[MAX_N][2][2] ;

int n , m , L , R , a[MAX_N] ;

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

data check(int k) {
	f[1][0][0] = (data){0 , 0} ;
	f[1][0][1] = (data){-INF , 0} ;
	f[1][1][0] = (data){-INF , 0} ;
	f[1][1][1] = (data){a[1] - k , 1} ;

	for (int i = 2 ; i <= n ; ++i) {
		f[i][0][0] = std::max(f[i - 1][0][0] , f[i - 1][1][0]) ;
		f[i][1][0] = (data){f[i - 1][0][0].sum + a[i] - k , f[i - 1][0][0].cnt + 1} ;

		f[i][0][1] = std::max(f[i - 1][0][1] , f[i - 1][1][1]) ;
		f[i][1][1] = (data){f[i - 1][0][1].sum + a[i] - k , f[i - 1][0][1].cnt + 1} ;
	}

	return std::max(std::max(f[n][0][1] , f[n][0][0]) , f[n][1][0]) ;
}

int main() {
	n = read() ; m = read() ;
	for (int i = 1 ; i <= n ; ++i) a[i] = read() ;

	L = R = a[1] ;
	for (int i = 1 ; i <= n ; ++i)
		L = std::min(L , a[i]) , R = std::max(R , a[i]) ,
		L = std::min(L , -a[i]) , R = std::max(R , -a[i]) ;

	///

	if (m > n / 2) {
		printf("Error!\n") ;
		return 0 ;
	}

	for (; L + 1 < R ;) {
		int mid = (L + R) >> 1 ;
		if (check(mid).cnt > m) L = mid ;
		else R = mid ;
	}

	if (check(R).cnt < m) --R ;
	printf("%d\n" , check(R).sum + m * R) ;

	return 0 ;
}