#include <stdio.h>
#include <stdlib.h>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 ;

struct data {
	int num ;
	bool same ;
}tre[MAX_N << 2] ;

int n , a[MAX_N] ;

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

void update(int t , int x , int y) {
	int mid = (x + y) >> 1 , L = t << 1 , R = L | 1 ;

	tre[t].num = tre[L].num ;
	tre[t].same = tre[L].same && tre[R].same && (tre[L].num == tre[R].num) ;
}

void down(int t) {
	int L = t << 1 , R = t << 1 | 1 ;

	if (tre[t].same) tre[L] = tre[R] = tre[t] ;
}

void build(int t , int x , int y) {
	if (x == y) {
		tre[t].num = a[x] ;
		tre[t].same = 1 ;

		return ;
	}

	int mid = (x + y) >> 1 ;
	build(t << 1 , x , mid) ; build(t << 1 | 1 , mid + 1 , y) ;

	update(t , x , y) ;
}

int find(int t , int x , int y , int fx , int fy , int a) {
	if (y < fx || fy < x) return 0 ;

	int mid = (x + y) >> 1 , ans ;
	if (x == y) {
		if (tre[t].num == a) ans = 1 ;
		else ans = 0 ;

		tre[t].num = a ;
		return ans ;
	}

	down(t) ;

	if (fx <= x && y <= fy && tre[t].same) ans = (tre[t].num == a) * (y - x + 1) ;
	else ans = find(t << 1 , x , mid , fx , fy , a) + find(t << 1 | 1 , mid + 1 , y , fx , fy , a) ;

	if (fx <= x && y <= fy) tre[t].num = a , tre[t].same = 1 ;
	else update(t , x , y) ;

	return ans ;
}

int main() {
	n = read() ;
	for (int i = 1 ; i <= n ; ++i) a[i] = read() ;

	///

	build(1 , 1 , n) ;
	for (int i = 0 ; i < n ; ++i) {
		int a , b , c ; a = read() ; b = read() ; c = read() ;

		printf("%d\n" , find(1 , 1 , n , a , b , c)) ;
	}

	return 0 ;
}