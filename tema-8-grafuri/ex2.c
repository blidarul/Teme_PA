//Realizați un algoritm care să detecteze dacă într-un graf orientat există un drum între două noduri date.
#include <stdio.h>

#include "graph.h"


bool hasPathDFS(Graph *graph, unsigned int current, unsigned int destination, bool *visited)
{
    visited[current] = true;

    if(current == destination)
        return true;
    
    Node *temp = graph->array[current].head;
    while(temp != NULL)
    {
        unsigned int neighbour = temp->dest;
        if(!visited[neighbour])
        {
            if(hasPathDFS(graph, neighbour, destination, visited))
                return true;
        }
        temp = temp->next;
    }

    return false;
}


bool hasPath(Graph *graph, unsigned int source, unsigned int destination)
{
    if(source >= graph->nodeCount || destination >= graph->nodeCount)
        return false;
    if(source == destination)
        return true;
    
    bool *visited = (bool *)malloc(sizeof(graph->nodeCount * sizeof(bool)));
    if(visited == NULL) return false;

    bool path = hasPathDFS(graph, source, destination, visited);

    free(visited);
    return path;
}

void verificaDrum(Graph *graph, unsigned int source, unsigned int destination)
{
    printf("%s drum intre %d si %d\n", hasPath(graph, source, destination) ? "Exista" : "Nu exista", source, destination);
}

int main()
{
    Graph *graph = createGraph(6);
    addEdgeDirected(graph, 0, 1);
    addEdgeDirected(graph, 0, 2);
    addEdgeDirected(graph, 0, 3);
    addEdgeDirected(graph, 2, 3);
    addEdgeDirected(graph, 2, 5);
    addEdgeDirected(graph, 3, 1);
    addEdgeDirected(graph, 4, 1);
    addEdgeDirected(graph, 4, 5);
    addEdgeDirected(graph, 5, 4);

    printAdjList(graph);
    verificaDrum(graph, 0 , 4);
    deleteEdgeDirected(graph, 5, 4);
    printAdjList(graph);
    verificaDrum(graph, 0, 4);
    
    freeGraph(graph);
    return 0;
}