#include <stdio.h>
int main() {
	int n;
	scanf("%d", &n);
	int num[6],i=0,j=0;
	while(i<6){
		num[i++]=n%10;
		n=n/10;
	}
	for(i=5;i>=0&&num[i]==0;i--);
	while(num[i]==num[j]&&i>=j){
		i--;
		j++;
	}
	if (i<=j) {
		printf("Y\n");
	} else {
		printf("N\n");
	}
	return 0;
}
