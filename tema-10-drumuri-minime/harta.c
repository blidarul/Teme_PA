//Călătorul vrea să plece din X spre Y. Ajută-l să găsească cea mai rapidă rută. 
//Afișați ruta pe care a folosit-o să ajungă de la X la Y și km parcurși în total pentru aceste rute (conform hărții):
//X:Timișoara , Y: Constanța
//X:Craiova , Y: Iași
//X:Constanța , Y: Cluj-Napoca

/*
    Timisoara       0
    Cluj-Napoca     1
    Iasi            2
    Sibiu           3
    Brasov          4
    Craiova         5
    Bucuresti       6
    Constanta       7
*/

#include "graph.h"

char* numberToCity(int nr)
{
    switch (nr)
    {
    case 0:
        return "Timisoara";
        break;
    case 1:
        return "Cluj-Napoca";
        break;
    case 2:
        return "Iasi";
        break;
    case 3:
        return "Sibiu";
        break;
    case 4:
        return "Brasov";
        break;
    case 5:
        return "Craiova";
        break;
    case 6:
        return "Bucuresti";
        break;
    case 7:
        return "Constanta";
        break;
    default:
        return NULL;
        break;
    }

}

void printPath(Graph *graph, int start, int finish)
{
    printf("Distanta de la %s la %s este: %d\n", numberToCity(start), numberToCity(finish), Djikstra(graph, (unsigned int)start, (unsigned int)finish));

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
        printf("->%s", numberToCity(pathTaken[i]));
        i--;
    }
    printf("\n");
    
    free(pathTaken);
}

int main()
{
    Graph *graph = createGraphFromCSV("harta.csv", false);

    printPath(graph, 0, 7);
    printPath(graph, 5, 2);
    printPath(graph, 7, 1);

    freeGraph(graph);
    return 0;
}