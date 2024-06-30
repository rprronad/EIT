/*
Name        : RAVIKUMAR RONAD
Date        : 17-FEB-2023
Project Name: LSB(Least Significant Bit)-Steganography
Description : Steganography is the art of hiding the fact that communication is taking place, by hiding information in other 
              information. Many different carrier file formats can be used, but digital images are the most popular because of 
              their frequency on the internet. For hiding secret information in images, there exists a large variety of 
              steganography techniques some are more complex than others and all of them have respective strong and weak points.
 */




/*---------------------SYSTEM & USER DEFINED HEADER FILE NAMES---------------------------------------------------------*/
#include <stdio.h>                           
#include <string.h>
#include "encode.h"
#include "decode.h"
#include "types.h"
#include <unistd.h>
#include <stdlib.h>

/*-------------------------------------FUNCTION DEFINITION FOR OPERATION TYPE-----------------------------------------*/
OperationType check_operation_type(char *argv[])              
{
    if(!strcmp(argv[1],"-e"))                                   // String compare & check it's -e or not.
    {
        return e_encode;
    }
    if(!strcmp(argv[1],"-d"))                                   // String compare & check it's -d or not.
    {
        return e_decode;
    }
    else
        return e_unsupported;                               
}
/*---------------------MAIN FUNCTION (Passing 2 Arguments are count & Vector)------------------------------------------*/
int main(int argc, char *argv[])
{   

    EncodeInfo encInfo;                                                         // Structure declaration.
    DecodeInfo dncInfo;                                                         // Structure declaration.
    if(argc > 1)
    {
        int operation = check_operation_type(argv);                             // Function call operation type(encode or decode).
        if(argc >= 1)
        {
            if( operation == e_encode)                                          // Check the conditon operation for "encode" or not.
            {
                printf("+---------------------------------------------------------------+\n");
                printf("|\t\tSelected ENCODE operation\t\t\t|\n");
                printf("|\033[92m\t\t*************************\t\t\t\033[0m|\n|\t\t\t\t\t\t\t\t|\n");
                sleep(1);   

                if(read_and_validate_encode_args(argv, &encInfo) == e_success)  // Function call of read and validate arguments.
                {
                    printf("|\tENCODING: Read and validate arguments were successed\t|\n");
                    if(do_encoding(&encInfo) == e_success)                      // Check Encoding process is successed or not.
                    {
                        sleep(2);
                        printf("|\t\e\033[5m--------ENCODING is Done successfully-------\033[m\t\t|\n"); // Prints the message,When endoing is over.
                        printf("+---------------------------------------------------------------+\n");


                    }
                }
                else
                {
                    printf("|\tENCODING: Read and validate arguments were Failed\t|\n");  // Prints the message, When encoding is fails.
                }
            }
            else if( operation == e_decode)                                     // Check the condition for "decode" or not.
            {
                printf("+---------------------------------------------------------------+\n");
                printf("|\t\tSelected DECODE operation\t\t\t|\n");
                printf("|\033[92m\t\t**************************\t\t\t\033[0m|\n|\t\t\t\t\t\t\t\t|\n");
                sleep(1);
                if(read_and_validate_decode_args(argv,&dncInfo) == e_success)  // Read and validate arguments function call.
                {
                    printf("|\tDECODING: Read and validate arguments were successed\t|\n");
                    if(do_decoding(&dncInfo) == e_success)
                    {
                        printf("|\t\e\033[5m--------DECODING is Done successfully--------\033[m\t\t|\n"); // Prints the message, When decoding is over.  

                        printf("+---------------------------------------------------------------+\n");
                        // exit(0);

                    }

                }
                else
                {
                    printf("|\tDECODING: Read and validate arguments were Failed\t|\n");  // Prints the message, When decoding is fails.
                }
            }
            else
            {
                printf("\033[91mInvalid Option\nPlease pass...\nFor Encoding: ./a.out -e beautiful.bmp secret.txt stego.bmp\nFor Decoding: ./a.out -d stego.bmp decode.txt\033[0m\n");   // Prints the error message.
            }
        }
        else
        {
            printf("\033[91m+---------------------------------------------------------------+\033[0m\n");
            printf("\033[91m|Invalid number of arguments\t\t\t\t\t|\n|Please pass...\t\t\t\t\t\t\t|\n|For Encoding: ./a.out -e beautiful.bmp secret.txt stego.bmp\t|\n|For Decoding: ./a.out -d stego.bmp decode.txt\t\t\t|\033[0m\n");   //Prints the error message.
            printf("\033[91m+---------------------------------------------------------------+\033[0m\n");

        }
    }
    else
    {
        printf("\033[91m+---------------------------------------------------------------+\033[0m\n");
        printf("\033[91m|Invalid number of arguments\t\t\t\t\t|\n|Please pass...\t\t\t\t\t\t\t|\n|For Encoding: ./a.out -e beautiful.bmp secret.txt stego.bmp\t|\n|For Decoding: ./a.out -d stego.bmp decode.txt\t\t\t|\033[0m\n");   //Prints the error message.
        printf("\033[91m+---------------------------------------------------------------+\033[0m\n");
        return e_failure;
    }
    return 0;
}

/*******************************************************************************************************************************/
