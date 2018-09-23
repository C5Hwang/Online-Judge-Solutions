#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 2e5 + 10 , INF = 0x3f3f3f3f ;

struct data {
	int x , y , res , idx ;
}query[MAX_N] ;

std::vector<int> p[MAX_N] ;

bool ap[MAX_N] ;
int L , R , queue[MAX_N] , pt[MAX_N] ;
int n , m , maxa , a[MAX_N] , tree[MAX_N << 2] , temp[MAX_N] ;

///

bool cmp1(data a , data b) {
	return a.x < b.x || a.x == b.x && a.y < b.y ;
}

bool cmp2(data a , data b) {
	return a.idx < b.idx ;
}

///

void build(int t , int x , int y) {
	if (x == y) {
		tree[t] = temp[x] ;
		return ;
	}

	int mid = (x + y) >> 1 ;
	build(t << 1 , x , mid) ; build((t << 1) + 1 , mid + 1 , y) ;
	tree[t] = INF ;
}

void update(int t , int x , int y , int fx , int fy , int a) {
	if (y < fx || fy < x) return ;
	if (fx <= x && y <= fy) {
		tree[t] = std::min(tree[t] , a) ;
		return ;
	}

	int mid = (x + y) >> 1 ;
	update(t << 1 , x , mid , fx , fy , a) ;
	update((t << 1) + 1 , mid + 1 , y , fx , fy , a) ;
}

int getans(int t , int x , int y , int f) {
	if (f < x || y < f) return INF ;
	if (x == f && f == y) return tree[t] ;

	int mid = (x + y) >> 1 ,
		s1 = getans(t << 1 , x , mid , f) ,
		s2 = getans((t << 1) + 1 , mid + 1 , y , f) ;

	return std::min(tree[t] , std::min(s1 , s2)) ;
}

///

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 1 ; i <= n ; ++i) {
		scanf("%d" , &a[i]) ;
		maxa = std::max(maxa , a[i]) ; p[a[i]].push_back(i) ;
	}
	for (int i = 0 ; i < m ; ++i)
		scanf("%d %d" , &query[i].x , &query[i].y) , query[i].idx = i ;

	///

	++maxa ;
	std::sort(query + 0 , query + m , cmp1) ;

	for (int R = 0 ; R <= maxa ; ++R) queue[R] = R ;
	--R ;

	for (int i = 1 ; i <= n ; ++i) {
		ap[a[i]] = 1 ;
		while (ap[queue[L]]) ++L ;
		temp[i] = queue[L] ;
	}

	///
	
	build(1 , 1 , n) ; int np = 1 ;
	for (int i = 0 ; i < m ; ++i) {
		int x = query[i].x , y = query[i].y ;
		while (np < x) {
			int b = a[np] , ed ;
			if (pt[b] + 1 == p[b].size()) ed = n ;
			else ed = p[b][++pt[b]] - 1 ;
			update(1 , 1 , n , np , ed , b) ;
			++np ;
		}

		query[i].res = getans(1 , 1 , n , query[i].y) ;
	}

	std::sort(query + 0 , query + m , cmp2) ;
	for (int i = 0 ; i < m ; ++i) printf("%d\n" , query[i].res) ;

	return 0 ;
}
