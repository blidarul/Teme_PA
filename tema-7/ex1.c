// Implementati o functie ca sa verificati ca un binary tree este echilibrat
// (doi subarbori ai oricarui nod nu au o diferenta de nivel mai mare de 1)

#include "tree.h"

int isBalanced(Node *root)
{
    if (root == NULL) 
    {
        return 1;
    }

    int leftHeight = getHeight(root->leftChild);
    int rightHeight = getHeight(root->rightChild);

    if (abs(leftHeight - rightHeight) > 1) 
    {
        return 0;
    }

    return isBalanced(root->leftChild) && isBalanced(root->rightChild);
}

int main()
{
    Node *root = NULL;

    insertNode(&root, 7);
    insertNode(&root, 3);
    insertNode(&root, 10);
    insertNode(&root, 1);
    insertNode(&root, 14);

    /*
                7
               / \
              3   10
             /     \
            1      14
    */

    printf("Arborele este: ");
    inOrderTraversal(root);
    printf("\n");

    if (isBalanced(root)) 
    {
        printf("Arborele este echilibrat\n");
    } 
    else 
    {
        printf("Arborele nu este echilibrat\n");
    }

    freeTree(root);

    return 0;
}