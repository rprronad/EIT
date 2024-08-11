/*
   i
   Write a function given a string s, print 'yes' if it has a vowel in it else print 'no'.
   Sample execution :
   Test case 1 :
   Enter the string :  emertxe
   Yes, the vowel is present in the string

   Test case 2 :
   Enter the string :  xyz
   No, the vowel is not present in the string
 */
#if 1
#include <stdio.h>
#include <string.h>

void check_for_vowel(char *s)
{
	int len = strlen(s), flag = 0;
	for (int i = 0; i < len; i++) 
	{
		if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u' ||
				s[i] == 'A' || s[i] == 'E' || s[i] == 'I' || s[i] == 'O' || s[i] == 'U') 
		{
			flag = 1;
		}
	}
	if (flag == 1)
    printf("Yes, the vowel is present in the string\n");
    else
	printf("No, the vowel is not present in the string\n");
}

int main() 
{
	char s[100];
	printf("Enter the string: ");
	scanf("%s", s);
	check_for_vowel(s);
	return 0;
}
#endif

