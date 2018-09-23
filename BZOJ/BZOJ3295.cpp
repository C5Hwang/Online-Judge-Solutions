#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long

const int MAX_N = 1e5 + 10 ;

struct data {
	int x , y , idx ;
}query[MAX_N] , temp[MAX_N] ;

ll ans[MAX_N] ;
bool ap[MAX_N] ;
int n , m , tot , a[MAX_N] , pl[MAX_N] , BIT[MAX_N] ;

///

bool cmp(data a , data b) {
	return a.idx < b.idx || a.idx == b.idx && a.y < b.y ;
}

///

int lowbit(int x) {return x & (-x) ;}

void add(int x) {
	for (; x <= n ; x += lowbit(x)) ++BIT[x] ;
}

int sum(int x) {
	int s = 0 ;
	for (; x > 0 ; x -= lowbit(x)) s += BIT[x] ;
	return s ;
}

void init(int x) {
	for (; x <= n ; x += lowbit(x)) BIT[x] = 0 ;
}

///

void cdq(int x , int y , int type) {
	if (x == y) return ;

	int mid = (x + y) >> 1 , p1 = x , p2 = mid + 1 , t = 0 ;
	cdq(x , mid , type) ; cdq(mid + 1 , y , type) ;

	while (p1 <= mid && p2 <= y) {
		if (query[p1].x != query[p2].x && (query[p1].x < query[p2].x) ^ type) {
			data *p = &query[p1++] ;
			add(p->y) ;
			temp[t++] = *p ;
		}
		else {
			data *p = &query[p2++] ;
			if (type) ans[p->idx] += sum(p->y - 1) ;
			else ans[p->idx] += sum(n) - sum(p->y) ;
			temp[t++] = *p ;
		}
	}

	for (; p1 <= mid ; ++p1) temp[t++] = query[p1] ;
	for (; p2 <= y ; ++p2) {
		data *p = &query[p2] ;
		if (type) ans[p->idx] += sum(p->y - 1) ;
		else ans[p->idx] += sum(n) - sum(p->y) ;
		temp[t++] = *p ;
	}

	for (int i = 0 ; i < t ; ++i) {
		init(temp[i].y) ;
		query[i + x] = temp[i] ;
	}
}

///

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 1 ; i <= n ; ++i) scanf("%d" , &a[i]) , pl[a[i]] = i ;
	for (int j = 0 ; j < m ; ++j) {
		int p ;
		scanf("%d" , &p) ; p = pl[p] ;

		ap[p] = 1 ;
		query[++tot] = (data){p , a[p] , m - j} ;
	}
	for (int i = 1 ; i <= n ; ++i)
		if (!ap[i]) query[++tot] = (data){i , a[i] , 0} ;
	
	///
	
	std::sort(query + 1 , query + 1 + n , cmp) ;
	cdq(1 , tot , 0) ;
	std::sort(query + 1 , query + 1 + n , cmp) ;
	cdq(1 , tot , 1) ;

	for (int i = 1 ; i <= m ; ++i) ans[i] += ans[i - 1] ;
	for (int i = m ; i > 0 ; --i) printf("%lld\n" , ans[i]) ;

	return 0 ;
}
