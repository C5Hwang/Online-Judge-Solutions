#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 5e4 + 10 ;

struct Link {
	int num , val ;
	Link *next ;
}list[MAX_N << 1] ;

Link *head[MAX_N] ;
int n , m , mL , cur , f[MAX_N] , tmp[MAX_N] ;

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

void ins(int x , int y , int v) {
	list[cur].num = y ;
	list[cur].val = v ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

int count(int p , int o , int L) {
	int le = 0 , ri = o - 1 , s = 0 ;

	for (; le < ri ;) {
		if (ri == p) --ri ;
		for (; le < ri && tmp[le] + tmp[ri] < L ; ++le) ;

		if (le == p) ++le ;
		if (le < ri) ++s , ++le , --ri ;
	}

	return s ;
}

int check(int x , int fa , int L) {
	int ans = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa) continue ;

		ans += check(nx , x , L) ;
	}

	int o = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa) continue ;

		if (f[nx] + h->val >= L) ++ans ;
		else tmp[o++] = f[nx] + h->val ;
	}

	std::sort(tmp + 0 , tmp + o) ;

	int le = 0 , ri = o - 1 , sum = 0 ;
	for (; le < ri ;) {
		for (; le < ri && tmp[le] + tmp[ri] < L ; ++le) ;
		if (le < ri) ++sum , ++le , --ri ;
	}

	le = -1 ; ri = o ;
	for (; le + 1 < ri ;) {
		int mid = (le + ri) >> 1 ;
		if (count(mid , o , L) == sum) le = mid ;
		else ri = mid ;
	}

	if (le != -1) f[x] = tmp[le] ;
	else f[x] = 0 ;

	return ans + sum ;
}

int main() {
	n = read() ; m = read() ;
	for (int i = 1 ; i < n ; ++i) {
		int a , b , v ;
		a = read() ; b = read() ; v = read() ;

		ins(a , b , v) ; ins(b , a , v) ;
		mL += v ;
	}

	///

	int L = 0 , R = mL + 1 ;
	for (; L + 1 < R ;) {
		int mid = (L + R) >> 1 ;

		if (check(1 , 1 , mid) >= m) L = mid ;
		else R = mid ;
	}

	printf("%d\n" , L) ;

	return 0 ;
}