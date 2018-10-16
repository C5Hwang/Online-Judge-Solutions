#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ed(x) (x * siz)
#define st(x) ((x - 1) * siz + 1)
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 5 , MAX_B = 315 + 5 ;

int n , m , c , siz , ans , a[MAX_N] , bk[MAX_N] ;
int ap[MAX_N] , cnt[MAX_B][MAX_N] , f[MAX_B][MAX_B] ;

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

int cal(int a , int ti , int x , int y) {
	int bc = x <= y ? cnt[y][a] - cnt[x - 1][a] : 0 ;

	if (ti % 2) {
		if (!bc) return 0 ;

		if (bc % 2) return 1 ;
		else return -1 ;
	}
	else if (!bc) return 1 ;

	return 0 ;
}

int find(int x , int y , int bx , int by) {
	for (int i = x ; i <= y ; ++i) ++ap[a[i]] ;

	int res = 0 ;
	for (int i = x ; i <= y ; ++i)
		if (ap[a[i]]) res += cal(a[i] , ap[a[i]] , bx , by) , ap[a[i]] = 0 ;

	return res ;
}

int work(int x , int y) {
	int x1 , y1 , x2 , y2 , res ;

	x1 = x ; y1 = std::min(ed(bk[x]) , y) ;
	if (bk[x] != bk[y]) x2 = st(bk[y]) , y2 = y ;
	else x2 = 1 , y2 = 0 ;
	if (bk[x] + 1 < bk[y]) res = f[bk[x] + 1][bk[y] - 1] ;
	else res = 0 ;

	for (int i = x1 ; i <= y1 ; ++i) ++ap[a[i]] ;
	for (int i = x2 ; i <= y2 ; ++i) ++ap[a[i]] ;

	for (int i = x1 ; i <= y1 ; ++i)
		if (ap[a[i]]) res += cal(a[i] , ap[a[i]] , bk[x] + 1 , bk[y] - 1) , ap[a[i]] = 0 ;
	for (int i = x2 ; i <= y2 ; ++i)
		if (ap[a[i]]) res += cal(a[i] , ap[a[i]] , bk[x] + 1 , bk[y] - 1) , ap[a[i]] = 0 ;

	return res ;
}

int main() {
	n = read() ; c = read() ; m = read() ; siz = 316 ;
	for (int i = 1 ; i <= n ; ++i) a[i] = read() ;

	for (int i = 1 ; i <= n ; ++i) bk[i] = (i - 1) / siz + 1 ;

	///

	for (int i = 1 ; i <= bk[n] ; ++i) {
		int L = st(i) , R = std::min(ed(i) , n) ;

		for (int j = L ; j <= R ; ++j) ++ap[a[j]] ;
		for (int j = 1 ; j <= c ; ++j) {
			cnt[i][j] = cnt[i - 1][j] + ap[j] ;
			ap[j] = 0 ;
		}
	}

	for (int i = 1 ; i <= bk[n] ; ++i)
		for (int j = i ; j <= bk[n] ; ++j) {
			int L = st(j) , R = std::min(ed(j) , n) , tmp ;
			tmp = find(L , R , i , j - 1) ;

			f[i][j] = f[i][j - 1] + tmp ;
		}

	///

	ans = 0 ;
	for (int i = 0 ; i < m ; ++i) {
		int x , y ; x = read() ; y = read() ;
		x = (x + ans) % n + 1 ; y = (y + ans) % n + 1 ;

		if (x > y) std::swap(x , y) ;

		ans = work(x , y) ;
		printf("%d\n" , ans) ;
	}

	return 0 ;
}