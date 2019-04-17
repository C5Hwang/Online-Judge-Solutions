#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const ll INF = 1e15 ;
const int MAX_N = 1e5 + 10 ;

struct data {
	ll sum ; int cnt ;

	friend bool operator <(data a , data b) {return a.sum < b.sum || (a.sum == b.sum && a.cnt < b.cnt) ;}
}f[MAX_N][2] ;

int n , m , L , R , a[MAX_N] ;

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

data check(int ty , int k) {
	f[1][0] = (data){0 , 0} ;
	f[1][1] = (data){a[1] - k , 1} ;

	for (int i = 2 ; i <= n ; ++i) {
		f[i][0] = std::min(f[i - 1][0] , f[i - 1][1]) ;
		f[i][1] = (data){f[i - 1][0].sum + a[i] - k , f[i - 1][0].cnt + 1} ;
	}

	return std::min(f[n][0] , f[n][1]) ;
}

int main() {
	n = read() ; m = read() ;
	for (int i = 1 ; i <= n ; ++i) a[i] = read() ;

	L = 0 ; R = a[n] + 1 ; --n ;
	for (int i = 1 ; i <= n ; ++i) a[i] = a[i + 1] - a[i] ;

	///

	for (; L + 1 < R ;) {
		int mid = (L + R) >> 1 ;

		if (check(0 , mid).cnt <= m) L = mid ;
		else R = mid ;
	}

	printf("%lld\n" , check(1 , L).sum + (ll)m * L) ;

	return 0 ;
}