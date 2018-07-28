#include <stdio.h>
#include <stdlib.h>
#include "Node.h"
#include "md5.h"
#include <string.h>

char* str2md5(const char*, int );
char* readFile(char *filename);

int main(int argc, char **argv)
{
    //prints the md5 hash of the string file
    char file[64] = "Hello World\0";
    char *output = str2md5(file, strlen(file));
    printf("%s\n", output);
    free(output);

    //read from files and get hash based on that
    char *file3 = readFile("test1.txt");
    char *file4 = readFile("test2.txt");

    struct node* root = buildTree();
    root->left->hash_value = str2md5(file3, strlen(file3));
    root->right->hash_value = str2md5(file4, strlen(file4));
    char *combined1 = strcat(root->left->hash_value, root->right->hash_value);
    root->hash_value = str2md5(combined1, strlen(combined1));

    printf("Top Hash: %s\n", root->hash_value);

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

       // Always remember to close the file.
       fclose(handler);
    }

    return buffer;
}

/*
this helper function was found online, url to forum has since been lost
*/
char *str2md5(const char *str, int length) {
    int n;
    MD5_CTX c;
    unsigned char digest[16];
    char *out = (char*)malloc(33);

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
        snprintf(&(out[n*2]), 16*2, "%02x", (unsigned int)digest[n]);
    }

    return out;
}
