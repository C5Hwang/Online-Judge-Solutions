#include <map>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 ;

struct QUERY {
	int x , y , bk , idx ;
}qry[MAX_N] ;
struct data {
	int num , cnt , pl ;

	friend bool operator <(data x , data y) {return x.cnt < y.cnt || (x.cnt == y.cnt && x.num > y.num) ;}
	friend bool operator >(data x , data y) {return x.cnt > y.cnt || (x.cnt == y.cnt && x.num < y.num) ;}
}pq[MAX_N] ;

std::map<int , int> bh ;

int pt[MAX_N] ;
int n , tot , blk , a[MAX_N] , ans[MAX_N] ;

///

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

bool cmp(QUERY a , QUERY b) {
	return a.bk < b.bk || (a.bk == b.bk && a.y < b.y) ;
}

///

void swap(int x , int y) {
	int px = pq[x].pl , py = pq[y].pl ;

	std::swap(pt[px] , pt[py]) ;
	std::swap(pq[x] , pq[y]) ;
}

int getmin(int L , int R) {
	if (L > tot) return -1 ;
	else if (R > tot) return L ;

	if (pq[L] > pq[R]) return L ;
	else return R ;
}

void upp(int x) {
	int p = pt[x] ;

	for (; p != 1 ;) {
		int fa = p >> 1 ;
		if (pq[p] > pq[fa]) swap(p , fa) ;

		p = fa ;
	}
}

void dwn(int x) {
	for (; ;) {
		int p = pt[x] , mson = getmin(p << 1 , p << 1 | 1) ;

		if (mson == -1) return ;

		if (pq[mson] > pq[p]) swap(mson , p) ;
		else return ;
	}
}

void push(int a) {
	bh[a] = ++tot ;

	pq[tot] = (data){a , 0 , tot} ;
	pt[tot] = tot ;

	upp(tot) ;
}

void update(int x , int a) {
	x = bh[x] ;
	pq[pt[x]].cnt += a ;

	if (a > 0) upp(x) ;
	else dwn(x) ;
}

///

int main() {
	n = read() ;
	for (int i = 1 ; i <= n ; ++i) {
		int t = read() ;
		a[i] = t ;

		if (!bh.count(t)) push(a[i]) ;
	}

	///

	blk = (int)sqrt(n) ;
	for (int i = 1 ; i <= n ; ++i) {
		QUERY *P = &qry[i] ;

		P->x = read() ; P->y = read() ;
		P->bk = P->x / blk ;
		P->idx = i ;
	}

	std::sort(qry + 1 , qry + 1 + n , cmp) ;

	///

	int L = 1 , R = 0 ;
	for (int i = 1 ; i <= n ; ++i) {
		int nL = qry[i].x , nR = qry[i].y ;

		for (; R < nR ;) update(a[++R] , 1) ;
		for (; nR < R ;) update(a[R--] , -1) ;
		for (; L < nL ;) update(a[L++] , -1) ;
		for (; nL < L ;) update(a[--L] , 1) ;

		ans[qry[i].idx] = pq[1].num ;
	}

	for (int i = 1 ; i <= n ; ++i) printf("%d\n" , ans[i]) ;

	return 0 ;
}