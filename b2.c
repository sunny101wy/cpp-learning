#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int x=0;
	printf("input a number \n");
	scanf("%d",&x);
	if(x%2==1)
		printf("the number %d is odd",x);
	else
		printf("the number %d is not odd",x);
	return 0;
}
