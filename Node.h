#ifndef Node.h
#define Node.h
#define HASH_LENGTH 32

struct node
{
  char *hash_value;
  struct node *next;
  struct node *prev;
  struct node *parent;

  struct node *fp;
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
