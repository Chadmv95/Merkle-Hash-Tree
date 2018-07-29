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

// struct node* buildTree()
// {
//   struct node* root = newNode("");
//   struct node* lChild = newNode("");
//   struct node* rChild = newNode("");
//   struct node* llc = newNode("");
//   struct node* lrc = newNode("");
//   struct node* rlc = newNode("");
//   struct node* rrc = newNode("");

//   lChild->left = llc;
//   lChild->right = lrc;
//   rChild->left = rlc;
//   rChild->right = rrc;
//   root->left = lChild;
//   root->right = rChild;

//   return(root);
// }

insert(char *hash, struct node *prevNode)
{
  struct node *node = malloc(sizeof(struct node));
  node->hash_value = hash;
  prevNode->next = node;
  node->prev = prevNode;
  node->next = NULL;
  node->parent = NULL;

  return (node);
}

computeParentHash(struct node *n1, struct node *prevUncle)
{
  struct node *n2; 
  if (n1->next == NULL && n1->prev == NULL)
    return n1->hash_value;


  if (n1->next == NULL)
  {
    n2 = newNode('\0');
  }
  else
  {
    n2 = n1->next;
  }

  char *combinedHash = strcat(n1->hash_value, n2->hash_value);
  char *newHash = string2md5(combinedHash, 32);
  struct node *parent = malloc(sizeof(struct node));
  parent->hash_value = newHash;
  parent->prev = prevUncle;
  prevUncle->next = parent;

    if(prevUncle == NULL){
    parent->fp = parent;
    }
    else {
      parent->fp = prevUncle->fp;
    }

  if(n2->hash_value == '\0' || n2->next == NULL){
    computeParentHash(n1->fp, NULL);
  }
  computeParentHash(n2->next, parent);
}