#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int P = 10 , prime[10] = {2 , 3 , 5 , 7 , 11 , 13 , 17 , 19 , 23 , 29} ;

struct data{int x , y ;} ;

std::vector<data> num ;

int n ;

void find(int x , ll s , int g , int last) {
	if (!last) {
		num.push_back((data){(int)s , g}) ;
		return ;
	}

	for (int i = 0 ; i <= last && s <= n ; s *= prime[x] , ++i)
		find(x + 1 , s , g * (i + 1) , i) ;
}

bool cmp(data a , data b) {return a.x < b.x ;}

int main() {
	scanf("%d" , &n) ;
	find(0 , 1 , 1 , 32) ;

	///

	std::sort(num.begin() , num.end() , cmp) ;

	int last = 0 , ans = 0 , len = num.size() ;
	for (int i = 0 ; i < len ; ++i)
		if (num[i].y > last) {
			last = num[i].y ;
			ans = num[i].x ;
		}

	printf("%d\n" , ans) ;

	return 0 ;
}