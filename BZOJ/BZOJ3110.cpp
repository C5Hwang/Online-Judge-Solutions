#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 50000 + 10 ;

struct Stree {
	long long s , lazy ;
	Stree *ch[2] ;
};
struct question {
	int q , x , y , k ;
}que[MAX_N] ;

Stree *root[4 * MAX_N] ;
int n , m , lcur , list[MAX_N] ;

void down(Stree *rt , int x , int y) {
	long long sum = rt->lazy ; rt->lazy = 0 ;
	for (int i = 0 ; i < 2 ; ++i) {
		int mid = (x + y) >> 1 ; long long len ;
		if (!i) len = mid - x  + 1 ;
		else len = y - mid ;
		
		if (!rt->ch[i]) rt->ch[i] = new Stree() ;
		rt->ch[i]->s += sum * len ; rt->ch[i]->lazy += sum ;
	}
}

void ins(Stree *&rt , int x , int y , int fx , int fy) {
	if (fy < x || y < fx) return ;
	
	if (!rt) rt = new Stree() ;
	if (fx <= x && y <= fy) {
		rt->s += (y - x + 1) ; ++rt->lazy ;
		return ;
	}

	if (rt->lazy) down(rt , x , y) ;

	int mid = (x + y) >> 1 ;
	ins(rt->ch[0] , x , mid , fx , fy) ;
	ins(rt->ch[1] , mid + 1 , y , fx , fy) ;
	
	int s1 = rt->ch[0] ? rt->ch[0]->s : 0 ,
		s2 = rt->ch[1] ? rt->ch[1]->s : 0 ;
	rt->s = s1 + s2 ;
}

long long query(Stree *rt , int x , int y , int fx , int fy) {
	if (fy < x || y < fx || !rt) return 0 ;
	if (fx <= x && y <= fy) return rt->s ;

	if (rt->lazy) down(rt , x , y) ;
	
	int mid = (x + y) >> 1 ;
	long long s1 = query(rt->ch[0] , x , mid , fx , fy) ,
	     	  s2 = query(rt->ch[1] , mid + 1 , y , fx , fy) ;

	return s1 + s2 ;
}

///

void update_add(int t , int x , int y , int fx , int fy , int f) {
	while (x != y) {
		ins(root[t] , 1 , n , fx , fy) ;

		int mid = (x + y) >> 1 ;
		if (f <= mid) t = t << 1 , y = mid ;
		else t = (t << 1) + 1 , x = mid + 1 ;
	}

	ins(root[t] , 1 , n , fx , fy) ;
}
 
int getnum(int t , int x , int y , int fx , int fy , int k) {
	while(x != y) {
		long long sum = query(root[(t << 1) + 1] , 1 , n , fx , fy) ;

		int mid = (x + y) >> 1 ;
		if (sum < k) t = t << 1 , y = mid , k -= sum ;
		else t = (t << 1) + 1 , x = mid + 1 ;
	}

	return list[x] ;
}

int find(int t) {
	int L = 0 , R = lcur ;
	while (L + 1 < R) {
		int mid = (L + R) >> 1 ;
		
		if (list[mid] >= t) R = mid ;
		else L = mid ;
	}
	
	return R ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 0 ; i < m ; ++i) {
		int q , x , y , k ;
		scanf("%d %d %d %d" , &q , &x , &y , &k) ;

		que[i].q = q ; que[i].x = x ; que[i].y = y ; que[i].k = k ;

		if (q == 1) list[++lcur] = k ;
	}

	///
	
	std::sort(list + 1 , list + 1 + lcur) ;
	int s = 1 , last = list[1] ;
	for (int i = 2 ; i <= lcur ; ++i)
		if (list[i] != last) list[++s] = last = list[i] ;
	lcur = s ;

	///
	
	for (int i = 0 ; i < m ; ++i) {
		int q , x , y , k ;
		q = que[i].q ; x = que[i].x ; y = que[i].y ; k = que[i].k ;

		if (q == 1) {
			k = find(k) ;
			update_add(1 , 1 , lcur , x , y , k) ;
		}
		else {
			int res = getnum(1 , 1 , lcur , x , y , k) ;
			printf("%d\n" , res) ;
		}
	}

	return 0 ;
}
