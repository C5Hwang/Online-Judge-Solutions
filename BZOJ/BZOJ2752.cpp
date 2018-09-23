#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 ;

struct Link {
	ll sum[3] , lazy ;
}tree[MAX_N << 2] ;

int n , m ;
ll s[3][MAX_N] ;

ll qpow(int x , int t) {
	if (!t) return 1 ;
	else if (t == 1) return x ;
	else return (ll)x * x ;
}

void update(int t) {
	for (int i = 0 ; i < 3 ; ++i)
		tree[t].sum[i] = tree[t << 1].sum[i] + tree[t << 1 | 1].sum[i] ;
}

void change(int t , int x , int y , ll v) {
	for (int i = 0 ; i < 3 ; ++i)
		tree[t].sum[i] += (s[i][y] - s[i][x - 1]) * v ;
	tree[t].lazy += v ;
}

void down(int t , int x , int y) {
	int mid = (x + y) >> 1 ;
	ll tmp = tree[t].lazy ;

	change(t << 1 , x , mid , tmp) ;
	change(t << 1 | 1 , mid + 1 , y , tmp) ;
	tree[t].lazy = 0 ;
}

void modify(int t , int x , int y , int fx , int fy , int v) {
	if (y < fx || fy < x) return ;
	if (fx <= x && y <= fy) {
		change(t , x , y , v) ;

		return ;
	}

	down(t , x , y) ;

	int mid = (x + y) >> 1 ;
	modify(t << 1 , x , mid , fx , fy , v) ;
	modify(t << 1 | 1 , mid + 1 , y , fx , fy , v) ;

	update(t) ;
}

ll query(int t , int x , int y , int fx , int fy) {
	if (y < fx || fy < x) return 0 ;
	if (fx <= x && y <= fy) {
		ll tmp = tree[t].sum[0] * (fy - fx + 1 - (ll)fx * fy) + tree[t].sum[1] * (fy + fx) - tree[t].sum[2] ;
		return tmp ;
	}

	down(t , x , y) ;

	int mid = (x + y) >> 1 ;
	ll s1 = query(t << 1 , x , mid , fx , fy) ,
	   s2 = query(t << 1 | 1 , mid + 1 , y , fx , fy) ;

	return s1 + s2 ;
}

ll gcd(ll x , ll y) {return y ? gcd(y , x % y) : x ;}

int main() {
	scanf("%d %d" , &n , &m) ;

	///

	for (int i = 0 ; i < 3 ; ++i)
		for (int j = 1 ; j <= n ; ++j)
			s[i][j] = s[i][j - 1] + qpow(j , i) ;
	for (int i = 0 ; i < m ; ++i) {
		char op[2] ; int x , y , v ;
		scanf("%s %d %d" , op , &x , &y) ; --y ;
		if (op[0] == 'C') scanf("%d" , &v) ;

		if (op[0] == 'C') modify(1 , 1 , n , x , y , v) ;
		else {
			ll a = query(1 , 1 , n , x , y) , b = (ll)(y - x + 1) * (y - x + 2) >> 1 ;			
			ll d = gcd(a , b) ; a /= d ; b /= d ;

			printf("%lld/%lld\n" , a , b) ;
		}
	}

	return 0 ;
}