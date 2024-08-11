/*
   Write a c program to print all unique elements in an array
Description:

Read 'n' and 'n' no.of elements of array.
Check for the unique number in the array.
Print only the unique numbers from the given array.
Sample output:

Test case 1:
Enter the size of the array: 4
Enter 4 elements: 3 2 2 5
The unique elements found in the array are : 3 5

Test case 2:
Enter the size of the array: 6
Enter 6 elements: 5 5 3 1 2 5
The unique elements found in the array are : 3 1 2
 */
#if 1
#include <stdio.h>
int main() 
{
	int n, i, j, count;
	printf("Enter the size of the array:");
	scanf("%d", &n);
	int arr[n];
	printf("Enter %d elements:",n);
	for (i = 0; i < n; i++) 
	{
		scanf("%d", &arr[i]);
	}
	printf("The unique elements in the array are:");
	for (i = 0; i < n; i++) 
	{
		count = 0;
		for (j = 0; j < n; j++)
		{
			if (arr[i] == arr[j]) 
			{
				count++;
			}
		}
		if (count == 1) 
		{
			printf("%d ", arr[i]);
		}
	}
	return 0;
}
#endif 


