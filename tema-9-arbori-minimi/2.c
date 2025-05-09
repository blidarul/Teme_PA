//Realizați arborele minim de acoperire folosind algoritmul lui Prim. 
//Afișați ordinea nodurilor, valoarea muchiilor din arbore și costul total.

#include "graph.h"

int main()
{
    Graph *graph = createGraphFromCSV("weighted_graph.csv");

    Graph *minimumSpanningTree = Prim(graph);
    
    printEdges(minimumSpanningTree);

    freeGraph(graph);
    freeGraph(minimumSpanningTree);
    return 0;
}