#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 5e4 + 10 ;

struct QUERY {
	int x , y , bk , idx ;
}qry[MAX_N] ;
struct data {
	int num , idx ;
}a[MAX_N] ;

int BIT[MAX_N] ;
int n , m , tot , siz , res[MAX_N] ;

///

bool cmp1(data x , data y) {return x.num < y.num ;}

bool cmp2(data x , data y) {return x.idx < y.idx ;}

bool cmp3(QUERY a , QUERY b) {
	return a.bk < b.bk || (a.bk == b.bk && a.y < b.y) ;
}

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

///

inline int lowbit(int x) {return x & (-x) ;}

void modify(int x , int a) {
	for (; x <= tot ; x += lowbit(x)) BIT[x] += a ;
}

int getsum(int x) {
	int sum = 0 ;
	for (; x ; x -= lowbit(x)) sum += BIT[x] ;

	return sum ;
}

int find(int x , int y) {
	if (x > y) return 0 ;

	return getsum(y) - getsum(x - 1) ;
}

int update(int pl , int t , int ty) {
	int num = a[pl].num , sum ;

	if (!ty) sum = find(num + 1 , tot) ;
	else sum = find(1 , num - 1) ;

	modify(num , t) ;

	return sum ;
}

///

int main() {
	n = read() ; siz = (int)sqrt(n) ;
	for (int i = 1 ; i <= n ; ++i) {
		a[i].num = read() ;
		a[i].idx = i ;
	}

	m = read() ;
	for (int i = 0 ; i < m ; ++i) {
		QUERY *P = &qry[i] ;
		P->x = read() ; P->y = read() ;
		P->bk = P->x / siz ; P->idx = i ;
	}

	///

	std::sort(a + 1 , a + 1 + n , cmp1) ;

	int last = a[1].num ; a[1].num = ++tot ;
	for (int i = 2 ; i <= n ; ++i)
		if (a[i].num != last) {
			last = a[i].num ;
			a[i].num  = ++tot ;
		}
		else a[i].num = tot ;

	std::sort(a + 1 , a + 1 + n , cmp2) ;

	std::sort(qry + 0 , qry + m , cmp3) ;

	///

	int L = 1 , R = 0 , ans = 0 ;

	for (int i = 0 ; i < m ; ++i) {
		QUERY *P = &qry[i] ;
		int nL = P->x , nR = P->y ;

		for (; R < nR ;) ans += update(++R , 1 , 0) ;
		for (; nR < R ;) ans -= update(R-- , -1 , 0) ;
		for (; L < nL ;) ans -= update(L++ , -1 , 1) ;
		for (; nL < L ;) ans += update(--L , 1 , 1) ;

		res[P->idx] = ans ;
	}

	for (int i = 0 ; i < m ; ++i) printf("%d\n" , res[i]) ;

	return 0 ;
}