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
    DIR *d;
    struct dirent *dir;
    char file_dir[16] = "./files/";
    char *files;
    char *file_hash;
    d = opendir(file_dir);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if(strcmp(dir->d_name, ".") && strcmp(dir->d_name, "..")){
                printf("%s\n", dir->d_name);
            }
        }
        closedir(d);
    }

    //prints the md5 hash of the string file
    //this is a proof of concept for the hashing
    char file[64] = "Hello World\0";
    char *output = str2md5(file, strlen(file));
    printf("%s\n", output);
    free(output);

    //read from files and get hash based on that
    char *file1 = readFile("./files/test1.txt");
    char *file2 = readFile("./files/test2.txt");
    char *file3 = readFile("./files/test3.txt");
    char *file4 = readFile("./files/test4.txt");
    char *file5 = readFile("./files/test5.txt");
    char *file6 = readFile("./files/test6.txt");
    char *file7 = readFile("./files/test7.txt");
    char *file8 = readFile("./files/test8.txt");

    //builds the tree which is only 3 nodes
    struct node* root = buildTree();
    root->left->left->hash_value = str2md5(file1, strlen(file1));
    root->left->right->hash_value = str2md5(file2, strlen(file2));
    root->right->left->hash_value = str2md5(file3, strlen(file3));
    root->right->right->hash_value = str2md5(file4, strlen(file4));

    free(file1);
    free(file2);
    free(file3);
    free(file4);

    char *comb = strcat(root->left->left->hash_value, root->left->right->hash_value);
    root->left->hash_value = str2md5(comb, strlen(comb));

    comb = strcat(root->right->left->hash_value, root->right->right->hash_value);
    root->right->hash_value = str2md5(comb, strlen(comb));

    comb = strcat(root->left->hash_value, root->right->hash_value);
    root->hash_value = str2md5(comb, strlen(comb));

    printf("Top Hash: %s\n", root->hash_value);

    //computes hash values for the base level based on the file contents
    root->left->hash_value = str2md5(file3, strlen(file3));
    root->right->hash_value = str2md5(file4, strlen(file4));
    //free file variables, they are taking up memory and are not used anymore
    free(file3);
    free(file4);

    //combines the hash strings and computes top hash
    char *combined1 = strcat(root->left->hash_value, root->right->hash_value);
    root->hash_value = str2md5(combined1, strlen(combined1));

    //print top hash to console
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

       //close the file.
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
        //changed 32 to 33 and something worked
        snprintf(&(out[n*2]), 32*8+1, "%02x", (unsigned int)digest[n]);
    }

    return out;
}
