//Realizați drumul de cost  minim de la un nod ales sursa pana la un altul folosind algoritmul lui Bellman-Ford. 
//Afișați ordinea nodurilor, valoarea muchiilor din arbore și costul total.

#include "graph.h"

int main()
{
//Graf 1
    Graph *graph = createGraphFromCSV("weighted_graph.csv", false);

    int start = 0;
    int finish = 15;

    printf("Distanta de la nodul %d la nodul %d in graful 1 este: %d\n", start, finish, Bellman_Ford(graph, (unsigned int)start, (unsigned int)finish));

    printf("Nodurile cu valori actualizate(distanta fata de nodul %d):\n", start);
    printAdjList(graph);

    int *pathTaken;
    pathTaken = (int *)malloc(graph->nodeCount * sizeof(int));

    int i = 0;
    pathTaken[i] = finish;
    int currentNode = finish;
    while(currentNode != start)
    {
        i++;
        currentNode = graph->parent[currentNode];
        pathTaken[i] = currentNode;
    }
    
    while(i >= 0)
    {
        printf("->%d", pathTaken[i]);
        i--;
    }
    printf("\n");

    free(pathTaken);
    freeGraph(graph);

//Graf 2
    Graph *graph2 = createGraphFromCSV("weighted_graph_2.csv", true);

    start = 0;
    finish = 15;

    printf("Distanta de la nodul %d la nodul %d in graful 2 este: %d\n", start, finish, Bellman_Ford(graph2, (unsigned int)start, (unsigned int)finish));
    
    printf("Nodurile cu valori actualizate(distanta fata de nodul %d):\n", start);
    printAdjList(graph2);

    i = 0;

    pathTaken = (int *)malloc(graph2->nodeCount * sizeof(int));

    pathTaken[i] = finish;
    currentNode = finish;
    while(currentNode != start)
    {
        i++;
        currentNode = graph2->parent[currentNode];
        pathTaken[i] = currentNode;
    }
    
    while(i >= 0)
    {
        printf("->%d", pathTaken[i]);
        i--;
    }
    printf("\n");


    free(pathTaken);
    freeGraph(graph2);
    return 0;
}