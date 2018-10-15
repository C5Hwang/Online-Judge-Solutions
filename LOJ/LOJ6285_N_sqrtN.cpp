#include <map>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define ed(x) (x * siz)
#define st(x) ((x - 1) * siz + 1)
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 , MAX_B = 320 + 10 ;

struct data {
	int b , p ;

	friend data operator +(data x , int a) {return (data){x.b , x.p + a} ;}
}pl[MAX_N] ;
struct COUNT {
	int num , cnt ;
}ans[MAX_B][MAX_B] ;

std::map<int , int> bh ;

bool ap[MAX_N] ;
int n , siz , tot , num[MAX_N] , a[MAX_N] , bk[MAX_N] ;
int bp[MAX_B][MAX_N] , f[MAX_B][MAX_B][MAX_B] , g[MAX_B][MAX_N] ;

///

COUNT cmp(COUNT a , COUNT b) {
	if (a.cnt < b.cnt) return b ;
	else if (a.cnt > b.cnt) return a ;

	if (num[a.num] < num[b.num]) return a ;
	else return b ;
}

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

///

int cal(int p , int a) {
	if (!p) return 0 ;

	data P = pl[p] ;
	int nw = bp[P.b][a] ;

	return f[P.b][P.p][nw] + g[P.b - 1][a] ;
}

int update(int x , int y , int a) {
	return cal(y , a) - cal(x - 1 , a) ;
}

COUNT find(int x , int y , int fx , int fy) {
	COUNT res = (COUNT){-1 , -1} ;

	for (int i = fx ; i <= fy ; ++i) {
		COUNT tmp = (COUNT){a[i] , update(x , y , a[i])} ;
		res = cmp(res , tmp) ;
	}

	return res ;
}

COUNT getans(int x , int y) {
	COUNT A , B , C ;
	A = B = C = (COUNT){-1 , -1} ;

	A = find(x , y , x , std::min(ed(bk[x]) , y)) ;
	if (bk[x] != bk[y]) B = find(x , y , st(bk[y]) , y) ;
	if (bk[x] + 1 < bk[y]) {
		C = ans[bk[x] + 1][bk[y] - 1] ;
		C.cnt = update(x , y , C.num) ;
	}

	return cmp(cmp(A , B) , C) ;
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

	pl[0] = (data){0 , siz} ;
	for (int i = 1 ; i <= n ; ++i) {
		bk[i] = (i - 1) / siz + 1 ;
		pl[i] = pl[i - 1] + 1 ;

		if (pl[i].p > siz) pl[i].p -= siz , ++pl[i].b ;
	}

	///

	for (int i = 1 ; i <= bk[n] ; ++i) {
		int t = 0 , L = st(i) , R = std::min(ed(i) , n) ;

		for (int j = 1 ; j <= tot ; ++j) ap[j] = 0 ;
		for (int j = L ; j <= R ; ++j) if (!ap[a[j]]) bp[i][a[j]] = ++t , ap[a[j]] = 1 ;

		for (int j = L ; j <= R ; ++j) {
			int p = j - L + 1 , nw = bp[i][a[j]] ;

			for (int k = 1 ; k <= t ; ++k) f[i][p][k] = f[i][p - 1][k] ;
			++f[i][p][nw] ;
		}
	}

	for (int i = 1 ; i <= bk[n] ; ++i)
		for (int j = 1 ; j <= tot ; ++j) {
			int nw = bp[i][j] , ed = std::min(ed(i) , n) - st(i) + 1 ;

			g[i][j] = g[i - 1][j] + f[i][ed][nw] ;
		}

	for (int i = 1 ; i <= bk[n] ; ++i)
		for (int j = 1 ; j <= bk[n] ; ++j) {
			COUNT tmp ;
			if (i == j) tmp = (COUNT){-1 , -1} ;
			else tmp = ans[i][j - 1] ;

			int L = st(i) , R = std::min(ed(j) , n) ;
			if (tmp.cnt != -1) tmp.cnt = update(L , R , tmp.num) ;
			tmp = cmp(tmp , find(L , R , st(j) , R)) ;

			ans[i][j] = tmp ;
		}

	///

	for (int i = 0 ; i < n ; ++i) {
		int a , b ;
		a = read() ; b = read() ;

		COUNT res = getans(a , b) ;
		printf("%d\n" , num[res.num]) ;
	}

	return 0 ;
}