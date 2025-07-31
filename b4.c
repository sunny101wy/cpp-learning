#include <stdio.h>
#include <stdlib.h>

#define AR_COUNT  9
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int mical(int [],int );
int lone(int [],int );
int main(int argc, char *argv[]) {
	int in_count=0;
	printf("input count number \n");
	scanf("%d",&in_count);
//	int ally[in_count];
	int*ally=(int*)malloc( in_count * sizeof(int) );
	int i=0;
	for(;i<in_count;i++){
		printf("input number %d:",i);
		scanf("%d",&ally[i]); 
	}
	int min_index = mical(ally,in_count);
	int max_index = lone(ally,in_count);
	printf("OK %d %d %d %d",max_index,ally[max_index],min_index,ally[min_index]);
	
	free(ally);
	return 0;
}
int lone(int ally[],int count){
	int i=0;
	int stand=0;
	for( ;i<count;i++){
		if(ally[stand]<ally[i])
			stand=i;
		
	}
	return stand;
}
int mical(int ally[],int count){
	int i=0;
	int index=0;
	for( ;i<count;i++){
		if(ally[index]>ally[i])
			index=i;
	}
	return index ;
}
void stat(char*name){
	int info[256]={0};
	int len=strlen(name);
	int i=0;
	for( ;i<len;i++){
		info[name[i]]++;
	}
	for (i=0;i<256;i++)
	{
		if(info[i]>0)
			printf("%c ocuur %d\n",i,info[i]) ;
	}
}
