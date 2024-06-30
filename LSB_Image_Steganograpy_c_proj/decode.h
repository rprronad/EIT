#ifndef DECODE_H
#define DECODE_H                                


#include "types.h"  //Contains user defined types

/*
 * Struture to store information required for
 * decoding secret file to stego image
 */

#define SECRET_BUF_SIZE 1       //MACRO's                      
#define MAX_IMAGE_SIZE (MAX_SECRET_BUF_SIZE * 8)
#define MAX_FILE_SUFFIX 4

typedef struct _DecodeInfo
{
    /* Secret data output file info */
    char secret_fname[10];
    FILE *fptr_secret;
    char extn_secret_file[MAX_FILE_SUFFIX];
    char secret_data[SECRET_BUF_SIZE ];
    char *secret_data1;
    long size_secret_file;
    long extension_size;
    FILE *sec_fname;

    /* Stego image info */
    char buffer[100];
    char *stego_image_fname;
    FILE *fptr_stego_image;

    char *dest_image_fname;
    FILE *fptr_dest_image; 

} DecodeInfo;

/* Decoding function prototype */

/* Function declaration for read and validate */
Status read_and_validate_decode_args(char *argv[], DecodeInfo *dncInfo);

/* Perform the encoding */
Status do_decoding(DecodeInfo *dncInfo);

/* Get File pointers for i/p and o/p files */
Status d_open_files(DecodeInfo *dncInfo);

/* Decode skip headder */
Status decode_skip_header(FILE *fptr_stego_image);

/* Transfer data to file */
Status transfer_data_to_file(DecodeInfo *dncInfo);

/* Store Magic String */
Status decode_magic_string(DecodeInfo *dncInfo);

/* Decode data image */
Status decode_data_image (int size,FILE *fptr_stego_image,char *magic_str);

/* Decode a byte into LSB of fo image data array */
Status decode_byte_to_lsb(char *image_buffer);

/* Decode file extension size */
Status decode_file_extension_size(DecodeInfo *dncInfo);				
/* Decode size to lsb */
Status decode_size_to_lsb (char *buffer);

/* Decode file extension */
Status decode_file_extension(DecodeInfo *dncInfo);				
/* Decode secret secre file size */
Status decode_secret_file_size(DecodeInfo *dncInfo);				
/* Decode secret file data */
Status decode_secret_file_data(DecodeInfo *dncInfo);				
#endif

