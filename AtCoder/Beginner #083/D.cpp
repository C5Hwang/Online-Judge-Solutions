#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAX_N = 1e5 + 10 ;

char s[MAX_N] ;
bool com[MAX_N] ;
int len , cnt , num[MAX_N] , s1[MAX_N] , s2[MAX_N] ;

bool check(int x) {
	for (int i = 0 ; i < cnt ; ++i) com[i] = 0 ;

	for (int i = 0 ; i < cnt ; ++i) {
		int tmp ;

		tmp = s1[i] - num[i] ;
		if (s1[i] >= x && (tmp >= x || !tmp)) com[i] = 1 ;

		tmp = s2[i] - num[i] ;
		if (s2[i] >= x && (tmp >= x || !tmp)) com[i] = 1 ;
	}

	for (int i = 0 ; i < cnt ; ++i) {
		if (com[i]) continue ;

		if (s1[i] >= x) return 1 ;
		else break ;
	}

	for (int i = cnt - 1 ; i >= 0 ; --i) {
		if (com[i]) continue ;

		if (s2[i] >= x) return 1 ;
		else return 0 ;
	}

	return 1 ;
}

int main() {
	scanf("%s" , s) ;
	len = strlen(s) ;

	///

	char last = s[0] ; int sum = 0 ;
	for (int i = 0 ; i < len ; ++i)
		if (s[i] == last) ++sum ;
		else {
			last = s[i] ;
			num[cnt++] = sum ; sum = 1 ;
		}
	num[cnt++] = sum ;

	s1[0] = num[0] ; s2[cnt - 1] = num[cnt - 1] ;
	for (int i = 1 ; i < cnt ; ++i) s1[i] = s1[i - 1] + num[i] ;
	for (int i = cnt - 2 ; i >= 0 ; --i) s2[i] = s2[i + 1] + num[i] ;

	///

	int L = 1 , R = len + 1 ;
	while (L + 1 < R) {
		int mid = (L + R) >> 1 ;
		if (check(mid)) L = mid ;
		else R = mid ;
	}

	printf("%d\n" , L) ;

	return 0 ;
}