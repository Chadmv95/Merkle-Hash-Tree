#include <stdio.h>
#include <stdlib.h>
#include "Node.h"
#include "md5.h"
#include <dirent.h>

//function prototypes
char* str2md5(const char*, int );
char* readFile(char *filename);

int main(int argc, char **argv)
{

    long unsigned int num_files = 0;

    DIR *d;
    struct dirent *dir;
    char file_dir[16] = "./files/";

    struct node* prev = NULL;
    struct node* fn = NULL;

    d = opendir(file_dir);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if(strcmp(dir->d_name, ".") && strcmp(dir->d_name, "..")){
                //printf("%s\n", dir->d_name); //print to the console
                //get the hash from the file contents
                char *file_name = dir->d_name;
                char *file_content = readFile(file_name);
                size_t file_size = strlen(file_content);
                char *file_hash = str2md5(file_content, file_size);

                if(prev == NULL){
                    prev = newNode(file_hash);
                    fn = prev;
                } else {
                    prev = insert(file_hash, prev);
                }

                num_files++;
//                free(file_content);
//                free(file_hash);
            }
        }

        closedir(d);
    }

    printf("Number of files hashed: %d\n", num_files);

    computeParentHash(fn, NULL);

    return 0;
}

char* readFile(char *filename)
{
   char *buffer = NULL;
   int string_size, read_size;
   FILE *handler = fopen(filename, "r");

   if (handler)
   {
       // Seek the last byte of the file
       fseek(handler, 0, SEEK_END);
       // Offset from the first to the last byte, or in other words, filesize
       string_size = ftell(handler);
       // go back to the start of the file
       rewind(handler);

       // Allocate a string that can hold it all
       buffer = (char*) malloc(sizeof(char) * (string_size + 1) );

       // Read it all in one operation
       read_size = fread(buffer, sizeof(char), string_size, handler);

       // fread doesn't set it so put a \0 in the last position
       // and buffer is now officially a string
       buffer[string_size] = '\0';

       if (string_size != read_size)
       {
           // Something went wrong, throw away the memory and set
           // the buffer to NULL
           free(buffer);
           buffer = NULL;
       }

       //close the file.
       fclose(handler);
    }



    return buffer;
}

/*
this helper function was found online, url to forum has since been lost
*/
char *str2md5(const char *str, int length) {

    //printf("Input: %s\n", str);
    int n;
    MD5_CTX c;
    unsigned char digest[16];
    char *out = (char*)malloc(32);

    MD5_Init(&c);

    while (length > 0) {
        if (length > 512) {
            MD5_Update(&c, str, 512);
        } else {
            MD5_Update(&c, str, length);
        }
        length -= 512;
        str += 512;
    }

    MD5_Final(digest, &c);

    for (n = 0; n < 16; ++n) {
        //changed 32 to 33 and something worked
        snprintf(&(out[n*2]), 32+1, "%02x", (unsigned int)digest[n]);
    }

    //printf("Input Hashed: %s\n", out);
    return out;
}
