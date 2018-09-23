#include <map>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAX_XY = 5 , MAX_K = 10 + 10 ,
		  dx[4] = {0 , 1 , 1 , 1} ,
		  dy[4] = {1 , 0 , 1 , -1} ;

std::map<long long , short> sta ;
int n , m , k , ex , ey , inf[MAX_XY][MAX_XY] , sum[MAX_XY][MAX_XY] ;

long long hash() {
	long long t = 1 , ans = 0 ;
	for (int i = 0 ; i < 3 ; ++i)
		for (int j = 0 ; j < 3 ; ++j) {
			ans += sum[i][j] * t ;
			t *= 9 ;
		}
	
	return ans ;
}

bool find(int k) {
	if (k == 1) {
		if (sum[ex][ey]) return 1 ;
		else return 0 ;
	}
	
	long long h = hash() ;
	if (sta[h]) return sta[h] ;
	
	for (int x1 = 0 ; x1 < 3 ; ++x1)
		for (int y1 = 0 ; y1 < 3 ; ++y1) {
			if (!sum[x1][y1]) continue ;
			
			for (int p = 0 ; p < 4 ; ++p) {
				int x2 = x1 + dx[p] , y2 = y1 + dy[p] ;
				if (x2 < 0) x2 += 3 ;
				if (y2 < 0) y2 += 3 ;
				if (x2 >= n || y2 >= m) continue ;
				x2 %= 3 ; y2 %= 3 ;
				
				if (!sum[x2][y2]) continue ;
				
				int tx = (x2 + dx[p] + 3) % 3 , ty = (y2 + dy[p] + 3) % 3 ;
				
				if (inf[tx][ty] == sum[tx][ty]) continue ;
				++sum[tx][ty] ; --sum[x1][y1] ; --sum[x2][y2] ;
				bool ans = find(k - 1) ;
				--sum[tx][ty] ; ++sum[x1][y1] ; ++sum[x2][y2] ;
				
				if (ans) return (sta[h] = 1) ;
			}
		}
	
	return (sta[h] = 0) ;
}

int main() {
	while (scanf("%d %d %d %d %d" , &k , &n , &m , &ex , &ey) != EOF) {
		sta.clear() ;
		memset(inf , 0 , sizeof(inf)) ;
		memset(sum , 0 , sizeof(sum)) ;
		
		--ex ; --ey ; ex %= 3 ; ey %= 3 ;
		for (int i = 0 ; i < n ; ++i)
			for (int j = 0 ; j < m ; ++j) {
				int x = i % 3 , y = j % 3 ;
				++inf[x][y] ;
			}
		for (int i = 0 ; i < k ; ++i) {
			int x , y ;
			scanf("%d %d" , &x , &y) ;
			--x ; --y ; x %= 3 ; y %= 3 ;
			++sum[x][y] ;
		}
		
		///
		
		bool ans = find(k) ;
		if (ans) printf("Yes\n") ;
		else printf("No\n") ;
	}
	
	return 0 ;
}
