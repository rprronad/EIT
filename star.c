
#include <stdio.h>
#include<string.h>

void print_string(char*);

int main() {
   
   char str[100];
   printf("Enter the string=");
   scanf("%s",str);
   
   print_string( str );
   
   printf(" the string = %s",str);
 
}


void print_string(char *s ) {
   int mid = 0,mid1=0;
   
   mid = ( strlen(s) )/2;
   mid1 = mid - 1;
   
   if( ( strlen(s)%2 != 0) ) {
     s[mid]  = '*';
   }
   else  if( ( strlen(s)%2 == 0) ){
       s[mid]  = '*';
     s[ mid1 ]  = '*';  
   }
    
}

