# EITviva questions with answers related to a steganography project:
--------------------------------------------------------------
1. What is steganography? How is it different from cryptography?
Ans: 
Steganography is the practice of hiding a secret message within another message or file, while cryptography is the practice of transforming a message into a secure format using a cipher or key. The main difference is that steganography focuses on concealing the existence of a message, while cryptography focuses on securing the content of a message.

2. How did you choose the algorithm and tools for your steganography project?
Ans: 
We chose the LSB (Least Significant Bit) algorithm for our steganography project, as it is a simple and effective way to hide data in images. We also used Python as the programming language, and the Pillow library for image manipulation.

3. Can you explain the basic steps involved in steganography, and how they are implemented in your project?
Ans: 
The basic steps in steganography are: selecting a carrier file, encoding the secret message into the carrier file, and sending or storing the modified carrier file. In our project, we first opened the carrier image file and read its pixel values. We then converted the secret message into binary format and embedded it in the LSB of the carrier image pixels. Finally, we saved the modified image file as the output.

4. How do you ensure the security and integrity of the hidden message in your steganography project?
Ans: 
We ensure the security and integrity of the hidden message by using encryption to protect the original message before embedding it in the carrier file, and by using error-correcting codes to detect and correct any changes or errors that may occur during transmission or storage.

5. How do you evaluate the performance and effectiveness of your steganography project? What metrics do you use?
Ans: 
We evaluate the performance and effectiveness of our steganography project by measuring the size of the carrier file and the size of the embedded message, the quality of the carrier image before and after encoding, and the time required to encode and decode the message. We use metrics such as PSNR (Peak Signal-to-Noise Ratio) and MSE (Mean Squared Error) to assess the quality of the image.

6. How can your steganography project be used in real-life scenarios? What are some potential applications?
Ans: 
Our steganography project can be used for covert communication, where two parties can exchange hidden messages in public images without arousing suspicion. It can also be used for digital watermarking, where an image or document can be marked with a unique identifier for copyright or authentication purposes.

7. How do you address the legal and ethical implications of steganography? What are some guidelines or regulations that apply?
Ans: 
We address the legal and ethical implications of steganography by ensuring that our project is used only for lawful and legitimate purposes, and by respecting the privacy and intellectual property rights of others. We are also aware that steganography can be misused for criminal or terrorist activities, and we take measures to prevent such misuse.

8. How do you see the future of steganography evolving? What are some new trends or challenges that you anticipate?
Ans: 
We see steganography evolving to include more advanced algorithms and techniques that can hide messages in a wider range of multimedia formats, such as audio, video, and 3D models. We also anticipate new challenges in detecting and preventing steganography, as it can be used for malicious purposes such as malware or espionage.

9. What are some possible attacks or vulnerabilities that can compromise the security of steganography? How do you mitigate them in your project?
Ans:
Some possible attacks or vulnerabilities in steganography include brute-force attacks, statistical attacks, and visual attacks. We mitigate these risks in our project by using encryption.

---------------------------------------------------------------------------
DECODE PART:
-> Steganography decoding is the process of extracting hidden or secret data from a steganographic file. Steganography is the practice of hiding data within another file, such as an image, audio, or video file, without arousing suspicion. This is done by making small modifications to the file that are imperceptible to human perception, but which can be detected by a computer.

-> To decode a steganographic file, the receiver needs to know the method used to hide the data in the file. For example, the data may have been hidden by modifying the least significant bits of the pixels in an image file. In this case, the receiver would need to know which bits were modified and how to extract the hidden data.

-> The decoding process typically involves the following steps:

1. Open the steganographic file and read the hidden data from it.

2. Remove any encryption or compression applied to the hidden data, if necessary.

3. Extract any metadata or header information that was added to the file during the encoding process, such as the file format, data size, or key information.

4. Reconstruct the original data by reversing the encoding process. This may involve manipulating the file to extract the hidden data, such as by changing the least significant bits of pixels in an image file.

5. Save the decoded data to a new file or use it as necessary.
The success of steganography decoding depends on the method used to hide the data and the quality of the steganographic file. In some cases, the hidden data may be undetectable or impossible to extract.
---------------------------------------------------------------------------
DECODE CODE WITH EXPLANATION:

#include <stdio.h>        
#include <string.h>
#include <unistd.h>

Explanation: Standard C libraries, Header file.
-> The stdio.h header file provides input and output functionality,
-> string.h provides string manipulation functions,
-> unistd.h provides access to POSIX(Portable Operating System Interface) operating system functions such as sleep() and usleep().

#include "decode.h"
#include "types.h"
#include "common.h"

Explanation: Local Header file.
->USER header files decode.h, types.h, and common.h likely contain function and structure definitions that are specific to the program's functionality.


READ & VALIDATE: 

Status read_and_validate_decode_args(char *argv[], DecodeInfo *dncinfo)  
{
    if(argv[2] != NULL && strstr(argv[2], ".bmp"))                   // Check Argument-2 is "bmp file" or not.
    {
        dncinfo -> stego_image_fname = argv[2];

        if(argv[3] == NULL)                                          // Check Argument-3 is NULL or not
        {
            strcpy(dncinfo -> secret_fname, "output");               // If it's NULL then take file name as "output".
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

Explanation: 
-> This function reads and validates the command-line arguments for decoding a secret file from a stego image. It takes two arguments: an array of command-line arguments and a pointer to a DecodeInfo structure.

-> The function first checks if the second argument is not NULL and if it ends with ".bmp" to confirm that it is a valid stego image file. If it is, the function sets the stego image filename in the DecodeInfo structure.

-> Then it checks if the third argument is NULL or not. If it is NULL, the function sets the secret file name to "output". If it is not NULL, the function uses the strtok function to extract the file name from the path and extension and sets it as the secret file name in the DecodeInfo structure.

-> If all the arguments are valid, the function returns e_success. If the second argument is not a valid stego image file, the function returns e_failure

OPEN FILE:
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

Explanation:
-> The d_open_files() function takes a pointer to a DecodeInfo structure as input, which contains the name of the stego image file to be opened for decoding. The function attempts to open the file with the given name in read mode using fopen() function and returns e_success if the file is successfully opened. If the file cannot be opened, the function returns e_failure after printing an error message to stderr using perror() and a custom error message to stderr using fprintf().

-> In summary, the function is responsible for opening the stego image file for decoding and checking if it has been opened successfully or not.


SKIP HEADER:
Status decode_skip_header(FILE *fptr_stego_image)       
{
    fseek(fptr_stego_image, 54, SEEK_SET);      //Seek 54th Byte at the position.

    return e_success;   // Return e_success.
}
Explanation:
-> This function skips the header of the steganographic image. The header of a bitmap image is typically 54 bytes long, so this function uses fseek() to set the file pointer to the 54th byte, which is where the image data begins.

-> The fseek() function sets the file position indicator for the stream pointed to by fptr_stego_image to the offset of 54 bytes from the beginning of the file, using the SEEK_SET argument to specify that the offset is relative to the beginning of the file.

-> The function returns e_success to indicate that the header has been skipped successfully.


MAGIC STRING
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
Explanation:
-> This function is used to decode the magic string from the stego image and validate if it matches the expected magic string.

-> It takes a pointer to a DecodeInfo struct as input, which contains information about the stego image file and the output file.

-> The function first declares a character array magic_str of size 2 to store the decoded magic string. It then calls decode_data_image() function with the length of the magic string and the file pointer to the stego image, to decode the magic string from the image. If the decoding is successful, it compares the decoded magic string with the expected magic string "#*". If the comparison is successful, it returns e_success, indicating that the magic string is valid. Otherwise, it returns e_failure.

-> Note that e_success and e_failure are constants defined in the types.h header file, and they are used to indicate the status of the operation performed by the function.

DATA IMAGE:
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
Explanation:
-> The function decode_data_image reads data from the fptr_stego_image file pointer and decodes it into the magic_str character array using the LSB decoding technique.

-> It takes three arguments:

-> size: an integer representing the size of the data to be read from the file and decoded.
fptr_stego_image: a pointer to the stego image file.
magic_str: a character array to store the decoded data.
The function reads data from the file in chunks of 8 bytes and calls the decode_byte_to_lsb function to decode the LSB bits of each byte. The decoded bits are then stored in the magic_str array. At the end of the loop, a null character is appended to the magic_str array to terminate the string.

-> The function returns e_success if it successfully decodes and stores the data into the magic_str array.

BYTE TO LSB:
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
Explanation:
-> The function decode_byte_to_lsb takes a pointer to a character array image_buffer and returns a single character that is the result of decoding the least significant bits (LSB) of each of the 8 bits in image_buffer.

-> The function does this by initializing a character ch to 0x00, and then iterating over the bits in image_buffer from bit 7 (most significant) to bit 0 (least significant). For each bit, the function performs a bitwise AND with 0x01 to extract the LSB, and then left-shifts the result by i bits (where i is the current bit position) before performing a bitwise OR with ch.

-> This way, the function builds up a character ch where the 8 bits are the LSBs of the corresponding bits in image_buffer. The resulting ch is returned by the function.


EXTENSION SIZE:
Status decode_file_extension_size(DecodeInfo *dncInfo)      
{
    char buffer[32];                                                      // Character variable buffer with 32 size declaration.  
    fread(buffer, 32, 1, dncInfo->fptr_stego_image);                      // File read from fptr stego image.
    dncInfo -> extension_size = decode_size_to_lsb(buffer);               // Storing buffer values into structure member.
    return e_success;                                                     // Return e_success.
} 
Explanation:
-> this function reads the next 32 bytes from the stego image file pointed to by dncInfo->fptr_stego_image, and decodes the file extension size from the LSBs of these bytes.

-> First, a character array buffer of size 32 is declared. Then, the function reads 32 bytes of data from the file pointed to by dncInfo->fptr_stego_image into buffer using the fread() function.

-> The function then calls the decode_size_to_lsb() function to decode the size of the file extension from the LSBs of the bytes in buffer. This value is stored in the extension_size member of the dncInfo structure.

-> Finally, the function returns e_success to indicate that it completed successfully.

SIZE TO LSB:
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
Explanation:
-> This function is used to decode the size of the hidden file's extension from the LSBs of the stego image. It takes a character array buffer which is assumed to contain the LSBs of the image file, and decodes the size by performing bitwise operations on the buffer. The size is then returned as an integer value.

-> The function works by initializing a variable size to 0, and then looping through the buffer 32 times (since the size is assumed to be 32 bits long). In each iteration of the loop, the least significant bit of the ith element of buffer is extracted using a bitwise AND operation with 0x01, and then left-shifted by i bits. The resulting value is then OR-ed with the size variable to accumulate the bits into a single integer value.

-> At the end of the loop, the accumulated size value is returned as the output of the function.



FILE EXTENSION:
Status decode_file_extension(DecodeInfo *dncInfo)
{
    char *arr;                                                            // Character variable declration.
    char magic_str[4];                                                    // Character array variable declaration.
    int size = dncInfo -> extension_size * 8;                             // Integer variable size declaration with assigning size * 8
    decode_data_image(dncInfo -> extension_size, dncInfo -> fptr_stego_image, magic_str); 
    strcpy(dncInfo -> extn_secret_file, magic_str);                       // Copying the magic string into structure member.
    return e_success;                                                     // Return e_success.
}  
Explanation:
-> The function decode_file_extension is used to decode the file extension from the steganographed image. The function first calculates the size of the extension by multiplying the extension_size member of the DecodeInfo structure by 8, since the extension is stored in 8-bit chunks.

-> Then the decode_data_image function is called to read the extension from the image file and store it in magic_str. The size of the extension is passed as the first argument, the file pointer to the steganographed image is passed as the second argument, and the buffer to store the extension is passed as the third argument.

-> Finally, the strcpy function is used to copy the extension from magic_str to the extn_secret_file member of the DecodeInfo structure. If successful, the function returns e_success.

SECRET FILE SIZE:
Status decode_secret_file_size(DecodeInfo  *dncInfo)
{
    char buffer[32];                                                      // Character variable declaration buffer with 32 size.
    fread(buffer, 32, 1, dncInfo -> fptr_stego_image);                    // File read from structure member.
    dncInfo -> size_secret_file = decode_size_to_lsb(buffer);             // Decoding the buffer data into structure.
    return e_success;                                                     // Return e_success.
}
Explanation:
-> The decode_secret_file_size function reads 32 bytes of data from the stego image file using the fread function and stores it in a character array called buffer. Then it uses the decode_size_to_lsb function to extract the size of the secret file from the LSBs of the buffer data and stores the size value in the size_secret_file member of the dncInfo structure. Finally, the function returns e_success to indicate that the operation was successful. This function is responsible for decoding and extracting the size of the secret file that was embedded in the stego image file.

SECRET FILE DATA:
Status decode_secret_file_data(DecodeInfo *dncInfo)	
{

    int size = dncInfo -> size_secret_file;                               // Intger variable declaration.
    char buffer[size];                                                    // Char variable buffer declaration.
    decode_data_image(dncInfo -> size_secret_file, dncInfo -> fptr_stego_image, dncInfo -> buffer); // Decode data.
    return e_success;                                                     // Return e_success.
}
Explanation:
-> data from the stego image. It takes a pointer to DecodeInfo structure as input which contains the necessary information required for decoding the secret file data.

-> The function first gets the size of the secret file data from the DecodeInfo structure and stores it in the integer variable size. It then declares a character array named buffer of size size.

-> The function then calls the decode_data_image function to decode the secret file data from the stego image into the buffer array. The decode_data_image function decodes the data bit by bit using the LSB technique and stores it in the buffer array.

TRANSFER DATA FILE:
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
Explanation:
-> This is a function called "transfer_data_to_file" that takes a pointer to a "DecodeInfo" struct as its input parameter. The function returns an "e_success" status code indicating that the operation was successful.

-> The function first checks whether the "secret_fname" field of the "DecodeInfo" struct is not NULL, which would indicate that a valid filename for the secret file has been provided. If the filename is valid, the function concatenates the "extn_secret_file" field of the struct to the end of the filename using the "strcat" function.

-> The function then assigns the address of the "buffer" field of the "DecodeInfo" struct to a pointer variable called "ptr". This buffer is assumed to contain the data to be written to the file.

-> The function then declares a FILE pointer variable called "fptr" and opens the file with the filename specified in the "secret_fname" field using the "fopen" function in write mode ("w+"). This will create a new file if the specified file does not already exist, or overwrite the file if it already exists.

-> The function then uses the "fseek" function to move the file pointer to the beginning of the file, and then writes the data from the "ptr" buffer to the file using the "fwrite" function. The "size_secret_file" field of the "DecodeInfo" struct specifies the number of bytes to write, and "1" is the number of elements to write at a time.

-> Finally, the function returns the "e_success" status code to indicate that the data transfer was successful.


DO DECODING:
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
                                if(transfer_data_to_file(dncInfo) == e_success)      // Function call and check the data transfer to a file status.
                                {
                                    sleep(1);
                                    printf("|\t\033[32mINFO:---->Transfering data sucesfully\t\t\t\033[0m|\n"); // Prints the message for Origal data.
                                }
                                else
                                {
                                    printf("|\033[91m\tError!.Transfering data operation failed..\t\t\033[0m|\n"); // Prints Error msg in RED color.
                                }

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

Explanation:
-> This is a C function called "do_decoding" which takes a pointer to a "DecodeInfo" struct as an argument. The function decodes a secret message from a steganographic image file using the information in the "DecodeInfo" struct.

-> The function first calls "d_open_files" function to open the necessary files and checks the return value to ensure that the files were opened successfully. If the files were opened successfully, the function goes through a series of decoding steps, each of which calls a specific function and checks the return value for success.

-> If all decoding steps are successful, the function calls "transfer_data_to_file" function to transfer the decoded data to a file, and if that is successful, it prints a success message. If any of the decoding steps or the data transfer fails, the function prints an error message in red color and returns e_failure.

-> The function uses sleep(1) function calls to introduce a 1-second delay between each step of the decoding process. This may be done to give the user time to read the output messages.

-> The function returns e_success if all decoding steps are successful, and e_failure otherwise.

**********************************END**************************************



