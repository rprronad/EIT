#include<stdio.h>
int index_difference(int arr[], int size) 
{
	int max_index = 0;
	int min_index = 0;
	for (int i = 0; i < size; i++)
	{
		if (arr[i] > arr[max_index]) 
		{
			max_index = i;
		}
		if (arr[i] < arr[min_index]) 
		{

			min_index = i;
		}
	}
	return max_index - min_index;
}

int main() 
{
	int size, i;
	printf("Enter the size of array: ");
	scanf("%d",&size);
	int arr[size];
	//printf("Enter array elements:\n");
	for( i = 0; i < size; i++)
	{
		printf("element - %d: ",i);
		scanf("%d", (arr+i));
		//scanf("%d", &arr[i]);
	}
	int diff = index_difference(arr, size);
	printf("Difference b/w index of largest & smallest no: %d\n", diff);
	return 0;
}


