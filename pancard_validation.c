/*
Write a function Indian pan card issuing authority have found some fake pan cards. They have hired you so that you can validate pan card for them. Your task is to develop a suitable algorithm which could check if pan is valid or not

Description:
Pan must have uppercase letters only.
It must be of 10 character only
From index 1 to 5 all must be letters(A-Z),last index must be letter
Rest all must be integer Starting from 1
Input :
You are given a input string which indicates the PAN number
Output :
Print 'Valid Pan' if it is valid PAN number, else print 'Not Valid Pan'

Sample execution :
Test case 1 :
Enter the string : HXTPS2142R
Yes, this is a valid PAN card number

Test case 2 :
Enter the string : edcba1224t
No, this is not a valid PAN card number
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

int is_valid_pan(char *pan) 
{
	int i;
	// Check if PAN is of length 10
	if (strlen(pan) != 10) 
	{
		return 0;
	}
	// Check if first 5 characters are uppercase letters
	for (i = 0; i < 5; i++) 
	{
		if (!isupper(pan[i]))
		{
			return 0;
		}
	}
	// Check if last character is an uppercase letter
	if (!isupper(pan[9])) 
	{
		return 0;
	}
	// Check if the remaining characters are digits
	for (i = 5; i < 9; i++) 
	{
		if (!isdigit(pan[i])) 
		{
			return 0;
		}
	}
	// If all checks pass, the PAN is valid
	return 1;
}

int main() 
{
	char pan[11];
	printf("Enter the string :");
	scanf("%s", pan);
	if (is_valid_pan(pan)) 
	{
		printf("Yes, this is a valid PAN card numbe\n");
	} else {
		printf("No, this is not a valid PAN card number\n");
	}
	return 0;
}


