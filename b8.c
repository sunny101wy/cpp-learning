#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void sort(int swen[],int num,int sen);
int main(int argc, char *argv[]) {
	int sen=0;
	FILE*file=fopen("input.txt","r");
	FILE*file2=fopen("result.txt","w");
	fscanf(file,"%d",&sen);
	int num;
	fscanf(file,"%d",&num);
	int*swen=(int*)malloc(num* sizeof(int) );
	int count=0;
	for(;count<num;count++)
	{
		fscanf(file,"%d",&swen[count]);		
	}
	sort(swen,num,sen);
	for(count=0;count<num;count++)
	{
		fprintf(file2,"%d \n",swen[count]);		
	}
	fclose(file);
	fclose(file2);
	return 0;
}
void sort(int swen[],int num,int sen){
	int i=0;
	int blank=0;
	int j=0;
	int swap=0;
	for( ;i<num-1;i++)
	{	
		swap=0;
		for(j=0;j<num-i-1;j++)
		{
			if((swen[j]>swen[j+1]&&sen==1)||(swen[j]<swen[j+1]&&sen==0))
			{
				blank=swen[j];
				swen[j]=swen[j+1];
				swen[j+1]=blank;
				swap=1;
			}
			else
				swap=0;	
		}
		if(swap==0)
			break;
	}
}
