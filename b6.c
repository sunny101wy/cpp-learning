#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
bool padrome(char*name);
int cine(char*name);
char*sily(char*name);
void stat(char*name);
int main(int argc, char *argv[]) {
	int count=0;
	printf("input a number: \n");
	scanf("%d",&count);
	char*name=(char*)malloc(count *sizeof(char) );
	printf("input the name: \n");
	scanf("%s",name);
	printf("%s\n",(char*)sily(name));
printf("%s %s palindrome \n",name,padrome(name)?"is":"isnot");
	
	stat(name);
	return 0;
}
char*sily(char*name){
	int len=cine(name);
	char blank=0;
	int start=0;
	int end=len-1;
	for( ;start<end;start++,end--){
		blank=name[start];
		name[start]=name[end];
		name[end]=blank;
}
	return name;
}
int cine(char*name){
	int i=0;
	for( ;name[i]!=0;i++){
	}
	return i;
}
bool padrome(char*name){
	int len=cine(name);
	int start=0;
	int end=len-1;
	for( ;start<=end;start++,end--){
		if(name[start]!=name[end])
			return false;
	}
	return true;
}
void stat(char*name){
	int info[256]={0};
	int i=0;
	int len=strlen(name);
	for( ;i<len;i++){
		info[name[i]]++;
	}
	for(i=0;i<256;i++){
	
	if(info[i]>0)
		printf("%c occur %d \n",i,info[i]);
	}
}

