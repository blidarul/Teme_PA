//Realizați arborele minim de acoperire folosind algoritmul lui Kruskal.
//Afișați ordinea nodurilor, valoarea muchiilor din arbore și costul total.

#include "graph.h"

int main()
{
    Graph *graph = createGraphFromCSV("weighted_graph.csv");

    Graph *minimumSpanningTree = Kruskal(graph);

    minimumSpanningTree->edgesHead = bubbleSort(minimumSpanningTree->edgesHead, minimumSpanningTree->edgeCount);
    printEdges(minimumSpanningTree);

    freeGraph(minimumSpanningTree);
    freeGraph(graph);
    return 0;
}