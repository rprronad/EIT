/* C Program to Print Number of Days in a Month using Else If Statement 
Description:
Read the month (integer value) from 1 - 12 and display the no.of days in the given month.
Assume the input is 1, 1 refers to January, because January is the 1st month of the year, if the input is 2 then respected month will be February and so on.
If the input is 1, no. of days in the 1st month will be 31.
Sample output:
Test case 1:
Enter the Month number : 7
No. of days in the given month is 31

Test case 2:
Enter the Month number : 11
No. of days in the given month is 30

Test case 3:
Enter the Month number : 2
No. of days in the given month is 28

Test case 4:
Enter the Month number : 17
Invalid input
*/

#include <stdio.h>
#if 1
int main()
{ 
	int month;
   do
   {	  
	printf("Enter the Month Number:");
	scanf("%d", &month);
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12 )
	{
		printf("\nNo. of days in the given month is 31\n");  	
	}
	else if ( month == 4 || month == 6 || month == 9 || month == 11 )
	{
		printf("\nNo. of days in the given month is 30\n");  	
	}  
	else if ( month == 2 )
	{
		printf("\nNo. of days in the given month is 28\n");  	
	} 
	else
		printf("\nInvalid input\n");
	}
	while(month >= 0);

	return 0;
}
#endif

#if 0
void printNumberOfDays(int N)
{

	// Check for 31 Days
	if (N == 1 || N == 3 || N == 5 || N == 7 || N == 8 || N == 10 || N == 12) 
	{
		printf("31 Days.");
	}

	// Check for 30 Days
	else if (N == 4 || N == 6 || N == 9 || N == 11) 
	{
		printf("30 Days.");
	}

	// Check for 28/29 Days
	else if (N == 2) 
	{
		printf("28/29 Days.");
	}

	// Else Invalid Input
	else 
	{
		printf("Invalid Month.");
	}
}

// Driver Code
int main()
{
	int N;
	// Input Month
	do
	{
		printf("Enter the month number: ");
		scanf("%d", &N);
		// Function Call
		printNumberOfDays(N);
	}
	while(N!=0);	
	return 0;
}
#endif

