#include <bits/stdc++.h>

const int L = 100 , R = 1000 - 1 ;

bool check(int x) {
	std::vector<int> num ; num.clear() ;
	for (; x ; x /= 10) num.push_back(x % 10) ;

	int s = num.size() ;
	for (int i = 0 ; i < s ; ++i) if (num[i] != num[s - i - 1]) return 0 ;
	return 1 ;
}

int main() {
	int ans = 0 ;
	for (int i = L ; i <= R ; ++i)
		for (int j = L ; j <= R ; ++j)
			if (check(i * j)) ans = std::max(ans , i * j) ;
	printf("%d\n" , ans) ;

	return 0 ;
}