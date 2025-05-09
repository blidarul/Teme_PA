#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    unsigned int dest;
    struct Node* next;
} Node;

typedef struct AdjList
{
    int value;
    Node *head;
} AdjList;

typedef struct Graph
{
    unsigned int nodeCount;
    unsigned int edgeCount;
    AdjList *array;
} Graph;

Node* createNode(unsigned int destination);
Graph* createGraph(unsigned int nodeCount);
void addEdgeDirected(Graph *graph, unsigned int source, unsigned int destination);
void addEdgeUndirected(Graph *graph, unsigned int source, unsigned int destination);
void deleteEdgeDirected(Graph *graph, unsigned int source, unsigned int destination);
void deleteEdgeUndirected(Graph *graph,unsigned int source, unsigned int destination);
bool searchEdge(Graph *graph,unsigned int source,unsigned int destination);
void setNodeValue(Graph *graph, unsigned int source, int value);
int getNodeValue(Graph *graph, unsigned int source);
void printAdjList(Graph *graph);
void freeGraph(Graph *graph);

#endif