#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 ;

struct data {int L , R ;}are[MAX_N] ;
struct Link {
	int num , val ;
	Link *next ;
}list[MAX_N] ;

Link *head[MAX_N] ;
int n , m , cur , f[MAX_N] ;

bool cmp(data a , data b) {return a.R < b.R || a.R == b.R && a.L < b.L ;}

void ins(int x , int y , int v) {
	list[cur].num = y ;
	list[cur].val = v ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

int main() {
	scanf("%d" , &n) ;
	for (int i = 0 ; i < n ; ++i) {
		int a , b ; scanf("%d %d" , &a , &b) ;
		++a ; b = n - b ;

		if (a <= b) are[m++] = (data){a , b} ;
	}

	///

	std::sort(are + 0 , are + m , cmp) ;

	data *last = &are[0] ; int sum = 1 ;
	for (int i = 1 ; i < m ; ++i)
		if (are[i].L == last->L && are[i].R == last->R) ++sum ;
		else {
			ins(last->R , last->L , std::min(sum , last->R - last->L + 1)) ;
			sum = 1 ; last = &are[i] ;
		}

	ins(last->R , last->L , std::min(sum , last->R - last->L + 1)) ;

	///

	for (int i = 1 ; i <= n ; ++i) {
		f[i] = f[i - 1] ;

		for (Link *h = head[i] ; h ; h = h->next) {
			int j = h->num ;
			f[i] = std::max(f[j - 1] + h->val , f[i]) ;
		}
	}

	printf("%d\n" , n - f[n]) ;

	return 0 ;
}