/*
Name        : RAVIKUMAR RONAD
Date        : 17-FEB-2023
Project Name: LSB(Least Significant Bit)-Steganography
Description : Steganography is the art of hiding the fact that communication is taking place, by hiding information in other 
              information. Many different carrier file formats can be used, but digital images are the most popular because of 
              their frequency on the internet. For hiding secret information in images, there exists a large variety of
              steganography techniques some are more complex than others and all of them have respective strong and weak points. 
 */

/*-------------------------------SYSTEM & USER DEFINED HEADER FILES NAMES----------------------------------*/
#include <stdio.h>        
#include <string.h>
#include "decode.h"
#include "types.h"
#include "common.h"
#include <unistd.h>

/*---------------------------FUNCTION DEFINITION FOR READ & VALIDATE ARGUMENTS-----------------------------*/
Status read_and_validate_decode_args(char *argv[], DecodeInfo *dncinfo)  
{
    if(argv[2] != NULL && (strstr(argv[2], ".bmp")) != NULL)                   // Check Argument-2 is "bmp file" or not.
    {
        dncinfo -> stego_image_fname = argv[2];

        if(argv[3] == NULL)                                          // Check Argument-3 is NULL or not
        {
            strcpy(dncinfo -> secret_fname, "Output");               // If it's NULL then take file name as "output".
            printf("|\t\t\t\t%s\t\t\t\t|\n", dncinfo -> secret_fname);
        }
        else
        {
            strcpy(dncinfo -> secret_fname, strtok(argv[3], "."));   // Else check the file name. 
            printf("|\t\t\t\t%s\t\t\t\t|\n", dncinfo -> secret_fname);
        }
        return e_success;                                            // Return e_success.
    }
    else
    {
        return e_failure;                                            // Return e_failure.
    }
}

/*------------------------------FUNCTION DEFINITION TO OPEN FILES----------------------------------------------*/
Status d_open_files(DecodeInfo *dncinfo)             
{
    dncinfo -> fptr_stego_image = fopen(dncinfo -> stego_image_fname, "r");
    if(dncinfo -> fptr_stego_image == NULL)
    {
        perror("fopen");  
        fprintf(stderr, "Error: Unable to open file %s\n", dncinfo -> stego_image_fname);  //Prints standard error.
        return e_failure;
    }
    return e_success;
}

/*--------------FUNCTION DEFINITION TO DECODE SKIP HEADER FILES(54B same for both operation)--------------------*/
Status decode_skip_header(FILE *fptr_stego_image)       
{
    fseek(fptr_stego_image, 54, SEEK_SET);      //Seek 54th Byte at the position.

    return e_success;                           // Return e_success.
}

/*------------------------FUNCTION DEFINITION TO DECODING MAGIC STRING------------------------------------------*/
Status decode_magic_string(DecodeInfo *dncInfo)              
{
    char magic_str[2];                                                    //Character type variable declaration.
    if(decode_data_image(strlen(MAGIC_STRING), dncInfo -> fptr_stego_image, magic_str) == e_success)

        if(strcmp(magic_str, "#*") == 0)                                  // Comparing the magic string.
        {
            return e_success;                                             // If condition is true Return e_success.
        }
        else
        {
            return e_failure;                                             // If condition is false Return e_failure. 
        }
}

/*------------------------FUNCTION DEFINITION TO DECODE DATA TO IMAGE-------------------------------------------*/
Status decode_data_image (int size,FILE *fptr_stego_image,char *magic_str)
{

    char buffer[8];                                                       // Character type variable is "buffer" array with size 8 declaration. 
    int i;                                                                // Int i declaration.
    for(i = 0; i < size; i++)                                             // Run the loop till size.
    {
        fread(buffer, 8, 1, fptr_stego_image);                            // File reading from fptr_stego_image.
        magic_str[i] = decode_byte_to_lsb(buffer);                        // Byte to LSB storing into magic string.
    }
    magic_str[size] = '\0';                                               // At the end, null character is stored in magic stric. 
    return e_success;                                                     // Return e_success.
}

/*------------------------FUNCTION DEFINITION TO DECODE BYTE TO LSB----------------------------------------------*/
Status decode_byte_to_lsb(char *image_buffer)     
{
    char ch = 0x00;                                                       // Character tyep variable is ch with value 0x00 assigned. 
    int i;                                                                // Int i declaration.
    for(i = 7; i >= 0; i--)                                               // Run loop till 0 from 7bit.
    {
        ch = ch | ((image_buffer[i] & 0x01) << i);                        // Decodeing bits using bitwise OR and left shift with based on index values.
    }
    return ch;                                                            // Return ch.
}

/*------------------------FUNCTION DEFINITION TO DECODE FILE EXTENSION SIZE-------------------------------------*/
Status decode_file_extension_size(DecodeInfo *dncInfo)      
{
    char buffer[32];                                                      // Character variable buffer with 32 size declaration.  
    fread(buffer, 32, 1, dncInfo->fptr_stego_image);                      // File read from fptr stego image.
    dncInfo -> extension_size = decode_size_to_lsb(buffer);               // Storing buffer values into structure member.
    return e_success;                                                     // Return e_success.
} 
/*------------------------FUNCTION DEFINITION TO DECODE SIZE TO LSB---------------------------------------------*/
Status decode_size_to_lsb(char *buffer)            
{
    int size = 0;                                                         // Int variable size declaration with value is 0.
    int i;                                                                // Int i variable declaration.
    for(i = 0; i < 32; i++)                                               // Run loop till 32 times.
    {
        size = size | ((buffer[i] & 0x01) << i);                          // To get size of extension using bit OR, AND & <<.
    }
    return size;                                                          // Return size
}
/*------------------------FUNCTION DEFINITION TO DECODE FILE EXTENSION------------------------------------------*/
Status decode_file_extension(DecodeInfo *dncInfo)
{
    char *arr;                                                            // Character variable declration.

    char magic_str[4];                                                    // Character array variable declaration.
    int size = dncInfo -> extension_size * 8;                             // Integer variable size declaration with assigning size * 8
    //printf("|\t\033[92mExtension size = %ld\t\t\t\t\t\033[0m|\n", dncInfo -> extension_size); // Prints Extension file size
    decode_data_image(dncInfo -> extension_size, dncInfo -> fptr_stego_image, magic_str);  
    //printf("|\t\033[92mFile Extn = %s\t\t\t\t\t\t\033[0m|\n",magic_str); // Prints File Extn (.h or .txt)
    strcat(dncInfo->secret_fname,magic_str);
    //printf("|\t\033[92mOutput file name = %s\t\t\t\t\033[0m|\n", dncInfo -> secret_fname); //Prints Output file name (Output.h or Output.txt)
    dncInfo -> sec_fname = fopen(dncInfo -> secret_fname,"w");

    return e_success;                                                     // Return e_success.
}  

/*------------------------FUNCTION DEFINITION TO DECODE FILE SIZE-----------------------------------------------*/
Status decode_secret_file_size(DecodeInfo  *dncInfo)
{
    char buffer[32];                                                      // Character variable declaration buffer with 32 size.
    fread(buffer, 32, 1, dncInfo -> fptr_stego_image);                    // File read from structure member.
    dncInfo -> size_secret_file = decode_size_to_lsb(buffer);             // Decoding the buffer data into structure.
    // printf("\n\t|sec_size = %ld\t\t\t\t|\n", dncInfo -> size_secret_file);

    return e_success;                                                     // Return e_success.
}
/*------------------------FUNCTION DEFINITION TO DECODING SECRET FILE DATA--------------------------------------*/
Status decode_secret_file_data(DecodeInfo *dncInfo)	
{

    int size = dncInfo -> size_secret_file;                               // Intger variable declaration.
    //printf("sec buff size = %d\n",size);
    char buffer[size];                                                    // Char variable buffer declaration.
    decode_data_image(dncInfo -> size_secret_file, dncInfo -> fptr_stego_image,buffer); // Decode data.
    fwrite(buffer, size, 1, dncInfo -> sec_fname);
    return e_success;                                                     // Return e_success.
}

/*------------------------FUNCTION DEFINITION FOR TRANSFER DATA TO FILE-----------------------------------------*/
/*
   Status transfer_data_to_file(DecodeInfo *dncInfo)    
   {
   int i = 0;                                                            // Integer variable declaration.
   if(dncInfo -> secret_fname != NULL)                                   // Check secret file 
   {
   strcat(dncInfo ->secret_fname ,dncInfo ->extn_secret_file);       // String concat..
   char *ptr = dncInfo ->buffer;                                     // Size is assigning into ptr
   FILE *fptr;                                                       // File pointer.
   fptr = fopen(dncInfo -> secret_fname, "w+");                      // Open file with Write mode 
   fseek(fptr, 0, SEEK_SET);                                         // Seek 0th Byte at the start.
   fwrite(ptr, dncInfo -> size_secret_file, 1, fptr);                // File write.
   }
   return e_success;                                                     // Return e_success.
   }
 */

/*----------------FUNCTION DEFINITION FOR DO DECODING-----------------------------------------------------------*/
Status do_decoding(DecodeInfo *dncInfo)
{
    if(d_open_files(dncInfo) == e_success)                                           // Function call & check the open files status.
    {
        sleep(1);
        printf("|\033[32m\tINFO:---->Files are opened sucessfully\t\t\t\033[0m|\n");
        if(decode_skip_header(dncInfo->fptr_stego_image)==e_success)                 // Function call & check the skip headder status.
        {
            sleep(1);
            printf("|\033[32m\tINFO:---->Header skipped successfull\t\t\t\033[0m|\n");
            if(decode_magic_string(dncInfo) == e_success )                           // Function call & check the magic string status.
            {
                sleep(1);
                printf("|\033[32m\tINFO:---->Magic string sucesfully\t\t\t\033[0m|\n");
                if(decode_file_extension_size(dncInfo) == e_success )                // Function call & check the file extension size status.
                {
                    sleep(1);
                    printf("|\033[32m\tINFO:---->File extension size sucessfully\t\t\033[0m|\n");
                    if(decode_file_extension(dncInfo) == e_success)                  // Function call & check the file extension status.
                    {
                        sleep(1);
                        printf("|\033[32m\tINFO:---->File extension sucessfully\t\t\t\033[0m|\n");
                        if(decode_secret_file_size(dncInfo) == e_success)            // Function call & check the secret file size status.
                        {
                            sleep(1);
                            printf("|\033[32m\tINFO:---->Secret file size sucessfully\t\t\t\033[0m|\n");
                            if(decode_secret_file_data(dncInfo) == e_success)        // Function call and check the secret file data status.
                            {
                                sleep(1);
                                printf("|\t\033[32mINFO:---->Secret file data sucessfully\t\t\t\033[0m|\n");
                                /*
                                   if(transfer_data_to_file(dncInfo) == e_success)      // Function call and check the data transfer to a file status.
                                   {
                                   sleep(1);
                                   printf("|\t\033[32mINFO:---->Transfering data sucesfully\t\t\t\033[0m|\n"); // Prints the message for Origal data.
                                   return e_success;
                                   }

                                   else
                                   {
                                   printf("|\033[91m\tError!.Transfering data operation failed..\t\t\033[0m|\n"); // Prints Error msg in RED color.

                                   }
                                 */

                            }
                            else
                            {
                                printf("|\033[91m\tError!.Secret file data operation is failed..\t\t\033[0m|\n"); // Prints Error msg in RED color.
                            }
                        }
                        else
                        {
                            printf("|\033[91m\tError!.Secret file size operation is failed..\t\t\033[0m|\n"); // Prints Error msg in RED color.
                        }
                    }
                    else
                    {
                        printf("|\033[91m\tError!.File extension operation is failed..\t\t\033[0m|\n"); // Prints Error msg in RED color.
                    }

                }
                else
                {
                    printf("|\033[91m\tError!.File extension size operation is failed..\t\033[0m|\n"); // Prints Error msg in RED color.
                }
            }
            else
            {
                printf("|\033[91m\tError!.Magic string operation is failed..\t\t\033[0m|\n"); // Prints Errror msg in RED color.
            } 

        }
        else
        {
            printf("|\033[91m\tError!.Header data operation is failed..\t\t\033[0m|\n"); // Prints Error msg in RED color.
        }
    }
    else
    {
        printf("|\033[91m\tError!.File are failes to open\t\t\t\t\033[0m|\n");  // Prints Error msg in RED color.
        return e_failure;   // Return e_failure.
    }
    return e_success; //Return e_success.

}

/*************************************************GOTO test encode.c file****************************************************************************************************************************************************************************************/




















