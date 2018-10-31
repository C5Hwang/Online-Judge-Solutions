#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 2e5 + 10 , MAX_Q = 4e5 + 10 ;

struct data {
	int ty , x , y , k , idx ;
}qry[MAX_Q] , tmp[MAX_Q] ;

int n , m , mx , ans[MAX_N] , cnt[MAX_Q] , BIT[MAX_N] ;

///

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

inline int lowbit(int x) {return x & (-x) ;}

void add(int x , int a) {
	for (; x <= mx ; x += lowbit(x)) BIT[x] += a ;
}

int query(int x) {
	int s = 0 ;
	for (; x ; x -= lowbit(x)) s += BIT[x] ;

	return s ;
}

///

void devide(int qx , int qy , int L , int R) {
	if (qx > qy) return ;

	if (L == R) {
		for (int i = qx ; i <= qy ; ++i)
			if (qry[i].ty == 2) ans[qry[i].idx] = L ;

		return ;
	}

	///

	int mid = (L + R) >> 1 ;
	for (int i = qx ; i <= qy ; ++i) {
		data *p = &qry[i] ;

		if (p->ty == 1 && p->y <= mid) add(p->x , 1) ;
		else if (p->ty == 2) cnt[i] = query(p->y) - query(p->x - 1) ;
	}
	for (int i = qx ; i <= qy ; ++i) {
		data *p = &qry[i] ;

		if (p->ty == 1 && p->y <= mid) add(p->x , -1) ;
	}

	for (int i = qx ; i <= qy ; ++i) {
		data *p = &qry[i] ;

		if (p->ty == 1) {
			if (p->y <= mid) cnt[i] = 0 ;
			else cnt[i] = 1 ;
		}
		else {
			if (cnt[i] >= p->k) cnt[i] = 0 ;
			else p->k -= cnt[i] , cnt[i] = 1 ;
		}
	}

	int o = 0 , l1 = 0 ;
	for (int i = qx ; i <= qy ; ++i) if (!cnt[i]) tmp[o++] = qry[i] , ++l1 ;
	for (int i = qx ; i <= qy ; ++i) if (cnt[i]) tmp[o++] = qry[i] ;

	for (int i = qx ; i <= qy ; ++i) qry[i] = tmp[i - qx] ;
	devide(qx , qx + l1 - 1 , L , mid) ; devide(qx + l1 , qy , mid + 1 , R) ;
}

///

int main() {
	freopen("shooting.in" , "r" , stdin) ;
	freopen("shooting.out" , "w" , stdout) ;

	n = read() ; m = read() ;
	for (int i = 1 ; i <= n ; ++i) {
		data *p = &qry[i + m] ;
		p->ty = 2 ; p->x = read() ; p->y = read() ; p->k = read() ; p->idx = i ;

		mx = std::max(mx , p->y) ;
	}
	for (int i = 1 ; i <= m ; ++i) {
		data *p = &qry[i] ;
		p->ty = 1 ; p->x = read() ; p->y = i ;

		mx = std::max(mx , p->x) ;
	}

	///

	devide(1 , n + m , 0 , m + 1) ;

	for (int i = 1 ; i <= m ; ++i) cnt[i] = 0 ;
	for (int i = 1 ; i <= n ; ++i) ++cnt[ans[i]] ;
	for (int i = 1 ; i <= m ; ++i) printf("%d\n" , cnt[i]) ;

	fclose(stdin) ; fclose(stdout) ;

	return 0 ;
}