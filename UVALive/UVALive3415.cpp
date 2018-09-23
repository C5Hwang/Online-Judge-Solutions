#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAX_N = 500 + 10 , MAX_L = 100 + 10 ;

struct Link {
	int num ;
	Link *next ;
}list[MAX_N * MAX_N] ;
struct Query {
	int height ;
	char music[MAX_L] , sport[MAX_L] ;
}male[MAX_N] , female[MAX_N] ;

bool T[MAX_N] ;
Link *head[MAX_N] ;
int n , c1 , c2 , cur , left[MAX_N] ;

bool check(int x , int y) {
	if (abs(female[x].height - male[y].height) > 40) return 0 ;

	int len1 = strlen(female[x].music) , len2 = strlen(male[y].music) ;
	if (len1 == len2) {
		bool res = 0 ;
		for (int i = 0 ; i < len1 ; ++i)
			if (female[x].music[i] != male[y].music[i]) {res = 1 ; break;}

		if (res) return 0 ;
	}
	else return 0 ;

	len1 = strlen(female[x].sport) ; len2 = strlen(male[y].sport) ;
	if (len1 == len2) {
		bool res = 1 ;
		for (int i = 0 ; i < len1 ; ++i)
			if (female[x].sport[i] != male[y].sport[i]) {res = 0 ; break;}
		if (res) return 0 ;
	}

	return 1 ;
}

void init() {
	cur = c1 = c2 = 0 ;
	memset(head , 0 , sizeof(head)) ;
	memset(left , 0 , sizeof(left)) ;
}

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

///

bool match(int x) {
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (T[nx]) continue ;
		T[nx] = 1 ;

		if (!left[nx] || match(left[nx])) {
			left[nx] = x ;
			return 1 ;
		}
	}

	return 0 ;
}

int main() {
	int Q ; scanf("%d" , &Q) ;
	while (Q--) {
		init() ;

		scanf("%d" , &n) ;
		for (int i = 1 ; i <= n ; ++i) {
			int heg ; char se ;
			scanf("%d %c" , &heg , &se) ;

			if (se == 'M') {male[++c1].height = heg ; scanf("%s %s" , male[c1].music , male[c1].sport) ;}
			else {female[++c2].height = heg ; scanf("%s %s" , female[c2].music , female[c2].sport) ;}
		}

		///

		for (int i = 1 ; i <= c2 ; ++i)
			for (int j = 1 ; j <= c1 ; ++j)
				if (check(i , j)) ins(i , j) ;

		///

		int res = 0 ;
		for (int i = 1 ; i <= c2 ; ++i) {
			for (int j = 1 ; j <= c1 ; ++j) T[j] = 0 ;
			
			if (match(i)) ++res ;
		}

		printf("%d\n" , n - res) ;
	}

	return 0 ;
}
