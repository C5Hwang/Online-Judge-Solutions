#include <queue>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 , INF = 0x3f3f3f3f ;

struct data {
	int num , pl ;

	friend bool operator <(data a , data b) {return a.num > b.num ;}
} ;

std::priority_queue<data> que ;

bool ap[MAX_N] ;
int n , m , pre[MAX_N] , nxt[MAX_N] , a[MAX_N] ;

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

int main() {
	n = read() ; m = read() ;
	for (int i = 1 ; i <= n ; ++i) a[i] = read() ;
	for (int i = 1 ; i < n ; ++i) {
		a[i] = a[i + 1] - a[i] ;
		pre[i] = i - 1 ; nxt[i] = i + 1 ;
	}
	a[0] = INF ; a[n] = INF ;
	pre[0] = nxt[0] = 0 ; pre[n] = nxt[n] = n ;

	///

	for (int i = 1 ; i < n ; ++i) que.push((data){a[i] , i}) ;

	int ans = 0 ;
	for (; m-- ;) {
		for (; ap[que.top().pl] ; que.pop()) ;

		data tmp = que.top() ; int p = tmp.pl ;

		ans += tmp.num ; que.pop() ;
		ap[pre[p]] = ap[nxt[p]] = 1 ;

		a[p] = a[pre[p]] + a[nxt[p]] - tmp.num ;
		que.push((data){a[p] , p}) ;

		pre[p] = pre[pre[p]] ; nxt[p] = nxt[nxt[p]] ;
		nxt[pre[p]] = p ; pre[nxt[p]] = p ;
	}
	printf("%d\n" , ans) ;

	return 0 ;
}