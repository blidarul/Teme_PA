#include "graph.h"

Node* createNode(unsigned int destination)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->dest = destination;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(unsigned int nodeCount)
{
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->nodeCount = nodeCount;
    graph->edgeCount = 0;
    graph->array = (AdjList*)malloc(nodeCount * sizeof(AdjList));
    for(unsigned int i = 0; i < nodeCount; i++)
    {
        graph->array[i].head = NULL;
        graph->array[i].value = 0;
    }
    return graph;
}

bool searchEdge(Graph *graph, unsigned int source, unsigned int destination)
{
    Node *temp = graph->array[source].head;
    while(temp != NULL)
    {
        if(temp->dest == destination)
            return true;
        temp = temp->next;
    }

    return false;
}

void addEdgeDirected(Graph *graph, unsigned int source, unsigned int destination)
{
    if(searchEdge(graph, source, destination))
        return;
    Node* newNode = createNode(destination);
    newNode->next = graph->array[source].head;
    graph->array[source].head = newNode;
    graph->edgeCount ++;
}

void addEdgeUndirected(Graph *graph, unsigned int source, unsigned int destination)
{
    if(searchEdge(graph, source, destination))
        return;
    addEdgeDirected(graph, source, destination);
    addEdgeDirected(graph, destination, source);
    graph->edgeCount --;
}

void deleteEdgeDirected(Graph *graph, unsigned int source, unsigned int destination)
{
    Node *temp = graph->array[source].head;
    Node *prev = NULL;

    while(temp != NULL && temp->dest != destination)
    {
        prev = temp;
        temp = temp->next;
    }
    if(temp != NULL)
    {
        if(prev != NULL)
            prev->next = temp->next;
        else
            graph->array[source].head = temp->next;
        free(temp);
    }
    graph->edgeCount --;
}

void deleteEdgeUndirected(Graph *graph, unsigned int source, unsigned int destination)
{
    deleteEdgeDirected(graph, source, destination);
    deleteEdgeDirected(graph, destination, source);
    graph->edgeCount ++;
}

void setNodeValue(Graph *graph, unsigned int source, int value)
{
    if (source < graph->nodeCount)
    {
        graph->array[source].value = value;
    }
}

int getNodeValue(Graph *graph, unsigned int source)
{
    if (source < graph->nodeCount)
    {
        return graph->array[source].value;
    }
    return 0;
}

void printAdjList(Graph *graph)
{
    printf("The graph has %u nodes and %u edges.\n", graph->nodeCount, graph->edgeCount);
    printf("Adjancency List ([Node ID] Node value):\n");
    
    for(unsigned int i = 0; i < graph->nodeCount; i++)
    {
        printf("([%u] %u):", i, graph->array[i].value);
        
        Node *current = graph->array[i].head;
        while(current != NULL)
        {
            printf(" -> ([%d] %d)", current->dest, graph->array[current->dest].value);
            current = current->next;
        }
        
        printf("\n");
    }
}

void freeGraph(Graph *graph)
{
    if (graph == NULL) return;
    
    for (unsigned int i = 0; i < graph->nodeCount; i++)
    {
        Node *current = graph->array[i].head;
        while (current != NULL)
        {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
    
    free(graph->array);
    free(graph);
}