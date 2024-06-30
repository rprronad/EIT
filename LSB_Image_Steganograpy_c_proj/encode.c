/*
Name        : RAVIKUMAR RONAD
Date        : 17-FEB-2023
Project Name: LSB(Least Significant Bit)-Steganography
Description : Steganography is the art of hiding the fact that communication is taking place, by hiding information in other 
              information. Many different carrier file formats can be used, but digital images are the most popular because of
              their frequency on the internet. For hiding secret information in images, there exists a large variety of
              steganography techniques some are more complex than others and all of them have respective strong and weak points. 
*/

/*---------------------------SYSTEM & USER DEFINED HEADER FILE NAMES----------------------------------------------------------*/
#include <stdio.h>
#include <unistd.h>
#include "string.h"
#include "encode.h"        
#include "types.h"
#include "common.h"

/* Function Definitions */
/* Get image size
 * Input: Image file ptr
 * Output: width * height * bytes per pixel (3 in our case)
 * Description: In BMP Image, width is stored in offset 18,
 * and height after that. size is 4 bytes
 */
/*---------------------------FUNCTION DEFINITION TO GET IMAGE SIZE-------------------------------------------------------------*/
uint get_image_size_for_bmp(FILE *fptr_image) 
{
    uint width, height; 
    fseek(fptr_image, 18, SEEK_SET);                                // Seek to 18th byte.

    fread(&width, sizeof(int), 1, fptr_image);                      // Read the width (an int).
    printf("|\t\t  \033[96mWidth  = %u\t\t\t\t\t\033[0m|\n", width);

    fread(&height, sizeof(int), 1, fptr_image);                     // Read the height (an int).
    printf("|\t\t  \033[96mHeight = %u\t\t\t\t\t\033[0m|\n", height);

    return width * height * 3;                                      // Return image capacity.
}

/* 
 * Get File pointers for i/p and o/p files
 * Inputs: Src Image file, Secret file and
 * Stego Image file
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file errors
 */

/*----------------------------FUNCTION DEFINITION TO OPEN FILES----------------------------------------------------------------*/
Status open_files(EncodeInfo *encInfo)
{
    encInfo -> fptr_src_image = fopen(encInfo -> src_image_fname, "r");     // Src Image file.

    if (encInfo -> fptr_src_image == NULL)                                  // Do Error handling.
    {
        perror("|\tfopen");
        fprintf(stderr,"|\t\033[91mError!.Unable to open file \"%s\"\t\t\033[0m|\n", encInfo -> src_image_fname);

        return e_failure;
    }


    encInfo -> fptr_secret = fopen(encInfo -> secret_fname, "r");           // Secret file.

    if (encInfo -> fptr_secret == NULL)                                     // Do Error handling.
    {
        perror("|\tfopen");
        fprintf(stderr, "|\t\033[91mError!.Unable to open file \"%s\"\t\t\t\033[0m|\n", encInfo -> secret_fname);

        return e_failure;
    }

    encInfo -> fptr_stego_image = fopen(encInfo -> stego_image_fname, "w"); // Stego Image file.

    if (encInfo -> fptr_stego_image == NULL)                                // Do Error handling.
    {
        perror("|\tfopen");
        fprintf(stderr, "|\t\033[91mError!.Unable to open file \"%s\"\t\t\t\033[0m|\n", encInfo -> stego_image_fname);

        return e_failure;
    }

    return e_success;                                                       // No failure return e_success.
}
/*-----------------------FUNCTION DEFINITION TO READ & VALIDATE,ENCODE PART AGRGUMENTS----------------------------------------*/ 
Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo)
{
    if(argv[2] != NULL && strstr(argv[2], ".bmp"))                          // Checking Argument-2 is "bmp file" or not.
    {
        encInfo -> src_image_fname = argv[2];
    }
    else
    {
        return e_failure;                                                   // Return e_failure, When bmp file is present.
    }
    if(argv[3] != NULL && strchr(argv[3], '.'))                             // Checking Argument-3 is "txt file" or not.
    {
        encInfo -> secret_fname = argv[3];
        strcpy(encInfo -> extn_secret_file, strchr(argv[3], '.'));          // Finds the last occurence of (.)
    }
    else
    {
        return e_failure;                                                   // Return e_failure, When txt file is not present.
    }
    if(argv[4] == NULL)                                                     // If condition for Argument-4 is NULL then assign it as a "stego image".
    {
        encInfo -> stego_image_fname = "stego.bmp";
    }
    else
    {
        if(strstr(argv[4], ".bmp"))                                          // Check it's an "bmp file" or not.
        {
            encInfo -> stego_image_fname = argv[4];
        }
        else
        {
            return e_failure;                                               //Return e_failure, When stego.bmp file is not present.
        }
    }
    return e_success;                                                       //Return e_success, When stego.bmp file is present.
}

/*-------------------------FUNCTION DEFINITION TO CHECK CAPACITY---------------------------------------------------------------*/
Status check_capacity(EncodeInfo *encInfo)
{
    encInfo -> image_capacity = get_image_size_for_bmp(encInfo -> fptr_src_image); //Storing image size into structure member.
    encInfo -> size_secret_file = get_file_size(encInfo -> fptr_secret);           //Sroeing file size into structure member.

    if(encInfo -> image_capacity > (54 + 2 + 4 + 4 + 4 + (encInfo -> size_secret_file)) * 8)  // Checking the if condition whether image capacity is greater than encoded size or not.
    {
        return e_success;
    }
    return e_failure;
}

/*-------------------------FUNCTION DEFINITION TO GET FILE SIZE------------==--------------------------------------------------*/
Status get_file_size(FILE *fptr)
{
    fseek(fptr, 0, SEEK_END);                   // Seek 0th Byte at the end
    return ftell(fptr);                                                                                    
}

/*-------------------------FUNCTION DEFINITION FOR COPYING THE BMP HEADER------------------------------------------------------*/
Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image)		  
{
    char buffer[54];						    // Character type variable "buffer" array with 54 Bytes size declaration. 		   
    fseek(fptr_src_image, 0, SEEK_SET);	        // The function fseek for Go to the begining.
    fread(&buffer, 54, 1, fptr_src_image);	    // Read the data from Source Image 1Byte by 1 Byte upto 54 Bytes (Usage: hd beautiful.bmp.				   	 
    fwrite(&buffer, 54, 1, fptr_dest_image);	// Write the data into Destination Image 1 Byte by 1 Byte (Usage: hd beautiful.bmp.			           
    return e_success;					        // Read & Write is Done then return e_success.
}

/*-------------------------FUNCTION DEFINITION FOR ENCODE DATA TO IMAGE--------------------------------------------------------*/
Status encode_data_to_image(char *data, int size, FILE *fptr_src_image, FILE *fptr_stego_image)
{
    char buffer[8];	                                    // Character type variable "buffer" array with 8 Bytes size declaration.							 
    int i;                                              // Interger type variable declaration.
    for (i = 0; i < size; i++)                          // Run the loop till size.
    {
        fread(&buffer, 8, 1, fptr_src_image);	        // Read the 1 Bytes from source image.				 
        encode_byte_to_lsb(data[i], buffer);		    // Function calling for encode_byte_to_lsb.			  
        fwrite(&buffer, 8, 1, fptr_stego_image);        // Write the 1 Byte in stego image.			 		  
    }
}

/*-------------------------FUNCTION DEFINITION FOR ENCODE BYTE TO LSB---------------------------------------------------------*/
Status encode_byte_to_lsb(char data, char *image_buffer)  			  
{
    int i;									                                   // Intger type variable delcaration.
    for(i = 0; i < 8; i++)						                               // Run the loop till 8.
    {
        image_buffer[i] = (image_buffer[i] & 0xFE) | ((data & (1 << i)) >> i);         
    }
}

/*-------------------------FUNCTION DEFINITION FOR ENCODE MAGIC STRING--------------------------------------------------------*/
Status encode_magic_string(char *magic_string, EncodeInfo *encInfo)         	
{
    encode_data_to_image(magic_string, strlen(magic_string), encInfo -> fptr_src_image, encInfo -> fptr_stego_image);  // Function call encode data image. 
    return e_success;
}

/*-------------------------FUNCTION DEFINITION FOR ENCODE SIZE---------------------------------------------------------------*/
Status encode_extension_size(int size, FILE *fptr_src_image, FILE *fptr_stego_image)
{
    char buffer[32];
    fread(buffer, 32, 1, fptr_src_image);                                    // File read 
    encode_size_to_lsb(buffer, size);                                        // Function call encode size to lsb.
    //printf("|\033[92m\tExtension size  = %d\t\t\t\t\t\033[0m|\n",size);    // Prints Extension size.
    fwrite(buffer, 32, 1, fptr_stego_image);
    return e_success;
}

/*-------------------------FUNCTION DEFINITION FOR ENCODE SIZE TO LSB--------------------------------------------------------*/
Status encode_size_to_lsb(char *image_buffer, int data)
{
    int i;									
    for(i = 0; i < 32; i++)	                                                // Run loop for 32 times					
    {
        image_buffer[i] = (image_buffer[i] & 0xFE) | ((data &(1<<i)) >> i); // Encode size to lsb.       
    }
    return e_success;
}

/*-------------------------FUNCTION DEFINITION FOR ENCODE FILE EXTENSION-------------------------------------------------------*/
Status encode_secret_file_extn(char *file_extn, EncodeInfo *encInfo) 
{
    encode_data_to_image(file_extn, strlen(file_extn ), encInfo -> fptr_src_image, encInfo -> fptr_stego_image);   // Function call encode data to image.
    return e_success;
}

/*-------------------------FUNCTION DEFINITION FOR SECRET FILE DATA------------------------------------------------------------*/
Status encode_secret_file_size(long file_size, EncodeInfo *encInfo) 	
{
    char buffer[32];                                                                // Character type array variable declaration.
    fread(buffer, 32, 1, encInfo -> fptr_src_image);                                // File read.
    encode_size_to_lsb(buffer, file_size);                                          // Function call encode size to lsb.
    //printf("|\033[92m\tSecret file size  = %ld\t\t\t\t\t\033[0m|\n",file_size);   // Prints file size.
    fwrite(buffer, 32, 1, encInfo -> fptr_stego_image);
    return e_success;
}

/*-------------------------FUNCTION DEFINITION FOR ENCODING THE SECRET FILE DATA-----------------------------------------------*/
Status encode_secret_file_data(EncodeInfo *encInfo)
{
    fseek(encInfo -> fptr_secret, 0, SEEK_SET);                             // Seek to 0th Byte.
    char buffer[encInfo -> size_secret_file];                               // Character type variable: buffer array.
    fread(buffer, encInfo -> size_secret_file, 1, encInfo -> fptr_secret);  // File read.
    encode_data_to_image(buffer, encInfo -> size_secret_file, encInfo -> fptr_src_image, encInfo -> fptr_stego_image);    // Function call encode data to image.
    return e_success;
}


/*-------------------------FUNCTION DEFINITION FOR COPY REMAINING DATA---------------------------------------------------------*/
Status copy_remaining_img_data(FILE *fptr_src_image, FILE *fptr_stego_image)
{
    char buffer;                                                        
    while(fread(&buffer, 1, 1, fptr_src_image) > 0) //  While loop copy the reamaing data in the src image to encoding stego image with help of File read and file write function. 
    {
        fwrite(&buffer, 1, 1, fptr_stego_image);
    }
    return e_success;

}

/*-------------------------FUNCTION DEFINITION FOR DO ENCODING----------------------------------------------------------------*/ 
Status do_encoding(EncodeInfo *encInfo) 
{
    if(open_files(encInfo) == e_success)  // Function call & Check the condition for openfiles. 
    {
        sleep(1);
        printf("|\t\033[32mINFO:---->Files are opened sucessfully.\t\t\t\033[0m|\n");
        if(check_capacity(encInfo) == e_success)  // Function call & check the condition for check capacity.
        {
            sleep(1);
            printf("|\t\033[32mINFO:---->Check capacity is successfully.\t\t\033[0m|\n");
            if(copy_bmp_header(encInfo -> fptr_src_image, encInfo -> fptr_stego_image) == e_success)    // Function call & Check the condition for copy bmp header.
            {
                sleep(1);
                printf("|\t\033[32mINFO:---->Copy header is sucessfully.\t\t\t\033[0m|\n");
                if(encode_magic_string(MAGIC_STRING, encInfo) == e_success) // Function call & check the condition for magic string
                {
                    sleep(1);
                    printf("|\t\033[32mINFO:---->Magic string added sucessfully.\t\t\033[0m|\n");
                    if(encode_extension_size(strlen(strstr(encInfo -> secret_fname, ".")),encInfo -> fptr_src_image, encInfo -> fptr_stego_image) == e_success) // Function call & check the condition for encode extension size.
                    {
                        sleep(1);
                        printf("|\t\033[32mINFO:---->Extension size is sucessfully.\t\t\033[0m|\n");
                        if(encode_secret_file_extn(strstr(encInfo->secret_fname, "."),encInfo ) == e_success)   // Function call & check the condition for secret file extension.
                        {
                            sleep(1);
                            printf("|\t\033[32mINFO:---->Encoding extension is sucessfully.\t\t\033[0m|\n");
                            if(encode_secret_file_size(encInfo -> size_secret_file, encInfo) == e_success)  // Function call & check the condition for secret file size.
                            {
                                sleep(1);
                                printf("|\t\033[32mINFO:---->Encoding secret file size sucessfully.\t\033[0m|\n");
                                if(encode_secret_file_data(encInfo) == e_success)   // Function call & check the condition for secret file data.
                                {
                                    sleep(1);
                                    printf("|\t\033[32mINFO:---->Encoding secret file data sucessfully.\t\033[0m|\n");
                                    if(copy_remaining_img_data(encInfo -> fptr_src_image, encInfo -> fptr_stego_image) == e_success)  // Function call & check the condition for copy remaing data.
                                    {
                                        sleep(1);
                                        printf("|\t\033[32mINFO:---->Remaining image data is coiped sucessfully.\t\033[0m|\n"); // When if condition is fails, Prints Error msg in RED color.
                                    }
                                    else
                                    {
                                        printf("|\033[91m\tError!.Remaining image data is failed to coiped\t\t\033[0m|\n"); // When is condition is fails, Prints Error msg in RED color.
                                    }

                                }
                                else
                                {
                                    printf("|\033[91m\tError!.Encoding secret file data is failed...\t\t\033[0m|\n"); // When if condition is fails, Prints Error msg in RED color.
                                }

                            }
                            else
                            {
                                printf("|\033[91m\tError!.Encoding secret file size is failed...\t\t033[0m|\n"); // When if condition is fails, Prints Error msg in RED color.
                            }

                        }
                        else
                        {
                            printf("|\033[91m\tError!.Encoding extension is failed...\t\t\t\033[0m|\n"); // When if condition is fails, Prints Error msg in RED color.
                        }

                    }
                    else
                    {
                        printf("|\33[91m\tError!.Extension size is failed...\t\t\t\033[0m|\n");  // When if condition is fails, Prints Error msg in RED color.
                    }

                }
                else
                {
                    printf("|\033[91m\tError!.Adding of magic string is failed..\t\t\033[0m|\n"); // When if condition is fails, Prints Error msg.
                }

            }
            else
            {
                printf("|\033[91m\tError!.Copying of header file is failed..\t\t\033[0m|\n"); // When if condition is fails, Prints Error msg.
            }
        }
        else
        {
            printf("|\033[91m\ttError!.Checking capacity is failed..\t\t\t\033[0m|\n"); // When if condition is fails, Prints Error msg.
        }

    }
    else
    {
        printf("|\033[91m\tError!.Files are failes to open...\t\t\t\033[0m|\n|\033[91m\tCheck all operation once...\t\t\t\t\033[0m|\n");  // When if condition is fails, Prints Error msg.
        printf("+---------------------------------------------------------------+\n"); 
        return e_failure;                                                   // Return e_failure.
    }
    return e_success;                                                       // Return e_success.
}

/****************************************************GOTO test_encode.c file*************************************************************************************************************************************************************************************/
