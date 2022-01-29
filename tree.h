#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef TREE_H
#define TREE H 
/*
Struct Node :
Represent the node of the a n-tree
- elt : the element of a node, it can be anything (char, int, bool, struct...)
- id : id of the node (Int)
- child : adress of a the child's current node (Node*)
- sibling : adresse of the sibling's current node (Node*)
*/
typedef struct Node{
    void* elt;
    int id;
    struct Node* child;
    struct Node* sibling;
} Node;

/*
Representation of a n-tree
Struct Tree :
- root : tree's root (Node*)
*/
typedef struct {
    Node *root;
    int nbNode;
} Tree;
/*
Return a new Tree with the root initialized with NULL
@param elt : element of the root node
*/
Tree* createTree(void* elt);

/*
Return a new created node
@param t : adress of tree
       elt : element of the node
*/
Node* createNode(Tree *t, void *elt);
/*
Return true if the node is empty else return false
(Here we are checking if a node is NULL because of the implementation...)
@param t : adress of a tree
*/
bool isTreeEmpty(Tree *t);

/*
Return the node searched
@param t : adress of a tree
       nodeId : id of the searched node
*/
Node* searchNode(Tree *t, int nodeId);

/*
Find the max ID in the tree
@param t : adress of a tree
*/
int findMaxId(Tree *t, int currentMax);

/*
Add the new child of a node
Return the tree with added child.
@param n : adress of the parent node
       newChild : adress of the new child.   
*/
Tree* addChild(Tree *t, int parentNodeId, Node *newChild);

/*
Add the new sibling of a node
Return the tree with added sibling.
@param n : adress of the node
       newSibling : adress of the new sibling.   
*/
Tree* addSibling(Tree *t, int siblingNodeId, Node *newSibling);

/*
Free every node.
@param t : the tree to desallocate

We suppose that the parameter t exist and is allocate.
*/

void destroyNodes(Tree *t);

#endif