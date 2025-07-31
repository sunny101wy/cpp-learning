#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Prime{
	int data;	
	struct Prime*next;
}Prime;
Prime*Creat()
{
	return NULL;
}




void findPrime(int n);
void find(Prime**head);
int main(int argc, char *argv[]) {
	int n;
	printf("input:");
	scanf("%d",&n);
	findPrime(n); 
}
void find(Prime**head){
	Prime* node=(Prime*)malloc(sizeof(Prime));
	node->data=2;
	node->next=NULL;
	*head=node;
	int i=3;
	for( ;i<1000000;i++)
	{
		Prime*temp=*head;
		Prime* last = *head;
	 	int flag=0;
	 	while(temp!=NULL)
		{
			if(i%temp->data==0) 
			{
				flag=1;
	 			break;
			}
			last = temp ;
	 		temp=temp->next;
	 		flag=0;
		}
		if(flag==0)
		{
	 		Prime* node2=(Prime*)malloc(sizeof(Prime));
			node2->data=i;
			node2->next=NULL;
			last->next=node2; 
	    }
	}
}
void findPrime(int n)
{
	bool*isPrime=(bool*)malloc((n+1)*sizeof(bool));
	for(int i=0;i<=n;i++)
	{
		isPrime[i]=true;
	} 
	for(int p=2;p*p<=n;p++)
	{
		if(isPrime[p]==true)
		{
			for(int i=p*p;i<=n;i+=p)
			{
				isPrime[i]=false;
			}
		}
	}
	FILE*file=fopen("result.txt","w");
	for(int i=2;i<=n;i++)
	{
		if(isPrime[i])
		{
		fprintf(file,"%d  ",i);
		}
	}
	fclose(file);
	free(isPrime);
}
