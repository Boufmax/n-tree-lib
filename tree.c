#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "tree.h"

Tree* createTree(void* rootElt){
    Tree *t = malloc(sizeof(Tree));
    t->nbNode = 0;
    t->root = createNode(t, rootElt);
    t->nbNode++;
    return t;
}
int findMaxId(Tree *t, int currentMax) {
    if(isTreeEmpty(t)) {
        return currentMax;
    }
    Node *n = t->root; 
    Tree child = {n->child};
    Tree sibling = {n->sibling};
    if(n->id <= currentMax) {
        if(isTreeEmpty(&child) && isTreeEmpty(&sibling)) {
            return currentMax;
        }

        if(!isTreeEmpty(&child) && isTreeEmpty(&sibling)) {
            currentMax = child.root->id;
            return findMaxId(&child, currentMax);
        }

        if(isTreeEmpty(&child) && !isTreeEmpty(&sibling)) {
            currentMax = sibling.root->id;
            return findMaxId(&sibling, currentMax);
        }

        if(!isTreeEmpty(&child) && !isTreeEmpty(&sibling)) {
            int maxChild = findMaxId(&child, child.root->id);
            int maxSibling = findMaxId(&sibling, sibling.root->id);
            if(maxChild > maxSibling) {
                return maxChild;
            } else {
                return maxSibling;
            }
        }
    }
    return currentMax;
}
Node* createNode(Tree *t, void* elt) {
    Node* n = malloc(sizeof(Node));
    n->child = NULL;
    n->sibling = NULL;
    n->elt = elt;
    n->id = t->nbNode == 0 ? 1 : findMaxId(t, 1)+1;

    return n;
}

bool isTreeEmpty(Tree* t) {
    if(t->root == NULL) {
        return true;
    } else {
        return false;
    }
}

Node* searchNode(Tree *t, int nodeId) {
    if(isTreeEmpty(t)) {
        return NULL;
    }
    Node *n = t->root;
    Tree child = {n->child};
    Tree sibling = {n->sibling};
    if(n->id != nodeId) {
        if(isTreeEmpty(&child) && isTreeEmpty(&sibling)) {
            return NULL;
        }
        if(!isTreeEmpty(&child) && isTreeEmpty(&sibling)) {
            Node *node = searchNode(&child, nodeId);
            return node;
        }

        if(isTreeEmpty(&child) && !isTreeEmpty(&sibling)) {
            Node *node = searchNode(&sibling, nodeId);
            return node;
        }
        if(isTreeEmpty(&child) && isTreeEmpty(&sibling)) {

            Node *nC = searchNode(&child, nodeId);
            Node *nS = searchNode(&sibling, nodeId);
            if(nC == NULL && nS == NULL) {
                return NULL;
            }

            if(nC != NULL && nS == NULL) {
                return nC;
            }

            if(nC == NULL && nS != NULL) {
                return nS;
            }
            //nC and nS can't be both different of NULL because id is unique
        }
    }
    return n;
}

Tree* addChild(Tree *t, int parentNodeId, Node *newChild) {
    if(isTreeEmpty(t) || newChild == NULL) {
        return NULL;
    }
    Node* parentNode = searchNode(t, parentNodeId);
    if(parentNode == NULL) {
        return NULL;
    }
    parentNode->child = newChild;
    t->nbNode++;
    return t;
}

Tree* addSibling(Tree *t, int siblingNodeId, Node *newSibling) {
    if(isTreeEmpty(t) || newSibling == NULL) {
        return NULL;
    }
    Node* siblingNode = searchNode(t, siblingNodeId);
    if(siblingNode == NULL){
        return NULL;
    }
    siblingNode->sibling = newSibling;
    t->nbNode++;
    return t;
}

void destroyNodes(Tree *t) {
    Node *n = t->root;
    Tree child = {n->child};
    Tree sibling = {n->sibling};
    if(!isTreeEmpty(&child) && isTreeEmpty(&sibling)) {
        destroyNodes(&child);
        free(t->root->child);
    }

    if(isTreeEmpty(&child) && !isTreeEmpty(&sibling)) {
        destroyNodes(&sibling);
        free(t->root->sibling);
    }

    if(!isTreeEmpty(&child) && !isTreeEmpty(&sibling)) {
        destroyNodes(&child);
        destroyNodes(&sibling);
        free(t->root->child);
        free(t->root->sibling);
    }
}

int main(int argc, const char *argv[]) {
    Tree *t = createTree((void*)6);
    t = addChild(t, 1, createNode(t, (void*)'c'));
    t = addSibling(t, t->root->child->id, createNode(t, (void *)false));
    printf("Sibling id : %d\n", t->root->child->sibling->id);
    printf("Sibling element : %s\n", *((bool *)&t->root->child->sibling->elt) ? "true" : "false");

    t = addSibling(t, 3, createNode(t, (void*)"Salut"));
    printf("Sibling of sibling id : %d\n", searchNode(t, 3)->sibling->id);
    printf("sibling of sibling element : %s\n", (char *)(searchNode(t, 3)->sibling->elt));
    destroyNodes(t);
    free(t->root);
    free(t);
    return EXIT_SUCCESS;
}
