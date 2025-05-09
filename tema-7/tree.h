#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

typedef struct node
{
    int value;
    struct node *leftChild;
    struct node *rightChild;
} Node;

void insertNode(Node **root, int value);
int getHeight(Node *node);
void freeTree(Node *node);
void preOrderTraversal(Node *node);
void inOrderTraversal(Node *node);
void postOrderTraversal(Node *node);

#endif