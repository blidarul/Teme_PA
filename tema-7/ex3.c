// Implementati o functie care sa gaseasca cel mai apropiat stramos comun al doua noduri dintr-un arbore binar.

#include "tree.h"

Node *findCommonAncestor(Node *root, int value1, int value2)
{
    if (root == NULL) 
    {
        return NULL;
    }

    if (root->value == value1 || root->value == value2) 
    {
        return root;
    }

    Node *leftAncestor = findCommonAncestor(root->leftChild, value1, value2);
    Node *rightAncestor = findCommonAncestor(root->rightChild, value1, value2);

    if (leftAncestor && rightAncestor) 
    {
        return root;
    }

    return leftAncestor ? leftAncestor : rightAncestor;
}

int main()
{
    Node *root = NULL;
    insertNode(&root, 20);
    insertNode(&root, 10);
    insertNode(&root, 30);
    insertNode(&root, 5);
    insertNode(&root, 15);
    insertNode(&root, 25);
    insertNode(&root, 35);

    /*
                    20
                   /  \
                  10   30
                 / \   / \
                5  15 25 35
    */

    printf("Arborele este: ");
    inOrderTraversal(root);
    printf("\n");

    Node *ancestor = findCommonAncestor(root, 5, 15);

    if (ancestor != NULL) 
    {
        printf("Stramosul comun al nodurilor 5 si 15 este: %d\n", ancestor->value);
    } 
    else 
    {
        printf("Nu s-a gasit stramosul comun al nodurilor 5 si 15.\n");
    }

    freeTree(root);

    return 0;
}