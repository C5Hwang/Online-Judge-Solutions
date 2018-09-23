#include <stdio.h>
#include <stdlib.h>

const int MAX_N = 5e5 + 10 ;

struct data {
	int type , idx , val ;
}query[MAX_N << 2] , temp[MAX_N << 2] ;

int n , m , qt , tot , ans[MAX_N] ;

bool cmp(int x , int y) {
	return query[x].idx <= query[y].idx ;
}

void cdq(int x , int y) {
	if (x == y) return ;
	int mid = (x + y) >> 1 ;
	cdq(x , mid) ; cdq(mid + 1 , y) ;

	int p1 = x , p2 = mid + 1 , sum = 0 , t = 0 ;
	while (p1 <= mid && p2 <= y) {
		if (cmp(p1 , p2)) {
			data *p = &query[p1] ;
			if (p->type == 1) sum += p->val ;
			temp[t++] = *p ; ++p1 ;
		}
		else {
			data *p = &query[p2] ;
			if (p->type == 2) ans[p->val] += sum ;
			else if (p->type == 3) ans[p->val] -= sum ;
			temp[t++] = *p ; ++p2 ;
		}
	}

	for (; p1 <= mid ; ++p1) temp[t++] = query[p1] ;
	for (; p2 <= y ; ++p2) {
		data *p = &query[p2] ;
		if (p->type == 2) ans[p->val] += sum ;
		else if (p->type == 3) ans[p->val] -= sum ;
		temp[t++] = *p ;
	}

	for (int i = 0 ; i < t ; ++i) query[i + x] = temp[i] ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 1 ; i <= n ; ++i) {
		int a ; scanf("%d" , &a) ;
		query[++tot] = (data){1 , i , a} ;
	}
	for (int i = 0 ; i < m ; ++i) {
		int ty , x , y ;
		scanf("%d %d %d" , &ty , &x , &y) ;

		if (ty == 1) query[++tot] = (data){1 , x , y} ;
		else {
			if (x - 1 > 0) query[++tot] = (data){3 , x - 1 , qt} ;
			query[++tot] = (data){2 , y , qt} ;
			++qt ;
		}
	}

	///
	
	cdq(1 , tot) ;
	for (int i = 0 ; i < qt ; ++i)
		printf("%d\n" , ans[i]) ;

	return 0 ;
}
