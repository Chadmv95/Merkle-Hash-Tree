#ifndef Node.h
#define Node.h
#define HASH_LENGTH 32

struct node
{
  int key_value;
  char *hash_value;
  struct node *left;
  struct node *right;
};

struct node* newNode( char *hash );

struct node* buildTree();

void destroy_tree( struct node* );

insert( int, struct node** );

struct node *search( int, struct node* );

int size(struct node* node);

void printTree(struct node* node);

int maxDepth(struct node* node);


#endif // Node
