#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 1e2 + 10 ;

int len1 , len2 ;
char s1[MAX_N] , s2[MAX_N] ;

bool cmp1(char a , char b) {return a < b ;}
bool cmp2(char a , char b) {return a > b ;}

int main() {
	scanf("%s %s" , s1 , s2) ;
	len1 = strlen(s1) ; len2 = strlen(s2) ;

	///

	std::sort(s1 + 0 , s1 + len1 , cmp1) ;
	std::sort(s2 + 0 , s2 + len2 , cmp2) ;

	int p = 0 , L = std::min(len1 , len2) ;
	for (; p < L && s1[p] == s2[p] ; ++p) ;

	if (p == L) {
		if (len1 >= len2) printf("No\n") ;
		else printf("Yes\n") ;
	}
	else {
		if (s1[p] > s2[p]) printf("No\n") ;
		else printf("Yes\n") ;
	}

	return 0 ;
}