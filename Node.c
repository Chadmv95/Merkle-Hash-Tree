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

        printf("parent->fp->next: %s\n", parent->fp->next);
        printf("parent->fp->prev: %s\n", parent->fp->prev);
    }
    else
    {
        printf("prevUncle->hash_value: %s\n", prevUncle->hash_value);
        printf("prevUncle->fp->hash: %s\n", prevUncle->fp->hash_value);
        prevUncle->next = parent;
        parent->prev = prevUncle;
        parent->fp = prevUncle->fp;
    }
    if(n2->hash_value == '\0' || n2->next == NULL)
    {
        printf("2parent->fp->next: %s\n", parent->fp->next);
        printf("2parent->fp->prev: %s\n", parent->fp->prev);

        return computeParentHash(parent->fp, NULL);
    }
    return computeParentHash(n2->next, parent);
}








//#include "Node.h"
//#include <string.h>
//
//struct node* newNode(char *hash) {
//  struct node* node = malloc(sizeof(struct node));
//  node->key_value = 0;
//  node->hash_value = hash;
//  node->left = NULL;
//  node->right = NULL;
//
//  return(node);
//}
//
//struct node* buildTree()
//{
//  struct node* root = newNode("");
//  struct node* lChild = newNode("");
//  struct node* rChild = newNode("");
//  struct node* llc = newNode("");
//  struct node* lrc = newNode("");
//  struct node* rlc = newNode("");
//  struct node* rrc = newNode("");
//
//  lChild->left = llc;
//  lChild->right = lrc;
//  rChild->left = rlc;
//  rChild->right = rrc;
//  root->left = lChild;
//  root->right = rChild;
//
//  return(root);
//}
//
//void destroy_tree(struct node *leaf)
//{
//  if( leaf != 0 )
//  {
//      destroy_tree(leaf->left);
//      destroy_tree(leaf->right);
//      free( leaf );
//  }
//}
//
//int size(struct node* node) {
//  if (node == NULL) {
//    return(0);
//  } else {
//    return(size(node->left) + 1 + size(node->right));
//  }
//}
//
//int maxDepth(struct node* node) {
//  if (node==NULL) {
//    return(0);
//  }
//  else {
//
//    int lDepth = maxDepth(node->left);
//    int rDepth = maxDepth(node->right);
//
//    if (lDepth > rDepth) return(lDepth+1);
//    else return(rDepth+1);
//  }
//}
//
//void printTree(struct node* node) {
//  if (node == NULL) return;
//  printTree(node->left);
//  printf("%d ", node->key_value);
//  printTree(node->right);
//}
//
//unsigned int getLeafCount(struct node* node)
//{
//  if(node == NULL)
//    return 0;
//  if(node->left == NULL && node->right==NULL)
//    return 1;
//  else
//    return getLeafCount(node->left) + getLeafCount(node->right);
//}
//
//insert(int key, struct node **leaf)
//{
//    if( *leaf == 0 )
//    {
//        *leaf = (struct node*) malloc( sizeof( struct node ) );
//        (*leaf)->key_value = key;
//        /* initialize the children to null */
//        (*leaf)->left = 0;
//        (*leaf)->right = 0;
//    }
//    else if(key < (*leaf)->key_value)
//    {
//        insert( key, &(*leaf)->left );
//    }
//    else if(key > (*leaf)->key_value)
//    {
//        insert( key, &(*leaf)->right );
//    }
//}
//
//struct node *search(int key, struct node *leaf)
//{
//  if( leaf != 0 )
//  {
//      if(key==leaf->key_value)
//      {
//          return leaf;
//      }
//      else if(key<leaf->key_value)
//      {
//          return search(key, leaf->left);
//      }
//      else
//      {
//          return search(key, leaf->right);
//      }
//  }
//  else return 0;
//}
