#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

void insertNode(Node **root, int value)
{
    Node *tempNode = (Node *)malloc(sizeof(Node));
    Node *current;
    Node *parent;

    tempNode->value = value;
    tempNode->leftChild = NULL;
    tempNode->rightChild = NULL;

    // Arborele este gol
    if (*root == NULL) 
    {
        *root = tempNode;
    } 
    else 
    {
        current = *root;
        parent = NULL;
        while (1) 
        {
            parent = current;

            // Subarbore stanga
            if (value < parent->value) 
            {
                current = current->leftChild;

                // Insert la stanga
                if (current == NULL) 
                {
                    parent->leftChild = tempNode;
                    return;
                }
            } 
            // Subarbore dreapta
            else 
            {
                current = current->rightChild;

                // Insert la dreapta
                if (current == NULL) 
                {
                    parent->rightChild = tempNode;
                    return;
                }
            }
        }
    }
}

int getHeight(Node *node)
{
    if (node == NULL) 
    {
        return 0;
    }

    int leftHeight = getHeight(node->leftChild);
    int rightHeight = getHeight(node->rightChild);

    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

void freeTree(Node *node)
{
    if (node == NULL) 
    {
        return;
    }

    freeTree(node->leftChild);
    freeTree(node->rightChild);
    free(node);
}

void preOrderTraversal(Node *node)
{
    if (node == NULL) 
    {
        return;
    }

    printf("%d ", node->value);
    preOrderTraversal(node->leftChild);
    preOrderTraversal(node->rightChild);
}

void inOrderTraversal(Node *node)
{
    if (node == NULL) 
    {
        return;
    }

    inOrderTraversal(node->leftChild);
    printf("%d ", node->value);
    inOrderTraversal(node->rightChild);
}

void postOrderTraversal(Node *node)
{
    if (node == NULL) 
    {
        return;
    }

    postOrderTraversal(node->leftChild);
    postOrderTraversal(node->rightChild);
    printf("%d ", node->value);
}