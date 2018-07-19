#ifndef Node.h
#define Node.h

struct node;
struct node *root;

void destroy_tree( struct node* );

insert( int, struct node** );

struct node *search( int, struct node* );


#endif // Node
