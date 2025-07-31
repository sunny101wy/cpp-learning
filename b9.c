#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

//int cmpstring(char str1[],char str2[]){
//	int len1=strlen(str1);
//	int len2=strlen(str2);
//	if(len1!=len2)
//		return 1;
//	int i=0;
//	for( ;i<len1;i++){
//		if(str1[i]==str2[i])
//			continue;
//		contine;
//		ddfd;
//		return 1;
//	}
//	return 0;
//}
int cmpstring(char str1[],char str2[])
{
	int i=0;
	while(str1[i]!=0&&str2[i]!=0)
	{
		if(str1[i]==str2[i])
			i++;
		else
			return str1[i]-str2[i];
	}
	return str1[i]-str2[i];
}
typedef struct Student{
	float score;
	char name[10];
	int id;	
	struct Student*next;
}Student;
void dleat(int id,Student**head);
Student* loadFromFile();
Student* findStudent(Student*head,char name[]); 
void insert(Student**head,char name[],float score,int id){
	Student* node=(Student*)malloc(sizeof(Student));
	node->score=score;
	node->id=id;
	strcpy(node->name,name);
	node->next=NULL;
	if(*head==NULL){
		*head=node;
		return;
	}
	Student*temp=*head;
	while(temp->next!=NULL){
		temp=temp->next;
	}
	temp->next=node;
}

Student* createlink(){
	return NULL;
}
void writeList(Student*head);
Student*findStudent(Student*head,char name_std[]);


int main(int argc, char *argv[]) {
	Student*head=loadFromFile();
	printf("input the requirement:\n");
	while(1){
		char rqm;
		scanf("%c",&rqm);
		if(rqm=='q'){
			break;
		}
		if(rqm=='i'){
			char name[10];
			float score;
			int id;
			scanf("%s %f %d",name,&score,&id);
			insert(&head,name,score,id);
		}
		if(rqm=='f'){
			char name[10];
			scanf("%s",name);
			Student*temp=findStudent(head,name);
			printf("%s %d %f \n",temp->name,temp->id,temp->score);
		}
		if(rqm=='d'){
			int id;
			scanf("%d",&id);
			dleat(id,&head);
		}
	}
	writeList(head);	
	return 0;
}
Student* loadFromFile(){
	Student*head=createlink();
	FILE*file=fopen("input.txt","r");
	if(file==NULL){
		return;
	}
	int number=0;
	fscanf(file,"%d",&number);
	int i=0;
	for(i=0;i<number;i++){
		char name[10];
		int id=0;
		float score=0;
		fscanf(file,"%s",name);
		fscanf(file,"%d",&id);
		fscanf(file,"%f",&score);
		Student* node=(Student*)malloc(sizeof(Student));
		insert(&head,name,score,id);
	}
	fclose(file);
	return head;
	
}
void writeList(Student*head){
	FILE*file=fopen("result.txt","w");
	Student*temp=head;
	while(temp!=NULL){
		fprintf(file,"%s %d %f \n",temp->name,temp->id,temp->score);
		temp=temp->next;
	}
	fclose(file);
	return;
}
void dleat(int id,Student**head)
{
	Student*temp=*head;
	if(temp->id==id&&temp!=NULL)
	{
		*head=temp->next;
		free(temp);
		return;
	}
	Student*pre=temp;
	temp=temp->next;	
	while(temp!=NULL)
	{
		if(temp->id!=id)
		{
			pre = temp;
			temp=temp->next;
		}
		else
		{
			pre->next=temp->next;
			free(temp);
			break;
		}
	}
}
Student*findStudent(Student*head,char name_std[]){
	Student* temp=head;
	while(temp!=NULL)
	{
		if(cmpstring(temp->name,name_std)==0)
			return temp;
		temp=temp->next;
	}
	return NULL;
	
}
