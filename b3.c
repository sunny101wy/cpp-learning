#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int calc(int x);
int calc2(int y);
int calc3(int z);
int calc4(int w); 
int main(int argc, char *argv[]) {
	float x=0,y=0,a=0,z=0,w=0;
	printf("input four numbers \n");
	scanf("%f %f %f %f",&x ,&y,&z,&w);
	a=y;
	y=x;
	x=a;
	printf("%f %f %d %d %d %d",x,y,calc(x),calc2(y),calc3(z),calc4(w));
	
	return 0;
}
int calc(int x){
	int result=1;
	int i=1;
	for( ;i<=x;i++)
		result = i*result;
									
	return result;
}
int calc2(int y){
	int result=1;
	int i=1;
	while(i<=y){
		result*=i;
		i++;
	}
	return result;  
}		
int calc3(int z){
	int result=1;
	int i=1;
	do{

		result*=i;
		i++;
	}
	while(i<=z);
	
	return result;
}
int calc4(int w){
	if(w>1)
		return w*calc4(w-1);
	else
		return 1;
}
