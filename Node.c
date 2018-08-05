#include "Node.h"
#include <string.h>

struct node *newNode(char *hash)
{
  struct node *node = malloc(sizeof(struct node));
  node->hash_value = hash;
  node->next = NULL;
  node->parent = NULL;

  return (node);
}

struct node* insert(char *hash, struct node *prevNode)
{
    struct node *node = malloc(sizeof(struct node));
    node->hash_value = hash;
    prevNode->next = node; //segmentation fault here
    node->prev = prevNode;
    node->next = NULL;
    node->parent = NULL;

    return (node);
}

void computeParentHash(struct node *n1, struct node *prevUncle)
{
    struct node *n2;
    struct node* firstParent;

    if (n1->next == NULL && n1->prev == NULL){ //fails here on new layer
        printf("\n============Top Hash============\n%s\n", n1->hash_value);
        printf("================================");

        printf("\n\nEnter 0 to exit: ");
        int exitInt;
        scanf("%d",&exitInt);
        exit(0);

        return 0;
    }


    if (n1->next == NULL)
    {
        n2 = newNode("");
    }
    else
    {
        n2 = n1->next;
    }

//    printf("n1->hash_value: %s\n", n1->hash_value);
//    printf("n2->hash_value: %s\n", n2->hash_value);

    char *combinedHash = strcat(n1->hash_value, n2->hash_value);
    char *newHash = str2md5(combinedHash, strlen(combinedHash));

    struct node *parent = malloc(sizeof(struct node));
    parent->hash_value = newHash;
    parent->next = NULL;
    parent->prev = NULL;
    //parent->prev = prevUncle; //added this to the else statement
                                //also added to if with null setter

    if(prevUncle == NULL)
    {
        parent->prev = NULL;
        parent->next = NULL;
        parent->fp = parent;

//        printf("parent->fp->next: %s\n", parent->fp->next);
//        printf("parent->fp->prev: %s\n", parent->fp->prev);
    }
    else
    {
//        printf("prevUncle->hash_value: %s\n", prevUncle->hash_value);
//        printf("prevUncle->fp->hash: %s\n", prevUncle->fp->hash_value);
        prevUncle->next = parent;
        parent->prev = prevUncle;
        parent->fp = prevUncle->fp;
    }
    if(n2->hash_value == '\0' || n2->next == NULL)
    {
//        printf("2parent->fp->next: %s\n", parent->fp->next);
//        printf("2parent->fp->prev: %s\n", parent->fp->prev);

        return computeParentHash(parent->fp, NULL);
    }
    return computeParentHash(n2->next, parent);
}
