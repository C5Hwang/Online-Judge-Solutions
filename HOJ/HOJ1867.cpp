#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std ;

const int MAX_N = 1000000 + 10 ;

int n , m , init , v[MAX_N] , tree[MAX_N] ;

void update(int x , int t) {
	while (x <= n) {
		tree[x] += t ;
		
		x += x & (-x) ;
	}
}

int find(int x) {
	int sum = 0 ;
	while (x != 0) {
		sum += tree[x] ;
		
		x -= x & (-x) ;
	}
	
	return sum ;
}

int sum(int x , int y) {
	int sx = find(x - 1) , sy = find(y) ;
	
	return sy - sx ;
}

bool check(int x) {
	if (x <= 1) return 0 ;
	
	for (int i = 2 ; i <= (int)sqrt(x) ; ++i)
		if (x % i == 0) return 0 ;
	
	return 1 ;
}

int main() {
	scanf("%d %d %d" , &n , &m , &init) ;
	for (int Q = 1 ; n || m || init ; ++Q) {
		printf("CASE #%d:\n" , Q) ;
		
		memset(tree , 0 , sizeof(tree)) ;
		
		for (int i = 1 ; i <= n ; ++i) v[i] = init ;
		if (check(init))
			for (int i = 1 ; i <= n ; ++i) update(i , 1) ;
		
		for (int i = 1 ; i <= m ; ++i) {
			int que , x , y ;
			scanf("%d %d %d" , &que , &x , &y) ;
			
			if (que == 0) {
				int nv = v[x] + y ;
				if (!check(v[x]) && check(nv)) update(x , 1) ;
				else if (check(v[x]) && !check(nv)) update(x , -1) ;
				
				v[x] += y ;
			}
			else printf("%d\n" , sum(x , y)) ;
		}
		
		printf("\n") ;
		scanf("%d %d %d" , &n , &m , &init) ;
	}
	
	return 0 ;
}
