#include <vector>
#include <stdio.h>
#include <stdlib.h>

const int MAX_N = 1e6 + 10 ;

std::vector<int>  num['Z' + 10] ;

struct Segment {
	int num , lazy ;
}tree[4 * MAX_N] ;

char c[MAX_N] ;
int n , p[MAX_N] ;

///

void Build(int t , int x , int y) {
	if (x == y) {
		tree[t].num = x - 1 ;
		return ;
	}
	
	int mid = (x + y) >> 1 ;
	Build(t << 1 , x , mid) ;
	Build((t << 1) + 1 , mid + 1 , y) ;
	
	tree[t].num = tree[t << 1].num + tree[(t << 1) + 1].num ;
}

void down(int t , int x , int y) {
	int L = t << 1 , R = L + 1 , mid = (x + y) >> 1 ;
	
	tree[L].num += tree[t].lazy * (mid - x + 1) ;
	tree[L].lazy += tree[t].lazy ;
	tree[R].num += tree[t].lazy * (y - mid) ;
	tree[R].lazy += tree[t].lazy ;
	
	tree[t].lazy = 0 ;
}

void Update(int t , int x , int y , int fx , int fy) {
	if (y < fx || fy < x) return ;
	if (fx <= x && y <= fy) {
		--tree[t].lazy ;
		tree[t].num -= y - x + 1 ;
		return ;
	}
	down(t , x , y) ;
	
	int mid = (x + y) >> 1 ;
	Update(t << 1 , x , mid , fx , fy) ;
	Update((t << 1) + 1 , mid + 1 , y , fx , fy) ;
	
	tree[t].num = tree[t << 1].num + tree[(t << 1) + 1].num ;
}

int Find(int t , int x , int y , int f) {
	if (f < x || y < f) return 0 ;
	if (x == f && y == f) return tree[t].num ;
	
	down(t , x , y) ;
	
	int mid = (x + y) >> 1 ,
		s1 = Find(t << 1 , x , mid , f) ,
		s2 = Find((t << 1) + 1 , mid + 1 , y , f) ;
		
	return s1 + s2 ;
}

///

int main() {
	scanf("%d" , &n) ; getchar() ;
	for (int i = 1 ; i <= n ; ++i) {
		char a ;
		scanf("%c" , &a) ;
		num[a].push_back(i) ;
	}
	
	///
	
	for (int i = 'A' ; i <= 'Z' ; ++i)
		if (num[i].size()) p[i] = 0 ;
		else p[i] = -1 ;
	
	///
	
	Build(1 , 1 , n) ; getchar() ;
	long long res = 0 ;
	for (int i = 1 ; i <= n ; ++i) {
		char a ;
		scanf("%c" , &a) ;
		
		int np = num[a][p[a]++] ;
		res += Find(1 , 1 , n , np) ;
		Update(1 , 1 , n , np + 1 , n) ;
	}
	
	printf("%lld\n" , res) ;
	
	return 0 ;
}
