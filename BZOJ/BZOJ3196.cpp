#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 50000 + 10 , lgN = 20 , INF = 0x3f3f3f3f ;

struct Treap {
	int num , s , r ;
	Treap *ch[2] ;

	int cmp(int x) {
		return x <= num ? 0 : 1 ;
	}
}tre[2 * MAX_N * lgN] ;

Treap *root[4 * MAX_N] ;
int n , m , cur , t[MAX_N] ;

void update(Treap *rt) {
	int sum = 1 ;

	for (int i = 0 ; i < 2 ; ++i)
		sum += rt->ch[i] ? rt->ch[i]->s : 0 ;

	rt->s = sum ;
}

void rotate(Treap *&rt , int d) {
	Treap *son = rt->ch[d^1] ;
	rt->ch[d^1] = son->ch[d] ; son->ch[d] = rt ; rt = son ;
	update(rt->ch[d]) ; update(rt) ;
}

void ins(Treap *&rt , int a) {
	if (!rt) {
		rt = &tre[cur++] ;
		rt->num = a ; rt->s = 1 ; rt->r = rand() ;
		rt->ch[0] = rt->ch[1] = NULL ;

		return ;
	}

	int d = rt->cmp(a) ;
	ins(rt->ch[d] , a) ; update(rt) ;
	if (rt->ch[d]->r < rt->r) rotate(rt , d^1) ;
}

void del(Treap *&rt , int a) {
	if (rt->num == a) {
		if (!rt->ch[0]) rt = rt->ch[1] ;
		else if (!rt->ch[1]) rt = rt->ch[0] ;
		else {
			int d = rt->ch[0]->r <= rt->ch[1]->r ? 1 : 0 ;

			rotate(rt , d) ;
			del(rt->ch[d] , a) ;
		}

		if (rt) update(rt) ;

		return ;
	}

	int d = rt->cmp(a) ;

	del(rt->ch[d] , a) ; update(rt) ;
}

int rank(Treap *rt , int a) {
	if (!rt) return 0 ;

	int r = rt->ch[0] ? rt->ch[0]->s + 1 : 1 ,
	    d = rt->cmp(a) , ans = MAX_N ;

	ans = rank(rt->ch[d] , a) + r * d ;

	return ans ;
}

int front(Treap *rt , int a) {
	if (!rt) return -1 ;

	int nt = rt->num ;

	if (nt < a) return std::max(nt , front(rt->ch[1] , a)) ;
	else return front(rt->ch[0] , a) ;
}

int behind(Treap *rt , int a) {
	if (!rt) return INF ;

	int nt = rt->num ;

	if (nt > a) return std::min(nt , behind(rt->ch[0] , a)) ;
	else return behind(rt->ch[1] , a) ;
}

///

void update_add(int t , int x , int y , int f , int a) {
	if (f < x || y < f) return ;
	ins(root[t] , a) ;

	if (x == y) return ;

	int mid = (x + y) >> 1 ;
	update_add(t * 2 , x , mid , f , a) ;
	update_add(t * 2 + 1 , mid + 1 , y , f , a) ;
}

void update_del(int t , int x , int y , int f , int a) {
	if (f < x || y < f) return ;
	del(root[t] , a) ;

	if (x == y) return ;

	int mid = (x + y) >> 1 ;
	update_del(t * 2 , x , mid , f , a) ;
	update_del(t * 2 + 1 , mid + 1 , y , f , a) ;
}

int getrank(int t , int x , int y , int fx , int fy , int a) {
	if (fy < x || y < fx) return 0 ;

	if (fx <= x && y <= fy) return rank(root[t] , a) ;

	int sum = 0 , mid = (x + y) >> 1 ;

	sum += getrank(t * 2 , x , mid , fx , fy , a) ;
	sum += getrank(t * 2 + 1 , mid + 1 , y , fx , fy , a) ;

	return sum ;
}

int getnum(int x , int y , int a) {
	int L = -1 , R = INF ;

	while (L + 1 < R) {
		int mid = (L + R) >> 1 ;
		
		if (getrank(1 , 1 , n , x , y , mid) + 1 <= a) L = mid ;
		else R = mid ;
	}

	return L ;
}

int getfront(int t , int x , int y , int fx , int fy , int a) {
	if (fy < x || y < fx) return -1 ;
	
	if (fx <= x && y <= fy) return front(root[t] , a) ;
	
	int mid = (x + y) >> 1 ;

	return std::max(getfront(t * 2 , x , mid , fx , fy , a) , getfront(t * 2 + 1 , mid + 1 , y , fx , fy , a)) ;
}

int getbehind(int t , int x , int y , int fx , int fy , int a) {
	if (fy < x || y < fx) return INF ;

	if (fx <= x && y <= fy) return behind(root[t] , a) ;

	int mid = (x + y) >> 1 ;

	return std::min(getbehind(t * 2 , x , mid , fx , fy , a) , getbehind(t * 2 + 1 , mid + 1 , y , fx , fy , a)) ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 1 ; i <= n ; ++i) {
		scanf("%d" , &t[i]) ;
		update_add(1 , 1 , n , i , t[i]) ;
	}

	///
	
	for (int i = 0 ; i < m ; ++i) {
		int q , x , y , k , res ;
		scanf("%d %d %d" , &q , &x , &y) ;

		if (q != 3) scanf("%d" ,  &k) ;

		if (q == 1)  res = getrank(1 , 1 , n , x , y , k) + 1 ;
		else if (q == 2)  res = getnum(x , y , k) ;
		else if (q == 3) {update_del(1 , 1 , n , x , t[x]) ; update_add(1 , 1 , n , x , t[x] = y) ;}
		else if (q == 4) res = getfront(1 , 1 , n , x , y , k) ;
		else if (q == 5) res = getbehind(1 , 1 , n , x , y , k) ;

		if (q != 3) printf("%d\n" , res) ;
	}

	return 0 ;
}
