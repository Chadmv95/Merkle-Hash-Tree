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

/*
*   This function will insert a new node into the tree with the given hash string
*
*   @return Returns the node inserted
*/
struct node* insert(char *hash, struct node *prevNode)
{
    struct node *node = malloc(sizeof(struct node));
    node->hash_value = hash;
    prevNode->next = node;
    node->prev = prevNode;
    node->next = NULL;
    node->parent = NULL;

    return (node);
}

/*
*   This recursive function uses a custom algorithm to compute top hash
*/
void computeParentHash(struct node *n1, struct node *prevUncle)
{
    struct node *n2;
    struct node* firstParent;

    //if this is the last node, print the top hash
    if (n1->next == NULL && n1->prev == NULL){
        printf("\n============Top Hash============\n%s\n", n1->hash_value);
        printf("================================");
        printf("\n\nEnter 0 to exit: ");
        int exitInt;
        scanf("%d",&exitInt);
        //the user must enter 0 to exit, or they can close the window
        exit(0);

        return 0;
    }

    //if the next node is null, make a new one with an empty string hash
    if (n1->next == NULL)
    {
        n2 = newNode("");
    }
    else
    {
        //'normal' case, set n2 to the next node for n1
        n2 = n1->next;
    }

    //combine the hashes and then recompute for the new hash of the 2
    char *combinedHash = strcat(n1->hash_value, n2->hash_value);
    char *newHash = str2md5(combinedHash, strlen(combinedHash));

    struct node *parent = malloc(sizeof(struct node));
    parent->hash_value = newHash;
    parent->next = NULL;
    parent->prev = NULL;

    //this is for when a new layer needs to occur
    if(prevUncle == NULL)
    {
        parent->prev = NULL;
        parent->next = NULL;
        parent->fp = parent;
    } else {
        prevUncle->next = parent;
        parent->prev = prevUncle;
        parent->fp = prevUncle->fp;
    }

    //this is for when a new layer needs to occur
    if(n2->hash_value == '\0' || n2->next == NULL)
    {
        return computeParentHash(parent->fp, NULL);
    }

    //this is the base case, this will happen most of the time
    return computeParentHash(n2->next, parent);
}
