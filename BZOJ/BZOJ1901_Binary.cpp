#include <stdio.h>
#include <stdlib.h>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e4 + 10 , MAX_Q = 3e4 + 10 , INF = 0x3f3f3f3f ;

struct data {
	int ty , x , y , k , sum , idx ;
}query[MAX_Q] , tmp[MAX_Q] ;

int cnt[MAX_Q] , BIT[MAX_N] ;
int n , m , tot , tans , a[MAX_N] , ans[MAX_N] ;

inline int lowbit(int x) {return x & (-x) ;}

void add(int x , int a) {
	for (; x <= n ; x += lowbit(x)) BIT[x] += a ;
}

int getsum(int x) {
	int sum = 0 ;
	for (; x ; x -= lowbit(x)) sum += BIT[x] ;

	return sum ;
}

void devide(int qx , int qy , int L , int R) {
	if (qx > qy) return ;

	if (L == R) {
		for (int i = qx ; i <= qy ; ++i)
			if (query[i].ty == 2) ans[query[i].idx] = L ;

		return ;
	}

	///

	int mid = (L + R) >> 1 ;
	for (int i = qx ; i <= qy ; ++i) {
		data *p = &query[i] ;

		if (p->ty == 1 && p->y <= mid) add(p->x , p->k) ;
		else if (p->ty == 2) cnt[i] = getsum(p->y) - getsum(p->x - 1) ;
	}
	for (int i = qx ; i <= qy ; ++i) {
		data *p = &query[i] ;

		if (p->ty == 1 && p->y <= mid) add(p->x , -p->k) ;
	}

	for (int i = qx ; i <= qy ; ++i) {
		data *p = &query[i] ;

		if (p->ty == 2 && p->sum + cnt[i] >= p->k) cnt[i] = 0 ;
		else if (p->ty == 2) p->sum += cnt[i] , cnt[i] = 1 ;
	}
	for (int i = qx ; i <= qy ; ++i) {
		data *p = &query[i] ;

		if (p->ty == 1 && p->y <= mid) cnt[i] = 0 ;
		else if (p->ty == 1) cnt[i] = 1 ;
	}

	int o = 0 , l1 = 0 ;
	for (int i = qx ; i <= qy ; ++i) if (!cnt[i]) tmp[o++] = query[i] , ++l1 ;
	for (int i = qx ; i <= qy ; ++i) if (cnt[i]) tmp[o++] = query[i] ;
	for (int i = qx ; i <= qy ; ++i) query[i] = tmp[i - qx] ;

	devide(qx , qx + l1 - 1 , L , mid) ;
	devide(qx + l1 , qy , mid + 1 , R) ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 1 ; i <= n ; ++i) {
		scanf("%d" , &a[i]) ;
		query[++tot] = (data){1 , i , a[i] , 1 , 0 , 0} ;
	}

	for (int i = 0 ; i < m ; ++i) {
		char op = getchar() ; int x , y , t ;
		for (; op < 'A' || op > 'Z' ; op = getchar()) ;

		if (op == 'Q') scanf("%d %d %d" , &x , &y , &t) ;
		else scanf("%d %d" , &x , &y) ;

		///

		if (op == 'Q') query[++tot] = (data){2 , x , y , t , 0 , tans++} ;
		else {
			query[++tot] = (data){1 , x , a[x] , -1 , 0 , 0} ;
			query[++tot] = (data){1 , x , y , 1 , 0 , 0} ;

			a[x] = y ;
		}
	}

	///

	devide(1 , tot , 0 , INF) ;

	for (int i = 0 ; i < tans ; ++i) printf("%d\n" , ans[i]) ;

	return 0 ;
}