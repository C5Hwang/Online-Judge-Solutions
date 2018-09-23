#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 2e5 + 10 ;
const long long INF = 1e15 ;

struct TREE {
	long long minn , lazy , sum ;
}tree[4 * MAX_N] ;

int n , q ;

///

void down(int t , int x , int y) {
	long long nl = tree[t].lazy ;
	int L = t << 1 , R = (t << 1) + 1 , mid = (x + y) >> 1 ;

	tree[L].lazy += nl ; tree[R].lazy += nl ;
	tree[L].minn += nl ; tree[R].minn += nl ;
	tree[L].sum += (mid - x + 1) * nl ; tree[R].sum += (y - mid) * nl ;

	tree[t].lazy = 0 ;
}

void update(int t) {
	int L = t << 1 , R = (t << 1) + 1 ;

	tree[t].sum = tree[L].sum + tree[R].sum ;
	tree[t].minn = std::min(tree[L].minn , tree[R].minn) ;
}

///

void add(int t , int x , int y , int fx , int fy , long long a) {
	if (y < fx || fy < x) return ;
	if (fx <= x && y <= fy) {
		tree[t].sum += (long long)(y - x + 1) * a ;
		tree[t].minn += a ;
		tree[t].lazy += a ;

		return ;
	}

	down(t , x , y) ;

	int mid = (x + y) >> 1 ;
	add(t << 1 , x , mid , fx , fy , a) ;
	add((t << 1) + 1 , mid + 1 , y , fx , fy , a) ;

	update(t) ;
}

long long GetMin(int t , int x , int y , int fx , int fy) {
	if (y < fx || fy < x) return INF ;
	if (fx <= x && y <= fy) return tree[t].minn ;

	down(t , x , y) ;

	int mid = (x + y) >> 1 ;
	long long m1 = GetMin(t << 1 , x , mid , fx , fy) ,
		 	  m2 = GetMin((t << 1) + 1 , mid + 1 , y , fx , fy) ;

	return std::min(m1 , m2) ;
}

long long GetSum(int t , int x , int y , int fx , int fy) {
	if (y < fx || fy < x) return 0 ;
	if (fx <= x && y <= fy) return tree[t].sum ;

	down(t , x , y) ;
	
	int mid = (x + y) >> 1 ;
	long long s1 = GetSum(t << 1 , x , mid , fx , fy) ,
		 	  s2 = GetSum((t << 1) + 1 , mid + 1 , y , fx , fy) ;

	return s1 + s2 ;
}

///

int main() {
	scanf("%d %d" , &n , &q) ;
	for (int i = 1 ; i <= n ; ++i) {
		int x ; scanf("%d" , &x) ;
		add(1 , 1 , n , i , i , x) ;
	}

	///
	
	for (int i = 0 ; i < q ; ++i) {
		char op ;
		int x , y ; long long a ;

		getchar() ; scanf("%c %d %d" , &op , &x , &y) ;
		if (op == 'P') scanf("%lld" , &a) ;

		long long res = 0 ;
		if (op == 'P') add(1 , 1 , n , x , y , a) ;
		else if (op == 'M') res = GetMin(1 , 1 , n , x , y) ;
		else res = GetSum(1 , 1 , n , x , y) ;

		if (op != 'P') printf("%lld\n" , res) ;
	}

	return 0 ;
}
