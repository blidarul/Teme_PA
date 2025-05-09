// Realizați un program prin care să puteți transforma un arbore într-un string
// și apoi să puteți transforma string-ul într-un arbore.

#include "tree.h"
#include <string.h>

#define SEPARATOR " "
#define NOD_INEXISTENT "-"

void appendNodesAtLevel(Node *root, int level, char *result, int *resultPos, int resultSize)
{
    if (root == NULL)
    {
        *resultPos += snprintf(result + *resultPos, (size_t)(resultSize - *resultPos), "%s%s",
                               NOD_INEXISTENT, SEPARATOR);
        return;
    }

    if (level == 0)
    {
        *resultPos += snprintf(result + *resultPos, (size_t)(resultSize - *resultPos), "%d%s",
                               root->value, SEPARATOR);
    }
    else if (level > 0)
    {
        appendNodesAtLevel(root->leftChild, level - 1, result, resultPos, resultSize);
        appendNodesAtLevel(root->rightChild, level - 1, result, resultPos, resultSize);
    }
}

char *treeToString(Node *root)
{
    if (root == NULL)
    {
        char *emptyResult = malloc(strlen(NOD_INEXISTENT) + 1);
        if (emptyResult == NULL)
            return NULL;
        strcpy(emptyResult, NOD_INEXISTENT);
        return emptyResult;
    }

    int height = getHeight(root);
    int maxNodes = (1 << height) - 1;


    char *result = (char *)malloc((size_t)maxNodes * 20);
    if (result == NULL)
        return NULL;

    result[0] = '\0';
    int resultPos = 0;
    int resultSize = maxNodes * 20;

    for (int level = 0; level < height; level++)
    {
        appendNodesAtLevel(root, level, result, &resultPos, resultSize);
    }

    if (resultPos > 0)
    {
        result[resultPos - 1] = '\0';
    }

    return result;
}

Node *stringToTree(char *str)
{
    if (str == NULL || strcmp(str, NOD_INEXISTENT) == 0)
        return NULL;
        
    char *strCopy = strdup(str);
    if (strCopy == NULL) return NULL;
    
    int nodeCount = 0;
    char *temp = strCopy;
    while (*temp) 
    {
        if (*temp == SEPARATOR[0]) nodeCount++;
        temp++;
    }
    nodeCount++;
    
    char **tokens = (char **)malloc((size_t)nodeCount * sizeof(char *));
    if (tokens == NULL) 
    {
        free(strCopy);
        return NULL;
    }
    
    char *token = strtok(strCopy, SEPARATOR);
    int i = 0;
    while (token != NULL && i < nodeCount) 
    {
        tokens[i++] = token;
        token = strtok(NULL, SEPARATOR);
    }
    
    Node **nodes = (Node **)malloc((size_t)nodeCount * sizeof(Node *));
    if (nodes == NULL) 
    {
        free(tokens);
        free(strCopy);
        return NULL;
    }
    
    for (i = 0; i < nodeCount; i++) 
    {
        if (strcmp(tokens[i], NOD_INEXISTENT) == 0) 
        {
            nodes[i] = NULL;
        } 
        else 
        {
            nodes[i] = (Node *)malloc(sizeof(Node));
            if (nodes[i] == NULL) continue;
            
            nodes[i]->value = atoi(tokens[i]);
            nodes[i]->leftChild = NULL;
            nodes[i]->rightChild = NULL;
        }
    }
    
    for (i = 0; i < nodeCount; i++) 
    {
        if (nodes[i] != NULL) 
        {
            int leftIndex = 2 * i + 1;
            int rightIndex = 2 * i + 2;
            
            if (leftIndex < nodeCount) 
            {
                nodes[i]->leftChild = nodes[leftIndex];
            }
            if (rightIndex < nodeCount) 
            {
                nodes[i]->rightChild = nodes[rightIndex];
            }
        }
    }
    
    Node *root = nodes[0];
    
    free(nodes);
    free(tokens);
    free(strCopy);
    
    return root;
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
    insertNode(&root, 1);
    insertNode(&root, 9);

    /*
                10
               /  \
              5    15
             / \   / \
            3   7 12  18
           /    \
          1     9
    */

    printf("Arborele initial este:\t\t");
    preOrderTraversal(root);
    printf("\n");

    char *treeString = treeToString(root);
    printf("String-ul arborelui este: %s\n", treeString);

    Node *newRoot = stringToTree(treeString);
    printf("Arborele reconstruit este:\t");
    preOrderTraversal(newRoot);
    printf("\n");

    free(treeString);
    freeTree(root);
    freeTree(newRoot);

    return 0;
}