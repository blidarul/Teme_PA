//Găsiți cel mai bun drum folosind A* search pentru următorul traseu.
/*
0 1 0 0 0 0
0 0 0 0 0 0
0 1 0 1 0 0
0 1 0 0 1 0
0 0 0 0 1 0
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define ROWS 5
#define COLS 6

typedef struct Node
{
    int row, col;
    int gCost;
    int hCost;
    int fCost;
    struct Node* parent;
    bool closed;
} Node;

Node* createNode(int row, int col, Node* parent)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode)
    {
        fprintf(stderr, "Alocarea memoriei pentru nod a esuat");
        exit(1);
    }
    newNode->row = row;
    newNode->col = col;
    newNode->gCost = 0;
    newNode->hCost = 0;
    newNode->fCost = 0;
    newNode->parent = parent;
    newNode->closed = false;
    return newNode;
}

int heuristic(int r1, int c1, int r2, int c2)
{
    return abs(r1 - r2) + abs(c1 - c2);
}

bool isValid(int r, int c)
{
    return (r >= 0 && r < ROWS && c >= 0 && c < COLS);
}

bool isObstacle(int grid[ROWS][COLS], int r, int c)
{
    return grid[r][c] == 1;
}

void printPath(Node* targetNode)
{
    if (targetNode == NULL)
    {
        printf("Niciun drum de afisat.\n");
        return;
    }
    Node* pathNodes[ROWS * COLS];
    int pathLen = 0;
    Node* current = targetNode;
    while (current != NULL)
    {
        if (pathLen < ROWS * COLS)
        {
            pathNodes[pathLen++] = current;
        }
        else
        {
            printf("Drumul este prea lung pentru a fi stocat pentru afisare.\n"); 
            break;
        }
        current = current->parent;
    }

    printf("Drum (de la start la final): ");
    for (int i = pathLen - 1; i >= 0; i--)
    {
        printf("(%d,%d) ", pathNodes[i]->row, pathNodes[i]->col);
        if (i > 0)
        {
            printf("-> ");
        }
    }
    printf("\n");
}

void aStar(int grid[ROWS][COLS], Node* startCoords, Node* endCoords)
{
    Node* nodeMap[ROWS][COLS];
    for (int r = 0; r < ROWS; ++r)
    {
        for (int c = 0; c < COLS; ++c)
        {
            nodeMap[r][c] = NULL;
        }
    }

    Node* startNode = createNode(startCoords->row, startCoords->col, NULL);
    startNode->gCost = 0;
    startNode->hCost = heuristic(startNode->row, startNode->col, endCoords->row, endCoords->col);
    startNode->fCost = startNode->gCost + startNode->hCost;
    nodeMap[startNode->row][startNode->col] = startNode;

    int dr[] = {-1, 1, 0, 0}; 
    int dc[] = {0, 0, -1, 1};
    int numDirections = 4; 

    while (true)
    {
        Node* currentNode = NULL;
        int minFCost = -1;

        for (int r = 0; r < ROWS; ++r)
        {
            for (int c = 0; c < COLS; ++c)
            {
                if (nodeMap[r][c] != NULL && !nodeMap[r][c]->closed)
                {
                    if (currentNode == NULL || nodeMap[r][c]->fCost < minFCost)
                    {
                        minFCost = nodeMap[r][c]->fCost;
                        currentNode = nodeMap[r][c];
                    }
                    else if (nodeMap[r][c]->fCost == minFCost)
                    {
                        if (nodeMap[r][c]->hCost < currentNode->hCost)
                        {
                            currentNode = nodeMap[r][c];
                        }
                    }
                }
            }
        }

        if (currentNode == NULL) 
        {
            printf("Niciun drum gasit.\n");
            break;
        }

        if (currentNode->row == endCoords->row && currentNode->col == endCoords->col) 
        {
            printf("Drum gasit!\n");
            printPath(currentNode);
            break; 
        }

        currentNode->closed = true;

        for (int i = 0; i < numDirections; ++i) 
        {
            int nextRow = currentNode->row + dr[i];
            int nextCol = currentNode->col + dc[i];

            if (!isValid(nextRow, nextCol) || isObstacle(grid, nextRow, nextCol)) 
            {
                continue;
            }

            Node* neighborNode = nodeMap[nextRow][nextCol];

            if (neighborNode != NULL && neighborNode->closed) 
            {
                continue;
            }

            int tentativeGCost = currentNode->gCost + 1; 

            if (neighborNode == NULL)
            {
                neighborNode = createNode(nextRow, nextCol, currentNode);
                neighborNode->gCost = tentativeGCost;
                neighborNode->hCost = heuristic(nextRow, nextCol, endCoords->row, endCoords->col);
                neighborNode->fCost = neighborNode->gCost + neighborNode->hCost;
                nodeMap[nextRow][nextCol] = neighborNode;
            }
            else if (tentativeGCost < neighborNode->gCost)
            {
                neighborNode->parent = currentNode;
                neighborNode->gCost = tentativeGCost;
                neighborNode->fCost = neighborNode->gCost + neighborNode->hCost;
            }
        }
    }

    for (int r = 0; r < ROWS; ++r) 
    {
        for (int c = 0; c < COLS; ++c) 
        {
            if (nodeMap[r][c] != NULL) 
            {
                free(nodeMap[r][c]);
                nodeMap[r][c] = NULL;
            }
        }
    }
}


int main() 
{
    int grid[ROWS][COLS] = 
    {
        {0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 0},
        {0, 1, 0, 0, 1, 0},
        {0, 0, 0, 0, 1, 0}
    };

    Node* startCoordNode = createNode(0, 0, NULL); 
    Node* endCoordNode = createNode(ROWS - 1, COLS - 1, NULL); 

    if (!isValid(startCoordNode->row, startCoordNode->col) || 
        isObstacle(grid, startCoordNode->row, startCoordNode->col)) 
    {
        printf("Nodul de start este nevalid sau un obstacol.\n");
        free(startCoordNode);
        free(endCoordNode);
        return 1;
    }
    if (!isValid(endCoordNode->row, endCoordNode->col) ||
        isObstacle(grid, endCoordNode->row, endCoordNode->col)) 
    {
        printf("Nodul de final este nevalid sau un obstacol.\n");
        free(startCoordNode);
        free(endCoordNode);
        return 1;
    }
    
    printf("Pornire cautare A* de la (%d,%d) la (%d,%d)...\n", 
           startCoordNode->row, startCoordNode->col, 
           endCoordNode->row, endCoordNode->col);
    
    aStar(grid, startCoordNode, endCoordNode);

    free(startCoordNode);
    free(endCoordNode);
    
    return 0;
}