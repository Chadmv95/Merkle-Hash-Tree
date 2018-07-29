#include "Node.h"
#include <string.h>

struct node* newNode(char *hash) {
  struct node* node = malloc(sizeof(struct node));
  node->key_value = 0;
  node->hash_value = hash;
  node->left = NULL;
  node->right = NULL;

  return(node);
}

struct node* buildTree()
{
  struct node* root = newNode("");
  struct node* lChild = newNode("");
  struct node* rChild = newNode("");
  struct node* llc = newNode("");
  struct node* lrc = newNode("");
  struct node* rlc = newNode("");
  struct node* rrc = newNode("");

  lChild->left = llc;
  lChild->right = lrc;
  rChild->left = rlc;
  rChild->right = rrc;
  root->left = lChild;
  root->right = rChild;

  return(root);
}

void destroy_tree(struct node *leaf)
{
  if( leaf != 0 )
  {
      destroy_tree(leaf->left);
      destroy_tree(leaf->right);
      free( leaf );
  }
}

int size(struct node* node) {
  if (node == NULL) {
    return(0);
  } else {
    return(size(node->left) + 1 + size(node->right));
  }
}

int maxDepth(struct node* node) {
  if (node==NULL) {
    return(0);
  }
  else {

    int lDepth = maxDepth(node->left);
    int rDepth = maxDepth(node->right);

    if (lDepth > rDepth) return(lDepth+1);
    else return(rDepth+1);
  }
}

void printTree(struct node* node) {
  if (node == NULL) return;
  printTree(node->left);
  printf("%d ", node->key_value);
  printTree(node->right);
}

insert(int key, struct node **leaf)
{
    if( *leaf == 0 )
    {
        *leaf = (struct node*) malloc( sizeof( struct node ) );
        (*leaf)->key_value = key;
        /* initialize the children to null */
        (*leaf)->left = 0;
        (*leaf)->right = 0;
    }
    else if(key < (*leaf)->key_value)
    {
        insert( key, &(*leaf)->left );
    }
    else if(key > (*leaf)->key_value)
    {
        insert( key, &(*leaf)->right );
    }
}

struct node *search(int key, struct node *leaf)
{
  if( leaf != 0 )
  {
      if(key==leaf->key_value)
      {
          return leaf;
      }
      else if(key<leaf->key_value)
      {
          return search(key, leaf->left);
      }
      else
      {
          return search(key, leaf->right);
      }
  }
  else return 0;
}
