#include <map>
#include <math.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

#define ed(x) (x * siz)
#define st(x) ((x - 1) * siz + 1)
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__  , __LINE__) ;

const int MAX_N = 1e5 + 10 , MAX_B = 1e3 + 10 ;

std::map<int , int> bh ;
std::vector<int> pl[MAX_N] ;

struct data {
	int num , cnt ;
}f[MAX_B][MAX_B] ;

int n , tot , siz , a[MAX_N] , bk[MAX_N] ;

data cmp(data x , data y) {
	if (x.cnt > y.cnt) return x ;
	else if (x.cnt < y.cnt) return y ;
	
	if (x.num > y.num) return y ;
	else return x ;
}

int find(int p , int x) {
	int L = 0 , R = pl[p].size() ;

	for (; L + 1 < R ;) {
		int mid = (L + R) >> 1 ;
		if (pl[p][mid] > x) R = mid ;
		else L = mid ;
	}

	return L ;
}

int cal(int x , int y , int num) {
	int p = bh[num] ;

	int L = find(p , x) , R = find(p , y) ;
	if (pl[p][L] < x) ++L ;

	if(L > R) return 0 ;
	else return (R - L + 1) ;
}

data count(int bx , int by , int b) {
	data res ;
	if (bx == by) res = (data){-1 , -1} ;
	else res = f[bx][by - 1] ;

	int L = st(bx) , R = std::min(ed(by) , n) ;
	if (res.cnt != -1) res.cnt = cal(L , R , res.num) ;

	for (int i = st(b) ; i <= std::min(ed(b) , n) ; ++i) {
		data tmp = (data){a[i] , cal(L , R , a[i])} ;
		res = cmp(tmp , res) ;
	}

	return res ;
}

data work(int L , int R) {
	data res ;
	int bx = bk[L] , by = bk[R] ;

	if (bx + 1 > by - 1) res = (data){-1 , -1} ;
	else res = f[bx + 1][by - 1] , res.cnt = cal(L , R , res.num) ;

	for (int i = L , j = std::min(ed(bx) , R) ; i <= j ; ++i) {
		data tmp = (data){a[i] , cal(L , R , a[i])} ;
		res = cmp(res , tmp) ;
	}

	if (bx != by)
		for (int i = st(by) , j = std::min(ed(by) , R) ; i <= j ; ++i) {
			data tmp = (data){a[i] , cal(L , R , a[i])} ;
			res = cmp(res , tmp) ;
		}

	return res ;
}

inline int read() {
	int num = 0 , f = 1 ;
	char c = getchar() ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

int main() {
	freopen("in" , "r" , stdin) ;
	freopen("out" , "w" , stdout) ;

	n = read() ;
	for (int i = 1 ; i <= n ; ++i) {
		int t ; t = read() ;
		a[i] = t ;

		int p ;
		if (!bh.count(t)) {
			bh[t] = ++tot ;
			pl[tot].push_back(-MAX_N) ;
		}

		p = bh[t] ;
		pl[p].push_back(i) ;
	}

	///

	siz = 200 ;
	for (int i = 1 ; i <= n ; ++i) bk[i] = (i - 1) / siz + 1 ;

	for (int i = 1 ; i <= bk[n] ; ++i)
		for (int j = i ; j <= bk[n] ; ++j)
			f[i][j] = count(i , j , j) ;

	///

	for (int i = 0 ; i < n ; ++i) {
		int a , b ; a = read() ; b = read() ;

		data ans = work(a , b) ;
		printf("%d\n" , ans.num) ;
	}

	return 0 ;
}