#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 50000 + 10 , MAX_M = 200000 + 10 , MAX_NUM = 1000000 + 10 ;

struct data {
	int x , y , bh , dep , ans ;
}q[MAX_M] ;

int n , m , sqn , a[MAX_N] , ap[MAX_NUM] ;

bool cmp1(data a , data b) {return a.dep < b.dep || a.dep == b.dep && a.y < b.y ;}
bool cmp2(data a , data b) {return a.bh < b.bh ;}

void add(int x , int &sum) {
	int num = a[x] ;
	if (!ap[num]) ++sum ;
	++ap[num] ;
}

void del(int x , int &sum) {
	int num = a[x] ;
	--ap[num] ;
	if (!ap[num]) --sum ;
}

int main() {
	scanf("%d" , &n) ; sqn = (int)sqrt(n) ;
	for (int i = 0 ; i < n ; ++i) scanf("%d" , &a[i]) ;
	scanf("%d" , &m) ;
	for (int i = 0 ; i < m ; ++i) {
		scanf("%d %d" , &q[i].x , &q[i].y) ;
		--q[i].x ; --q[i].y ;
		q[i].dep = q[i].x / sqn ; q[i].bh = i ;
	}

	///

	std::sort(q + 0 , q + m , cmp1) ;
	int L = -1 , R = -1 , last = -1 , sum = 0 ;
	for (int i = 0 ; i < m ; ++i)
		if (q[i].dep != last) {
			memset(ap , 0 , sizeof(ap)) ;

			sum = 0 ;
			L = q[i].x ; R = q[i].y ; last = q[i].dep ;
			for (int j = L ; j <= R ; ++j) add(j , sum) ;

			q[i].ans = sum ;
		}
		else {
			int nL = q[i].x , nR = q[i].y ;
			while (R < nR) add(++R , sum) ;
			while (L < nL) del(L++ , sum) ;
			while (nL < L) add(--L , sum) ;

			q[i].ans = sum ;
		}
	std::sort(q + 0 , q + m , cmp2) ;

	for (int i = 0 ; i < m ; ++i) printf("%d\n" , q[i].ans) ;

	return 0 ;
}
