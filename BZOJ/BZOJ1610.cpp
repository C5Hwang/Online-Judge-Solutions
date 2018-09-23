#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 200 + 10 ;

struct data {
	int x , y , pos ;
}t[MAX_N] , list[MAX_N * MAX_N] ;

int n , cur ;

int gcd(int x , int y) {
	if (!y) return x ;
	else return gcd(y , x % y) ;
}

bool cmp(data a , data b) {
	return a.pos < b.pos || a.pos == b.pos && a.x * b.y < b.x * a.y ;
}

bool check(data a , data b) {
	return a.pos == b.pos && a.x == b.x && a.y == b.y ;
}

int main() {
	scanf("%d" , &n) ;
	for (int i = 0 ; i < n ; ++i)
		scanf("%d %d" , &t[i].x , &t[i].y) ;

	///
	
	for (int i = 0 ; i < n ; ++i)
		for (int j = 0 ; j < n ; ++j)
			if (i != j) {
				int a = t[i].x - t[j].x , b = t[i].y - t[j].y , g = gcd(abs(a) , abs(b)) ;
				if (a * b > 0) list[cur].pos = 0 ;
				else list[cur].pos = 1 ;

				list[cur].x = abs(a) / g ; list[cur++].y = abs(b) / g ;
			}
	std::sort(list + 0 , list + cur , cmp) ;

	///
	
	int res = 1 ;
	for (int i = 1 ; i < cur ; ++i)
		if (!check(list[i] , list[i - 1])) ++res ;
	printf("%d\n" , res) ;

	return 0 ;
}
