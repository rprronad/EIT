#include <stdio.h>
/*
Write a function given two arrays print 'yes' if they are mirror image of each other, otherwise 'no' by using function
Sample execution :
Test case 1 :
Enter the array size :  4  
Array1 - 1 2 3 4
Array2 - 4 3 2 1
Expected output :
Yes

Test case 2 :
Enter the array size :  5  
Array1 - 10 20 30 40 50
Array2 - 50 40 30 10 20
Expected output :
No
*/
#if 1
char* check_mirror_image(int arr1[], int arr2[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (arr1[i] != arr2[size-1-i])
        {
            return "No";
        }
    }
    return "Yes";
}
int main()
{  
    int size;
	do
	{
    printf("Enter the array size: ");
    scanf("%d",&size);
    int arr1[size], arr2[size];
    printf("array1 - ");
    for(int i = 0; i < size; i++)
    {
        scanf("%d", &arr1[i]);
    }
    printf("array2 - ");
    for(int i = 0; i < size; i++)
    {
        scanf("%d", &arr2[i]);
    }
    char* result = check_mirror_image(arr1, arr2, size);

    printf("%s\n", result);
    }
	while(size>0);
    return 0;
}
#endif

