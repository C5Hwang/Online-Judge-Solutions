#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 , mod = (119 << 23) + 1 ;

struct data {
	int r , sumr , mulr , f , addf , mulf ;
}tre[MAX_N << 2] ;

int n , m , tot , pw[MAX_N] ;

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

inline void update(int t) {
	int L = t << 1 , R = t << 1 | 1 ;

	tre[t].sumr = ((ll)tre[L].sumr + tre[R].sumr + tre[t].r) % mod ;
}

inline void timesF(int t , int a) {
	tre[t].f = (ll)tre[t].f * a % mod ;
	tre[t].addf = (ll)tre[t].addf * a % mod ;
	tre[t].mulf = (ll)tre[t].mulf * a % mod ;
}

inline void timesR(int t , int a) {
	tre[t].r = (ll)tre[t].r * a % mod ;
	tre[t].sumr = (ll)tre[t].sumr * a % mod ;
	tre[t].mulr = (ll)tre[t].mulr * a % mod ;
}

inline void addF(int t , int a) {
	(tre[t].f += a) %= mod ;
	(tre[t].addf += a) %= mod ;
}

inline void addR(int t , int a) {
	(tre[t].r += a) %= mod ;
	(tre[t].sumr += a) %= mod ;
}

inline void down(int t) {
	int L = t << 1 , R = t << 1 | 1 ,
		t1 = tre[t].mulr , t2 = tre[t].mulf , t3 = tre[t].addf ;

	timesR(L , t1) ; timesF(L , t2) ; addF(L , t3) ;
	timesR(R , t1) ; timesF(R , t2) ; addF(R , t3) ;

	tre[t].mulr = tre[t].mulf = 1 ; tre[t].addf = 0 ;
}

inline void dealson(int t , int x , int y) {
	if (x == y) return ;
	down(t) ;

	int L = t << 1 , R = t << 1 | 1 ;
	timesR(L , 2) ; timesR(R , 2) ;

	update(t) ;
}

void modify(int t , int x , int y , int fx , int fy) {
	if (fx <= x && y <= fy) {
		addF(t , pw[tot]) ;
		addR(t , pw[tot]) ; dealson(t , x , y) ;

		return ;
	}
	down(t) ;

	int mid = (x + y) >> 1 ;
	if (fy <= mid) {
		int son = t << 1 | 1 ;
		addR(son , tre[son].f) ; dealson(son , mid + 1 , y) ;
		timesF(son , 2) ;

		modify(t << 1 , x , mid , fx , fy) ;
	}
	else if (mid < fx) {
		int son = t << 1 ;
		addR(son , tre[son].f) ; dealson(son , x , mid) ;
		timesF(son , 2) ;

		modify(t << 1 | 1 , mid + 1 , y , fx , fy) ;
	}
	else {
		modify(t << 1 , x , mid , fx , fy) ;
		modify(t << 1 | 1 , mid + 1 , y , fx , fy) ;
	}

	update(t) ;
}

int main() {
	n = read() ; m = read() ;
	pw[0] = 1 ;
	for (int i = 1 ; i <= m ; ++i) pw[i] = (pw[i - 1] << 1) % mod ;
	for (int i = 1 ; i <= (n << 2) ; ++i) tre[i].mulr = tre[i].mulf = 1 ;

	for (; m-- ;) {
		int op = read() ;

		if (op == 1) {
			int l , r ; l = read() ; r = read() ;

			modify(1 , 1 , n , l , r) ; ++tot ;
		}
		else printf("%d\n" , tre[1].sumr) ;
	}

	return 0 ;
}