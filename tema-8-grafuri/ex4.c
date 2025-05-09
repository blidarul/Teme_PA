//Realizați un algoritm care să calculeze distanța dintre cel mai mare 
//și cel mai mic nod dintr-un graf neorientat ce ține ca date în noduri numere. 
//Tratați și cazurile în care mai multe noduri au aceeași valoare.

#include "graph.h"

typedef struct Queue
{
    unsigned int value[100];
    int front;
    int rear;
} Queue;

void enqueue(Queue *queue, unsigned int value)
{
    queue->value[++queue->rear] = value;
}

unsigned int dequeue(Queue *queue)
{
    return queue->value[queue->front ++];
}

bool queueIsEmpty(Queue queue)
{
    return (queue.front > queue.rear);
}

void BFS(Graph *graph, unsigned int source, int parent[], int distance[])
{
    Queue queue;
    queue.front = 0;
    queue.rear = -1;

    distance[source] = 0;
    enqueue(&queue,source);

    while(!queueIsEmpty(queue))
    {
        unsigned int current = dequeue(&queue);;
        

        Node *temp = graph->array[current].head;

        while(temp != NULL)
        {
            unsigned int neighbour = temp->dest;
            if(distance[neighbour] == INT_MAX)
            {
                parent[neighbour] = (int) current;
                distance[neighbour] = distance[current] + 1;
                enqueue(&queue, neighbour);
            }
            temp = temp->next;
        }
    }
}

void printShortestPath(Graph *graph, unsigned int source, unsigned int destination)
{
    int parent[graph->nodeCount];
    int distance[graph->nodeCount];

    for(unsigned int i = 0; i < graph->nodeCount; i++)
    {
        parent[i] = -1;
        distance[i] = INT_MAX;
    }

    BFS(graph, source, parent, distance);

    if(distance[destination] == INT_MAX)
    {
        printf("Nu exista drum de la nodul %u (valoare %d) la nodul %u (valoare %d)\n", 
               source, getNodeValue(graph, source), 
               destination, getNodeValue(graph, destination));
        return;
    }

    printf("Distanta: %d\n", distance[destination]);
    printf("Drumul: ");
    
    int path[graph->nodeCount];
    int pathLen = 0;
    
    int currentNode = (int) destination;
    path[pathLen++] = currentNode;
    
    while(parent[currentNode] != -1)
    {
        currentNode = parent[currentNode];
        path[pathLen++] = currentNode;
    }
    
    for(int i = pathLen - 1; i >= 0; i--)
    {
        printf("%d", path[i]);
        if(i > 0) 
            printf(" -> ");
    }
    printf("\n");
}

int main()
{
    Graph *graph = createGraph(10);

    setNodeValue(graph, 0, 0);
    setNodeValue(graph, 1, 4);
    setNodeValue(graph, 2, 10);
    setNodeValue(graph, 3, 9);
    setNodeValue(graph, 4, 20);
    setNodeValue(graph, 5, 25);
    setNodeValue(graph, 6, 9);
    setNodeValue(graph, 7, 89);
    setNodeValue(graph, 8, 65);
    setNodeValue(graph, 9, 89);


    addEdgeUndirected(graph, 0, 1);
    addEdgeUndirected(graph, 1, 2);
    addEdgeUndirected(graph, 1, 3);
    addEdgeUndirected(graph, 0, 4);
    addEdgeUndirected(graph, 4, 5);
    addEdgeUndirected(graph, 5, 6);
    addEdgeUndirected(graph, 1, 7);
    addEdgeUndirected(graph, 2, 8);
    addEdgeUndirected(graph, 5, 9);

    printAdjList(graph);

    int min = INT_MAX;
    int max = INT_MIN;
    int minPos[graph->nodeCount];
    int maxPos[graph->nodeCount];
    int minCount = 0;
    int maxCount = 0;

    for(unsigned int i = 0; i < graph->nodeCount; i++)
    {
        int value = getNodeValue(graph, i);
        
        if(value > max)
        {
            max = value;
            maxPos[0] = (int) i;
            maxCount = 1;
        }
        else if(value == max)
        {
            maxPos[maxCount++] = (int) i;
        }
        
        if(value < min)
        {
            min = value;
            minPos[0] = (int) i;
            minCount = 1;
        }
        else if(value == min)
        {
            minPos[minCount++] = (int) i;
        }
    }

    printf("Noduri cu valoarea minima (%d):\n", min);
    for(int i = 0; i < minCount; i++)
    {
        printf("  Pozitia %d\n", minPos[i]);
    }

    printf("Noduri cu valoarea maxima (%d):\n", max);
    for(int i = 0; i < maxCount; i++)
    {
        printf("  Pozitia %d\n", maxPos[i]);
    }

    printf("\nCalculam distanta intre primul nod cu valoare minima si primul nod cu valoare maxima:\n");
    printShortestPath(graph, (unsigned int)minPos[0], (unsigned int)maxPos[0]);

    int shortestDistance = INT_MAX;
    int bestMinPos = -1;
    int bestMaxPos = -1;

    for(int i = 0; i < minCount; i++)
    {
        for(int j = 0; j < maxCount; j++)
        {
            int parent[graph->nodeCount];
            int distance[graph->nodeCount];
            
            for(unsigned int k = 0; k < graph->nodeCount; k++)
            {
                parent[k] = -1;
                distance[k] = INT_MAX;
            }
            
            BFS(graph, (unsigned int)minPos[i], parent, distance);
            
            if(distance[maxPos[j]] < shortestDistance && distance[maxPos[j]] != INT_MAX)
            {
                shortestDistance = distance[maxPos[j]];
                bestMinPos = minPos[i];
                bestMaxPos = maxPos[j];
            }
        }
    }

    if(bestMinPos != -1 && bestMaxPos != -1)
    {
        printf("\nCea mai scurta distanta dintre oricare nod cu valoare minima si oricare nod cu valoare maxima:\n");
        printShortestPath(graph, (unsigned int)bestMinPos, (unsigned int)bestMaxPos);
    }

    return 0;
}