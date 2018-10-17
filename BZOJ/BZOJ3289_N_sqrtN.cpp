#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ed(x) (x * siz)
#define st(x) ((x - 1) * siz + 1)
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 5e4 + 10 , MAX_B = 225 + 10 ;

struct data {
	int num , idx ;
}a[MAX_N] , Ta[MAX_B] , Tb[MAX_B] ;

int n , m , siz , tot , bk[MAX_N] , ap[MAX_N] ;
int f[MAX_B][MAX_B] , g[MAX_N] , h[MAX_N] , BIT[MAX_N] , sum[MAX_B][MAX_N] ;

///

bool cmp1(data x , data y) {return x.num < y.num ;}

bool cmp2(data x , data y) {return x.idx < y.idx ;}

bool cmp3(data x , data y) {return x.num > y.num ;}

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

///

inline int lowbit(int x) {return x & (-x) ;}

void modify(int x) {
	for (; x <= tot ; x += lowbit(x)) ++BIT[x] ;
}

int query(int x) {
	int s = 0 ;
	for (; x ; x -= lowbit(x)) s += BIT[x] ;

	return s ;
}

///

int count(int bx , int by , int a , int ty) {
	if (bx > by) return 0 ;

	if (ty) return sum[by][tot] - sum[by][a] - (sum[bx - 1][tot] - sum[bx - 1][a]) ;
	else return sum[by][a - 1] - sum[bx - 1][a - 1] ;
}

int work1(int bx , int by , int x , int y) {
	int res = bx > by ? g[y] : f[bx][by] + g[y] ;

	for (int i = x ; i <= y ; ++i) {
		int t = a[i].num ;
		res += count(bx , by , t , 1) ;
	}

	return res ;
}

int merge(int t1 , int t2) {
	int p1 = 0 , p2 = 0 , res = 0 ;

	for (; p1 < t1 && p2 < t2 ;)
		if (Ta[p1].num > Tb[p2].num) ++p1 ;
		else {++p2 ; res += p1 ;}

	for (; p2 < t2 ; ++p2) res += p1 ;

	return res ;
}

int work2(int x , int y) {
	int x1 , y1 , x2 , y2 , t1 , t2 , bx , by , res ;

	t1 = t2 = res = 0 ; bx = bk[x] ; by = bk[y] ;

	x1 = st(bx) ; y1 = std::min(ed(bx) , n) ; res += h[x] ;
	if (bx != by) x2 = st(by) , y2 = std::min(ed(by) , n) , res += g[y] ;
	else {
		if (y != y1) res -= h[y + 1] ;
		for (int i = x1 ; i <= y1 ; ++i)
			if (a[i].idx >= x && a[i].idx <= y) Ta[t1++] = a[i] ;
			else if (a[i].idx > y) Tb[t2++] = a[i] ;

		return res - merge(t1 , t2) ;
	}

	if (bx + 1 < by) res += f[bx + 1][by - 1] ;

	///

	for (int i = x1 ; i <= y1 ; ++i)
		if (a[i].idx >= x && a[i].idx <= y) {
			Ta[t1++] = a[i] ;

			int t = a[i].num ;
			res += count(bx + 1 , by - 1 , t , 0) ;
		}
	for (int i = x2 ; i <= y2 ; ++i)
		if (a[i].idx >= x && a[i].idx <= y) {
			Tb[t2++] = a[i] ;

			int t = a[i].num ;
			res += count(bx + 1 , by - 1 , t , 1) ;
		}

	return res + merge(t1 , t2) ;
}

///

int main() {
	n = read() ; siz = (int)sqrt(n) ;
	for (int i = 1 ; i <= n ; ++i) {
		a[i].num = read() ;
		a[i].idx = i ;
	}
	for (int i = 1 ; i <= n ; ++i) bk[i] = (i - 1) / siz + 1 ;

	std::sort(a + 1 , a + 1 + n , cmp1) ;
	int last = a[1].num ; a[1].num = tot = 1 ;
	for (int i = 2 ; i <= n ; ++i)
		if (a[i].num != last) {
			last = a[i].num ;
			a[i].num = ++tot ;
		}
		else a[i].num = tot ;
	std::sort(a + 1 , a + 1 + n , cmp2) ;

	///

	for (int i = 1 ; i <= bk[n] ; ++i) {
		for (int j = 1 ; j <= tot ; ++j) BIT[j] = 0 ;

		int L = st(i) , R = std::min(ed(i) , n) ;
		for (int j = L ; j <= R ; ++j) {
			int t = a[j].num , tmp = query(tot) - query(t) ;
			modify(t) ;

			if (j == L) g[j] = tmp ;
			else g[j] = g[j - 1] + tmp ;
		}

		for (int j = 1 ; j <= tot ; ++j) BIT[j] = 0 ;

		for (int j = R ; j >= L ; --j) {
			int t = a[j].num , tmp = query(t - 1) ;
			modify(t) ;

			if (j == R) h[j] = tmp ;
			else h[j] = h[j + 1] + tmp ;
		}
	}

	for (int i = 1 ; i <= bk[n] ; ++i) {
		int L = st(i) , R = std::min(ed(i) , n) ;

		for (int j = L ; j <= R ; ++j) ++ap[a[j].num] ;
		for (int j = 1 ; j <= tot ; ++j) {
			sum[i][j] = sum[i - 1][j] + ap[j] ;
			ap[j] = 0 ;
		}
	}
	for (int i = 1 ; i <= bk[n] ; ++i)
		for (int j = 2 ; j <= tot ; ++j) sum[i][j] += sum[i][j - 1] ;

	for (int i = 1 ; i <= bk[n] ; ++i)
		for (int j = 1 ; j <= bk[n] ; ++j) {
			int L = st(j) , R = std::min(ed(j) , n) ;

			f[i][j] = work1(i , j - 1 , L , R) ;
		}

	for (int i = 1 ; i <= bk[n] ; ++i) {
		int L = st(i) , R = std::min(ed(i) , n) ;
		std::sort(a + L , a + R + 1 , cmp3) ;
	}

	///

	m = read() ;
	for (int i = 0 ; i < m ; ++i) {
		int a , b ; a = read() ; b = read() ;

		printf("%d\n" , work2(a , b)) ;
	}

	return 0 ;
}