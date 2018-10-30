#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 5e4 + 10 ;

struct data {
	ll sum ;
	int ty , x , y , k , idx ;
}qry[MAX_N] , tmp[MAX_N] ;
struct Node {
	ll sum , lazy ;
}tre[MAX_N << 2] ;

ll cnt[MAX_N] ;
int n , m , tans , ans[MAX_N] ;

///

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

void down(int t , int x , int y) {
	ll a = tre[t].lazy ;
	int L = t << 1 , R = t << 1 | 1 , mid = (x + y) >> 1 ;

	tre[L].sum += (mid - x + 1) * a ; tre[R].sum += (y - mid) * a ;
	tre[L].lazy += a ; tre[R].lazy += a ;

	tre[t].lazy = 0 ;
}

void modify(int t , int x , int y , int fx , int fy , int a) {
	if (y < fx || fy < x) return ;
	if (fx <= x && y <= fy) {
		tre[t].sum += (y - x + 1) * a ;
		tre[t].lazy += a ;

		return ;
	}

	down(t , x , y) ;

	int mid = (x + y) >> 1 ;
	modify(t << 1 , x , mid , fx , fy , a) ;
	modify(t << 1 | 1 , mid + 1 , y , fx , fy , a) ;

	tre[t].sum = tre[t << 1].sum + tre[t << 1 | 1].sum ;
}

ll find(int t , int x , int y , int fx , int fy) {
	if (y < fx || fy < x) return 0 ;
	if (fx <= x && y <= fy) return tre[t].sum ;

	down(t , x , y) ;
	int mid = (x + y) >> 1 ;
	ll s1 = find(t << 1 , x , mid , fx , fy) ,
	   s2 = find(t << 1 | 1 , mid + 1 , y , fx , fy) ;

	return s1 + s2 ;
}

///

void devide(int qx , int qy , int L , int R) {
	if (qx > qy) return ;

	if (L == R) {
		for (int i = qx ; i <= qy ; ++i)
			if (qry[i].ty == 2) ans[qry[i].idx] = L ;

		return ;
	}

	///

	int mid = (L + R) >> 1 ;
	for (int i = qx ; i <= qy ; ++i) {
		data *p = &qry[i] ;

		if (p->ty == 1 && p->k > mid) modify(1 , 1 , n , p->x , p->y , 1) ;
		else if (p->ty == 2) cnt[i] = find(1 , 1 , n , p->x , p->y) ;
	}
	for (int i = qx ; i <= qy ; ++i) {
		data *p = &qry[i] ;

		if (p->ty == 1 && p->k > mid) modify(1 , 1 , n , p->x , p->y , -1) ;
	}

	for (int i = qx ; i <= qy ; ++i) {
		data *p = &qry[i] ;

		if (p->ty == 2 && cnt[i] + p->sum >= p->k) cnt[i] = 1 ;
		else if (p->ty == 2) p->sum += cnt[i] , cnt[i] = 0 ;

		if (p->ty == 1 && p->k > mid) cnt[i] = 1 ;
		else if (p->ty == 1) cnt[i] = 0 ;
	}

	int o = 0 , l1 = 0 ;
	for (int i = qx ; i <= qy ; ++i) if (!cnt[i]) tmp[o++] = qry[i] , ++l1 ;
	for (int i = qx ; i <= qy ; ++i) if (cnt[i]) tmp[o++] = qry[i] ;

	for (int i = qx ; i <= qy ; ++i) qry[i] = tmp[i - qx] ;
	devide(qx , qx + l1 - 1 , L , mid) ; devide(qx + l1 , qy , mid + 1 , R) ;
}

///

int main() {
	n = read() ; m = read() ;
	for (int i = 1 ; i <= m ; ++i) {
		data *p = &qry[i] ;
		p->ty = read() ; p->x = read() ; p->y = read() ; p->k = read() ;

		if (p->ty == 2) p->idx = tans++ ;
	}

	///

	devide(1 , m , -n , n) ;

	for (int i = 0 ; i < tans ; ++i) printf("%d\n" , ans[i]) ;

	return 0 ;
}