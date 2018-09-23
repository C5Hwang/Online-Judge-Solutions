#include <stdio.h>
#include <stdlib.h>

const int MAX_N = 1e3 + 60 ;

struct data {
	int x , y , r ;
}t[MAX_N] ;
struct Link {
	int num ;
	Link *next ;
}list[2 * MAX_N] ;

Link *head[MAX_N] ;
double res , sp[MAX_N] ;
int n , cur , ex , ey , st ;

bool dfs(int x , int fa) {
	if (t[x].x == ex && t[x].y == ey) {res += sp[x] ; return 1 ;}

	bool ad = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa) continue ;

		sp[nx] = sp[x] * t[x].r / t[nx].r ;
		ad |= dfs(nx , x) ;

		if (ad) break ;
	}

	if (ad) res += sp[x] ;
	return ad ;
}

int squ(int x) {
	return x * x ;
}

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

int main() {
	scanf("%d %d %d" , &n , &ex , &ey) ;
	for (int i = 0 ; i < n ; ++i) {
		scanf("%d %d %d" , &t[i].x , &t[i].y , &t[i].r) ;
		if (!t[i].x && !t[i].y) st = i ;
	}

	///
	
	for (int i = 0 ; i < n ; ++i)
		for (int j = 0 ; j < n ; ++j) {
			int s1 = squ(t[i].x - t[j].x) + squ(t[i].y - t[j].y) ,
				s2 = squ(t[i].r + t[j].r) ;

			if (s1 == s2) ins(i , j) ;
		}
	sp[st] = 1e4 ; dfs(st , st) ;

	printf("%d\n" , (int)res) ;

	return 0 ;
}
