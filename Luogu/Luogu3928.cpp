#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 1e5 + 10 ;

std::map<int , int> bh ;
int f[MAX_N][4] , tree[(3 * MAX_N) << 2][4] ;
int n , cnt , tot , anum[3 * MAX_N] , a[MAX_N][3] ;

void update(int t , int x , int y , int p , int ty , int a) {
	if (p < x || y < p) return ;
	if (x == p && p == y) {
		tree[t][ty] = std::max(tree[t][ty] , a) ;
		return ;
	}

	int mid = (x + y) >> 1 ;
	update(t << 1 , x , mid , p , ty , a) ;
	update((t << 1) + 1 , mid + 1 , y , p , ty , a) ;

	tree[t][ty] = std::max(tree[t << 1][ty] , tree[(t << 1) + 1][ty]) ;
}

int GetMax(int t , int x , int y , int fx , int fy , int ty) {
	if (y < fx || fy < x) return 0 ;
	if (fx <= x && y <= fy) return tree[t][ty] ;

	int mid = (x + y) >> 1 ,
		s1 = GetMax(t << 1 , x , mid , fx , fy , ty) ,
		s2 = GetMax((t << 1) + 1 , mid + 1 , y , fx , fy , ty) ;

	return std::max(s1 , s2) ;
}

int main() {
	scanf("%d" , &n) ;
	for (int j = 0 ; j < 3 ; ++j)
		for (int i = 0 ; i < n ; ++i) {
			scanf("%d" , &a[i][j]) ;
			anum[cnt++] = a[i][j] ;
		}

	///
	
	std::sort(anum + 0 , anum + (3 * n)) ;

	int last = anum[0] ; tot = 1 ;
	bh[last] = tot ;
	for (int i = 1 ; i < 3 * n ; ++i)
		if (last != anum[i]) {
			last = anum[i] ;
			bh[last] = ++tot ;
		}

	///
	
	int ans = 0 ;
	for (int i = 0 ; i < n ; ++i) {
		for (int j = 0 ; j < 4 ; ++j) {
			int na = j == 3 ? a[i][2] : a[i][j] ;
			int x , y , opt = 0 , np = bh[na] ;

			if (j % 2) x = np , y = tot ;
			else x = 1 , y = np ;

			for (int k = 0 ; k < 4 ; ++k)
				if (j < 2 || (j >= 2 && (j^1) != k)) opt = std::max(opt , GetMax(1 , 1 , tot , x , y , k)) ;

			f[i][j] = opt + 1 ;
		}

		for (int j = 0 ; j < 4 ; ++j) {
			int na = j == 3 ? a[i][2] : a[i][j] , np = bh[na] ;
			update(1 , 1 , tot , np , j , f[i][j]) ;

			ans = std::max(ans , f[i][j]) ;
		}
	}
	printf("%d\n" , ans) ;

	return 0 ;
}
