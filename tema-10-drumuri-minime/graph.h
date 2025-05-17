#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

typedef struct Edge
{
    unsigned int source;
    unsigned int destination;
    int weight;
    struct Edge *next;
} Edge;

typedef struct Graph
{
    unsigned int nodeCount;
    unsigned int edgeCount;
    Edge *edgesHead;
    int totalWeight;
    AdjList *array;
    int *parent;
} Graph;

Node* createNode(unsigned int destination);
Edge* createEdge(unsigned int source, unsigned int destination, int weight);
Graph* createGraph(unsigned int nodeCount);
void addEdgeDirected(Graph *graph, Edge edge);
void addEdgeUndirected(Graph *graph, Edge edge);
void deleteEdgeDirected(Graph *graph, Edge edge);
void deleteEdgeUndirected(Graph *graph, Edge edge);
bool searchEdge(Graph *graph, Edge edge);
void setNodeValue(Graph *graph, unsigned int nodeID, int value);
int getNodeValue(Graph *graph, unsigned int nodeID);
void printAdjList(Graph *graph);
Graph* createGraphFromCSV(char *fileName, bool directed);
void printEdges(Graph *graph);
bool cycleDFS(Graph *graph, unsigned int current, int parent, bool *visited);
bool checkCycle(Graph *graph);
Edge *bubbleSort(Edge * head, unsigned int edgeCount);
Graph* Kruskal(Graph *graph);
Graph* Prim(Graph *graph);
int Djikstra(Graph *graph, unsigned int start, unsigned int finish);
int Bellman_Ford(Graph *graph, unsigned int start, unsigned int finish);
void freeGraph(Graph *graph);

#endif