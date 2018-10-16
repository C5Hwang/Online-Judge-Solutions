#include <map>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ed(x) (x * siz)
#define st(x) ((x - 1) * siz + 1)
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 , MAX_B = 400 + 10 ;

std::map<int , int> bh ;

struct data {
	int num , cnt ;
}f[MAX_B][MAX_B] ;

int ap[MAX_N] , sum[MAX_B][MAX_N] ;
int n , siz , tot , num[MAX_N] , a[MAX_N] , bk[MAX_N] ;

///

data cmp(data x , data y) {
	if (x.cnt > y.cnt) return x ;
	else if (x.cnt < y.cnt) return y ;

	if (num[x.num] > num[y.num]) return y ;
	else return x ;
}

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

///

int find(int bx , int by , int a) {
	if (bx > by) return 0 ;

	return sum[by][a] - sum[bx - 1][a] ;
}

void update(data &res , int x , int y , int bx , int by) {
	for (int i = x ; i <= y ; ++i) {
		int t = a[i] ;
		if (!ap[t]) continue ;

		data tmp = (data){t , find(bx , by , t) + ap[t]} ;
		res = cmp(res , tmp) ; ap[t] = 0 ;
	}
}

data work1(int bx , int by , int x , int y) {
	data res = bx > by ? (data){-1 , -1} : f[bx][by] ;
	for (int i = x ; i <= y ; ++i) ++ap[a[i]] ;

	if (res.num != -1) res.cnt += ap[res.num] ;

	update(res , x , y , bx , by) ;

	return res ;
}

data work2(int x , int y) {
	int x1 , y1 , x2 , y2 ;
	data res = bk[x] + 1 < bk[y] ? f[bk[x] + 1][bk[y] - 1] : (data){-1 , -1} ;

	x1 = x ; y1 = std::min(ed(bk[x]) , y) ;
	if (bk[x] != bk[y]) x2 = st(bk[y]) ; y2 = y ;

	///

	for (int i = x1 ; i <= y1 ; ++i) ++ap[a[i]] ;
	for (int i = x2 ; i <= y2 ; ++i) ++ap[a[i]] ;

	update(res , x1 , y1 , bk[x] + 1 , bk[y] - 1) ;
	update(res , x2 , y2 , bk[x] + 1 , bk[y] - 1) ;

	return res ;
}

///

int main() {
	n = read() ; siz = (int)sqrt(n) ;
	for (int i = 1 ; i <= n ; ++i) {
		int t = read() ;

		if (!bh.count(t)) {
			bh[t] = ++tot ;
			num[tot] = t ;
		}
		a[i] = bh[t] ;
	}
	for (int i = 1 ; i <= n ; ++i) bk[i] = (i - 1) / siz + 1 ;

	///

	for (int i = 1 ; i <= bk[n] ; ++i){
		int L = st(i) , R = std::min(ed(i) , n) ;
		for (int j = L ; j <= R ; ++j) ++ap[a[j]] ;

		for (int j = 1 ; j <= tot ; ++j) {
			sum[i][j] = sum[i - 1][j] + ap[j] ;
			ap[j] = 0 ;
		}
	}

	for (int i = 1 ; i <= bk[n] ; ++i)
		for (int j = 1 ; j <= bk[n] ; ++j) {
			int L = st(j) , R = std::min(ed(j) , n) ;
			f[i][j] = work1(i , j - 1 , L , R) ;
		}

	///

	for (int i = 0 ; i < n ; ++i) {
		int a , b ; a = read() ; b = read() ;

		int ans = num[work2(a , b).num] ;
		printf("%d\n" , ans) ;
	}

	return 0 ;
}