// Implementati o functie prin care sa verificati ca un nod are "verisori"
// (doua noduri ale unui arbore binar sunt veri daca au aceeasi adancime cu parinti diferiti.)

#include "tree.h"

int getLevel(Node *node, int value, int level)
{
    if (node == NULL) 
    {
        return 0;
    }

    if (node->value == value) 
    {
        return level;
    }

    int downLevel = getLevel(node->leftChild, value, level + 1);
    if (downLevel != 0) 
    {
        return downLevel;
    }

    return getLevel(node->rightChild, value, level + 1);
}

Node *findParent(Node *root, int value)
{
    if (root == NULL) 
    {
        return NULL;
    }

    if ((root->leftChild != NULL && root->leftChild->value == value) ||
        (root->rightChild != NULL && root->rightChild->value == value)) 
    {
        return root;
    }

    Node *leftResult = findParent(root->leftChild, value);
    if (leftResult != NULL) 
    {
        return leftResult;
    }

    return findParent(root->rightChild, value);
}

int checkCousins(Node *root, int value1, int value2)
{
    if (root == NULL) 
    {
        return 0;
    }

    int level1 = getLevel(root, value1, 1);
    int level2 = getLevel(root, value2, 1);

    Node *parent1 = findParent(root, value1);
    Node *parent2 = findParent(root, value2);

    if (level1 == level2 && level1 != 0 && parent1 != parent2) 
    {
        return 1;
    }
    return 0;
}

int main()
{
    Node *root = NULL;
    insertNode(&root, 10);
    insertNode(&root, 5);
    insertNode(&root, 15);
    insertNode(&root, 3);
    insertNode(&root, 7);
    insertNode(&root, 12);
    insertNode(&root, 18);

    /*
                10
               /  \
              5    15
             / \   / \
            3   7 12  18
    */

    printf("Arborele este: ");
    inOrderTraversal(root);
    printf("\n");

    if (checkCousins(root, 3, 7)) 
    {
        printf("Nodurile 3 si 7 sunt verisori\n");
    } 
    else 
    {
        printf("Nodurile 3 si 7 nu sunt verisori\n");
    }

    if (checkCousins(root, 3, 12)) 
    {
        printf("Nodurile 3 si 12 sunt verisori\n");
    } 
    else 
    {
        printf("Nodurile 3 si 12 nu sunt verisori\n");
    }

    freeTree(root);

    return 0;
}