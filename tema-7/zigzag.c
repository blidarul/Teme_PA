// O cale ZigZag într-un arbore binar este definită astfel: 
// alegi un nod oarecare din arbore și o direcție (fie spre stânga, fie spre dreapta). 
// Dacă direcția aleasă este spre dreapta, te deplasezi către copilul din dreapta al nodului curent; 
// în caz contrar, mergi către copilul din stânga. 
// Apoi, schimbi direcția – dacă ai mers spre dreapta, urmează un pas spre stânga, și invers. 
// Repeți acest proces până când nu mai poți continua deplasarea în arbore.
// Lungimea unei căi ZigZag este definită ca numărul de noduri vizitate minus unu 
// (de exemplu, un nod singur are o lungime ZigZag de 0).
// Scrie o funcție care returnează cea mai lungă cale ZigZag care există în arbore.

#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEFT 0
#define RIGHT 1

void calculateZigZag(Node *node, int direction, int length, int *maxLength, Node **startNode, 
    int *startDirection, Node *origNode)
{
    if (node == NULL)
    {
        return;
    }

    if (length > *maxLength)
    {
        *maxLength = length;
        *startNode = origNode;
        *startDirection = direction;
    }

    if (direction == LEFT)
    {
        calculateZigZag(node->leftChild, RIGHT, length + 1, maxLength, startNode, 
            startDirection, origNode);
    }
    else
    {
        calculateZigZag(node->rightChild, LEFT, length + 1, maxLength, startNode, 
            startDirection, origNode);
    }
    

    if (node->leftChild != NULL)
        calculateZigZag(node->leftChild, RIGHT, 1, maxLength, startNode, startDirection, node);
    if (node->rightChild != NULL)
        calculateZigZag(node->rightChild, LEFT, 1, maxLength, startNode, startDirection, node);
}

void preOrderTraversal2(Node *node, int *maxLength, Node **startNode, int *startDirection)
{
    if (node == NULL)
    {
        return;
    }

    calculateZigZag(node, LEFT, 0, maxLength, startNode, startDirection, node);
    calculateZigZag(node, RIGHT, 0, maxLength, startNode, startDirection, node);

    preOrderTraversal2(node->leftChild, maxLength, startNode, startDirection);
    preOrderTraversal2(node->rightChild, maxLength, startNode, startDirection);
}

void printPath(Node *startNode, int startDirection, int maxLength)
{
    Node *current = startNode;
    int direction = startDirection;

    printf("Calea este: ");
    printf("%d ", current->value);
    
    for (int i = 0; i < maxLength; i++)
    {
        if (direction == LEFT)
        {
            current = current->leftChild;
            direction = RIGHT;
        }
        else
        {
            current = current->rightChild;
            direction = LEFT;
        }
        
        if (current == NULL) break;
        printf("%d ", current->value);
    }
    printf("\n");
}

int main()
{
    Node *root = NULL;
    Node *root2 = NULL;

    insertNode(&root, 10);
    insertNode(&root, 5);
    insertNode(&root, 15);
    insertNode(&root, 3);
    insertNode(&root, 7);
    insertNode(&root, 12);
    insertNode(&root, 18);
    insertNode(&root, 6);
    insertNode(&root, 13);
    insertNode(&root, 17);

    /*
                 10
               /     \
              5       15
             / \    /    \
            3   7  12    18
               /    \   / 
              6     13 17        
    */

    int maxLength = 0;
    Node *startNode = root;
    int startDirection = -1;

    preOrderTraversal2(root, &maxLength, &startNode, &startDirection);
    printf("Cea mai lunga cale ZigZag: %d\n", maxLength);
    printPath(startNode, startDirection, maxLength);
    printf("\n");

    insertNode(&root2, 10);
    insertNode(&root2, 5);
    insertNode(&root2, 15);
    insertNode(&root2, 18);
    insertNode(&root2, 17);
    insertNode(&root2, 20);
    insertNode(&root2, 25);
    insertNode(&root2, 22);
    insertNode(&root2, 24);
    insertNode(&root2, 23);

    /*
                     10
                   /    \
                  5      15
                          \
                          18
                         /   \
                        17   20
                               \
                               25
                              / 
                             22
                               \
                                24
                               /
                             23
    */

    int maxLength2 = 0;
    Node *startNode2 = root2;
    int startDirection2 = -1;

    preOrderTraversal2(root2, &maxLength2, &startNode2, &startDirection2);
    printf("Cea mai lunga cale ZigZag in arborele 2: %d\n", maxLength2);
    printPath(startNode2, startDirection2, maxLength2);
    printf("\n");

    freeTree(root);
    freeTree(root2);

    return 0;
}