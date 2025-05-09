//Realizați un algoritm care să detecteze dacă există cicluri într-un graf neorientat.

#include "graph.h"
#include <stdio.h>
#include <stdbool.h>

bool cycleDFS(Graph *graph, unsigned int current, int parent, bool *visited)
{
    visited[current] = true;

    Node *temp = graph->array[current].head;
    
    while(temp != NULL)
    {
        unsigned int neighbour = temp->dest;
        
        if(!visited[neighbour])
        {
            if(cycleDFS(graph, neighbour, (int)current, visited))
                return true;
        }
        else
        {
            if((int)neighbour != parent)
                return true;
        }

        temp = temp->next;
    }

    return false; 
}

bool checkCycle(Graph *graph)
{
    if(graph->edgeCount > graph->nodeCount - 1)
        return true;
    
    bool *visited = (bool*)malloc(graph->nodeCount * sizeof(bool));

    for(unsigned int i = 0; i < graph->nodeCount; i++)
    {
        visited[i] = false;
    }

    for(unsigned int i = 0; i < graph->nodeCount; i++)
    {
        if(!visited[i])
        {
            if(cycleDFS(graph, i, -1, visited))
                return true;
        }
    }

    return false;
}

void verificaBucle(Graph *graph)
{
    printf("Graful %s bucle\n", checkCycle(graph) ? "are" : "NU are");
}

int main()
{
    Graph *graph = createGraph(6);
    addEdgeUndirected(graph, 0, 1);
    addEdgeUndirected(graph, 0, 1);
    addEdgeUndirected(graph, 0, 2);
    addEdgeUndirected(graph, 1, 3);
    addEdgeUndirected(graph, 2, 3);
    addEdgeUndirected(graph, 3, 4);
    addEdgeUndirected(graph, 4, 5);

    printAdjList(graph);
    verificaBucle(graph);
    deleteEdgeUndirected(graph, 1, 3);
    printf("\n");
    printAdjList(graph);
    verificaBucle(graph);

    freeGraph(graph);
    return 0;
}