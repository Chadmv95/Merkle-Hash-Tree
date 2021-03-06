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

void computeParentHash(struct node *n1, struct node *prevUncle);

struct node* newNode( char *hash );

struct node* buildTree();

void destroy_tree( struct node* );

struct node* insert(char *hash, struct node *prevNode);

struct node *search( int, struct node* );

int size(struct node* node);

void printTree(struct node* node);

int maxDepth(struct node* node);


#endif // Node









//#ifndef Node.h
//#define Node.h
//#define HASH_LENGTH 32
//
//struct node
//{
//  int key_value;
//  char *hash_value;
//  struct node *left;
//  struct node *right;
//};
//
//struct node* newNode( char *hash );
//
//struct node* buildTree();
//
//void destroy_tree( struct node* );
//
//insert( int, struct node** );
//
//struct node *search( int, struct node* );
//
//int size(struct node* node);
//
//void printTree(struct node* node);
//
//int maxDepth(struct node* node);
//
//
//#endif // Node
