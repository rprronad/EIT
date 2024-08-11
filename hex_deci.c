/*
Write a C program to convert a hexadecimal number into binary without using an array.
Read an hexadecimal number from user.
Print the binary equivalent of the entered number in 32 bit format.
Sample output:
Test case 1:
Enter the hexadecimal : 11
Binary equivalent of 0x11 is : 00000000000000000000000000010001

Test case 2:
Enter the hexadecimal : A5
Binary equivalent of 0xA5 is : 00000000000000000000000010100101

Test case 3:
Enter the hexadecimal : AF5
Binary equivalent of 0xAF5 is : 00000000000000000000101011110101
*/

#include <stdio.h>
int main()
{
	int hexa;
	do
	{
		int i;
		printf("Enetr the hexadecimal number:");
		scanf("%X",&hexa);
		unsigned int mask = 0x80000000;
		printf("Binary equivalent of 0x%X is:",hexa);
		for(i = 0; i <= 31; i++)
		{
			if(hexa & mask)
			{
				printf("1");
			}
			else
			{
				printf("0");
			}
			mask>>=1;
		}
		printf("\n");
	}
	while(1);
	return 0;
}

