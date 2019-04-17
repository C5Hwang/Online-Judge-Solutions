#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 5e4 + 10 , MAX_M = 1e5 + 10 ;

struct data {int x , y , val ;}bl[MAX_M] , wh[MAX_M] ;

int n , m , k , t1 , t2 , fa[MAX_N] ;

bool cmp(data a , data b) {return a.val < b.val ;}

int findset(int x) {return fa[x] == -1 ? x : (fa[x] = findset(fa[x])) ;}

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

int check(int ty , int k) {
	int cnt = 0 , sum = 0 , p1 = 0 , p2 = 0 , lef = n ;

	for (int i = 0 ; i < n ; ++i) fa[i] = -1 ;
	for (; lef > 1 ;) {
		int x , y , v ;

		if (p1 == t1 || bl[p1].val > wh[p2].val - k) {
			x = wh[p2].x ; y = wh[p2].y ; v = wh[p2].val - k ; ++p2 ;

			int fx = findset(x) , fy = findset(y) ;
			if (fx != fy) {fa[fx] = fy ; ++cnt ; sum += v ; --lef ;}
		}
		else {
			x = bl[p1].x ; y = bl[p1].y ; v = bl[p1].val ; ++p1 ;

			int fx = findset(x) , fy = findset(y) ;
			if (fx != fy) {fa[fx] = fy ; sum += v ; --lef ;}
		}
	}

	if (ty) return sum ;
	else return cnt ;
}

int main() {
	n = read() ; m = read() ; k = read() ;
	for (int i = 0 ; i < m ; ++i) {
		int x , y , v , col ;
		x = read() ; y = read() ; v = read() ; col = read() ;

		if (col) bl[t1++] = (data){x , y , v} ;
		else wh[t2++] = (data){x , y , v} ;
	}

	///

	std::sort(bl + 0 , bl + t1 , cmp) ;
	std::sort(wh + 0 , wh + t2 , cmp) ;

	int L = -100 , R = 100 ;
	for (; L + 1 < R ;) {
		int mid = (L + R) >> 1 ;

		if (check(0 , mid) <= k) L = mid ;
		else R = mid ;
	}

	printf("%d\n" , check(1 , L) + L * k) ;

	return 0 ;
}