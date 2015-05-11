#include <cstdio>
int main(){
	int n,k;
	while(~scanf("%d%d" , &n , &k)){
		if(k > n || k == 2 && (n & 1)) puts("Yes");
		else puts("No");
	}
	return 0;
}