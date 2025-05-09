// Implementati o functie prin care sa verificati ca un binary tree este binary search tree.
// (pentru fiecare nod, valorile din subarborele stang sunt mai mici decat valoarea nodului, 
// iar valorile din subarborele drept sunt mai mari)

#include "tree.h"

int isBST(Node *node, int min, int max)
{
    if (node == NULL) 
    {
        return 1;
    }

    if (node->value < min || node->value > max) 
    {
        return 0;
    }

    return isBST(node->leftChild, min, node->value - 1) && 
           isBST(node->rightChild, node->value + 1, max);
}

int checkBST(Node *root)
{
    return isBST(root, INT_MIN, INT_MAX);
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
    postOrderTraversal(root);
    printf("\n");

    if (checkBST(root)) 
    {
        printf("Arborele este un binary search tree\n");
    } 
    else 
    {
        printf("Arborele nu este un binary search tree\n");
    }

    freeTree(root);

    return 0;
}