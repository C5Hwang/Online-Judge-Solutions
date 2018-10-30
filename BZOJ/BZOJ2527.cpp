#include <vector>
#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 3e5 + 10 , MAX_Q = 9e5 + 10 ;

struct data {
	int ty , x , y , k , idx ;
}qry[MAX_Q] , tmp[MAX_Q] ;

std::vector<int> stt[MAX_N] ;

ll cnt[MAX_Q] , BIT[MAX_N] ;
int n , m , q , tot , a[MAX_N] , ans[MAX_N] ;

///

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

inline int lowbit(int x) {return x & (-x) ;}

void update(int x , ll k) {
	for (; x <= m ; x += lowbit(x)) BIT[x] += k ;
}

void modify(int x , int y , ll k) {
	update(x , k) ; update(y + 1 , -k) ;
}

ll find(int x) {
	ll s = 0 ;
	for (; x ; x -= lowbit(x)) s += BIT[x] ;

	return s ;
}

///

void devide(int qx , int qy , int L , int R) {
	if (qx > qy) return ;
	if (L == R) {
		for (int i = qx ; i <= qy ; ++i)
			if (qry[i].ty == 2) ans[qry[i].x] = L ;

		return ;
	}

	///

	int mid = (L + R) >> 1 ;
	for (int i = qx ; i <= qy ; ++i) {
		data *p = &qry[i] ;

		if (p->ty == 1 && p->idx <= mid) modify(p->x , p->y , p->k) ;
		else if (p->ty == 2) {
			int sz = stt[p->x].size() ;

			cnt[i] = 0 ;
			for (int j = 0 ; j < sz ; ++j) {
				cnt[i] += find(stt[p->x][j]) ;
				if (cnt[i] >= p->y) break ;
			}
		}
	}
	for (int i = qx ; i <= qy ; ++i) {
		data *p = &qry[i] ;

		if (p->ty == 1 && p->idx <= mid) modify(p->x , p->y , -p->k) ;
	}

	for (int i = qx ; i <= qy ; ++i) {
		data *p = &qry[i] ;

		if (p->ty == 1) {
			if (p->idx <= mid) cnt[i] = 0 ;
			else cnt[i] = 1 ;
		}
		else {
			if (cnt[i] >= p->y) cnt[i] = 0 ;
			else p->y -= cnt[i] , cnt[i] = 1 ;
		}
	}

	int o = 0 , l1 = 0 ;
	for (int i = qx ; i <= qy ; ++i) if (!cnt[i]) tmp[o++] = qry[i] , ++l1 ;
	for (int i = qx ; i <= qy ; ++i) if (cnt[i]) tmp[o++] = qry[i] ;

	for (int i = qx ; i <= qy ; ++i) qry[i] = tmp[i - qx] ;
	devide(qx , qx + l1 - 1 , L , mid) ;
	devide(qx + l1 , qy , mid + 1 , R) ;
}

///

int main() {
	n = read() ; m = read() ;
	for (int i = 1 ; i <= m ; ++i) {
		int a = read() ;
		stt[a].push_back(i) ;
	}
	for (int i = 1 ; i <= n ; ++i) a[i] = read() ;

	q = read() ;
	for (int i = 0 ; i < q ; ++i) {
		int x , y , k ;
		x = read() ; y = read() ; k = read() ;

		if (x > y) qry[++tot] = (data){1 , x , m , k , i} , qry[++tot] = (data){1 , 1 , y , k , i} ;
		else qry[++tot] = (data){1 , x , y , k , i} ;
	}
	for (int i = 1 ; i <= n ; ++i) qry[++tot] = (data){2 , i , a[i] , 0 , 0} ;

	///

	devide(1 , tot , -1 , q) ;

	for (int i = 1 ; i <= n ; ++i)
		if (ans[i] == q) printf("NIE\n") ;
		else printf("%d\n" , ans[i] + 1) ;

	return 0 ;
}