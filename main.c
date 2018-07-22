#include <stdio.h>
#include <stdlib.h>
#include "Node.h"
#include "md5.h"

char *str2md5(const char*, int );

int main(int argc, char **argv)
{
    //prints the md5 hash of the string file
    char file[64] = "Hello World\0";
    char *output = str2md5(file, strlen(file));
    printf("%s\n", output);
    free(output);

    //struct node* root = buildTree();

    //the rest of the main proves that computing the top hash works
    char file1[64] = "file contents\0";
    char file2[64] = "different contents\0";

    char *hash1 = str2md5(file1, strlen(file1));
    char *hash2 = str2md5(file2, strlen(file2));

    char *combined = strcat(hash1, hash2);

    char *tophash = str2md5(combined, strlen(combined));

    printf("Top Hash: %s\n", tophash);

    //TODO: make a binary tree and compute top hash
    struct node* root = buildTree();


    return 0;
}

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
