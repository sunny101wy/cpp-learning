#include <stdio.h>
#include <stdlib.h>
typedef struct MinHeap{
	int*array;
	int size;
	int capacity;
}MinHeap;
MinHeap*createMinHeap(int capacity){
	MinHeap*min=(MinHeap*)malloc(sizeof(MinHeap));
	min->size=0;
	min->capacity=capacity;
	min->array=(int*)malloc(capacity*sizeof(int));
	return min;
}
void bubbleUp(MinHeap*min,int index){
	while(index>0){
		int parent=(index-1)/2;
		if(min->array[index]>=min->array[parent]){
			break;
		}
		int blank=min->array[index];
		min->array[index]=min->array[parent];
		min->array[parent]=blank;
		
		index=parent;
	}
	return;
}
void insert(MinHeap*min,int data){
	if(min->size>=min->capacity){
		printf("error!!!");
		return;
	}
	min->array[min->size]=data;
	bubbleUp(min,min->size); 
	min->size++;
}
void swap(int *a,int *b){
	int temp=*a;
	*a=*b;
	*b=temp;
} 
void siftDown(int*array,int size,int index){
	while(1){
		int largest=index;
		int left=index*2+1;
		int right=index*2+2;
		if( left < size && array[left] > array[largest]  )
		{
			largest = left;
		}
		if( right < size && array[right] > array[largest]  )
		{
			largest = right;
		}
		if(largest!=index){
			swap(&array[largest],&array[index]);
			index=largest;
		}
		else
		{
			break;
		}
	}
}
void bubbleDown(int*array,int size,int index){
	while(1){
		int minest=index;
		int left=index*2+1;
		int right=index*2+2;
		if( left < size && array[left] < array[minest]  )
		{
			minest = left;
		}
		if( right < size && array[right] < array[minest]  )
		{
			minest = right;
		}
		if(minest!=index){
			swap(&array[minest],&array[index]);
			index=minest;
		}
		else
		{
			break;
		}
	}
}
void print(int*array,int size){
	for(int i=0;i<size;i++){
		printf("%d  ",array[i]);
	}
	printf("\n");
}
int deleteMin(MinHeap*min){
	if(min->size==0){
		return -1;
	}
	int data=min->array[0];
	min->array[0]=min->array[min->size-1];
	bubbleDown(min->array,min->size,0);
	min->size--;
	return data;
}

void heapSort(int*array,int size){
	for(int i=size/2-1;i>=0;i--){
		siftDown(array,size,i);
	}
//	print(array,size);
	for(int i=size-1;i>0;i--){
		swap(&array[0],&array[i]);
		siftDown(array,i,0);
	}
}

int main()
{
    MinHeap *heap = createMinHeap(18);
    insert(heap, 10);
    insert(heap, 19);
    insert(heap, 23);
    insert(heap, 8);
    insert(heap, 4);
    insert(heap, 2);
    insert(heap, 7);
    insert(heap, 6);
    insert(heap, 23);
    insert(heap, 9);
    insert(heap, 45);
    insert(heap, 3);

    printf("最小元素: %d\n", deleteMin(heap)); // 输出 1
    printf("最小元素: %d\n", deleteMin(heap)); // 输出 2
        printf("最小元素: %d\n", deleteMin(heap)); // 输出 2
    printf("最小元素: %d\n", deleteMin(heap)); // 输出 2
    printf("最小元素: %d\n", deleteMin(heap)); // 输出 2
    printf("最小元素: %d\n", deleteMin(heap)); // 输出 2
    printf("最小元素: %d\n", deleteMin(heap)); // 输出 2
    printf("最小元素: %d\n", deleteMin(heap)); // 输出 2
    printf("最小元素: %d\n", deleteMin(heap)); // 输出 2
    printf("最小元素: %d\n", deleteMin(heap)); // 输出 2 
    printf("最小元素: %d\n", deleteMin(heap)); // 输出 2
    printf("最小元素: %d\n", deleteMin(heap)); // 输出 2



    
    int array[] ={10,19,23,8,4,2,7,6,23,19,45,3};
    heapSort(array,12);
    print(array,12);
	return 0;
}
