#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void stat(char*name);
void cove(char*name);
long getsize(char*name);
int main(int argc, char *argv[]) {
	printf("input the file name:\n");
	char file_name[100]={0};
    fgets(file_name,sizeof(file_name),stdin);
    
	file_name[strcspn(file_name, "\n")] = '\0';
    
    printf("the %s file size is %d",file_name,getsize(file_name));
    
    cove(file_name);
    stat(file_name);
	return 0;
}
long getsize(char*name){
	FILE*file=fopen(name,"rb");
	if(file==NULL){
		return -1;
	}
	fseek(file,0,SEEK_END);
	long filesize=ftell(file);
	fclose(file);
	return filesize;
}
void cove(char*name){
	char ch;
	char CH;
	FILE*file=fopen(name,"r");
	if(file==NULL){
		return;
	}
	FILE*filetwo=fopen("result.txt","w");
	if(filetwo==NULL){
		return;
	}
	while((ch=fgetc(file))!=EOF){
		CH=toupper(ch);
		fputc(CH,filetwo);
	}
	fclose(file);
}
void stat(char*name){
	int swen[256]={0};
	char c;
	int len=getsize(name);
	FILE*file=fopen(name,"r");
	if(file==NULL){
		return;
	}
	FILE*filetwo=fopen("result.txt","w");
	if(filetwo==NULL){
		return;
	}
	while((c=fgetc(file))!=EOF){
		swen[c]++;
	}
	int i=0;
	for(i=0;i<256;i++)
	{
		if(swen[i]>0&&!isspace(i)){
			fprintf(filetwo,"%c ocur %d \n",i,swen[i]);
			fprintf(stdout,"%c ocur %d \n",i,swen[i]);
		}
	}
	fclose(file);
}
