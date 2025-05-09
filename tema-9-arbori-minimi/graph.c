#include "graph.h"

Node* createNode(unsigned int destination)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->dest = destination;
    newNode->next = NULL;
    return newNode;
}

Edge* createEdge(unsigned int source, unsigned int destination, unsigned int weight)
{
    Edge *newEdge = (Edge*)malloc(sizeof(Edge));
    if (newEdge == NULL)
    {
        return NULL;
    }
    newEdge->source = source;
    newEdge->destination = destination;
    newEdge->weight = weight;
    newEdge->next = NULL;
    return newEdge;
}

Graph* createGraph(unsigned int nodeCount)
{
    Graph *graph = (Graph*)malloc(sizeof(Graph));
    graph->nodeCount = nodeCount;
    graph->edgeCount = 0;
    graph->totalWeight = 0;
    graph->array = (AdjList*)malloc(nodeCount * sizeof(AdjList));
    for(unsigned int i = 0; i < nodeCount; i++)
    {
        graph->array[i].head = NULL;
        graph->array[i].value = 0;
    }
    return graph;
}

bool searchEdge(Graph *graph, Edge edge)
{
    if(edge.source >= graph->nodeCount || edge.destination >= graph->nodeCount)
        return false;
    
    Node *temp = graph->array[edge.source].head;
    while(temp != NULL)
    {
        if(temp->dest == edge.destination)
            return true;
        temp = temp->next;
    }

    return false;
}

void addEdgeDirected(Graph *graph, Edge edge)
{
    if(searchEdge(graph, edge))
        return;
    Node *newNode = createNode(edge.destination);
    newNode->next = graph->array[edge.source].head;
    graph->array[edge.source].head = newNode;
    
    Edge *newEdge = createEdge(edge.source, edge.destination, edge.weight);
    
    if(graph->edgeCount == 0)
    {
        graph->edgesHead = newEdge;
    }
    else
    {
        newEdge->next = graph->edgesHead;
        graph->edgesHead = newEdge;
    }
    
    graph->totalWeight += edge.weight;
    graph->edgeCount++;
}

void addEdgeUndirected(Graph *graph, Edge edge)
{
    if(searchEdge(graph, edge))
        return;
    
    addEdgeDirected(graph, edge);
    
    Edge reverseEdge = {edge.destination, edge.source, edge.weight, NULL};
    addEdgeDirected(graph, reverseEdge);
    
    graph->totalWeight -= edge.weight;
    graph->edgeCount--;
}

void deleteEdgeDirected(Graph *graph, Edge edge)
{
    Node *temp = graph->array[edge.source].head;
    Node *prev = NULL;

    while(temp != NULL && temp->dest != edge.destination)
    {
        prev = temp;
        temp = temp->next;
    }
    if(temp != NULL)
    {
        if(prev != NULL)
            prev->next = temp->next;
        else
            graph->array[edge.source].head = temp->next;
        free(temp);
    }
    
    Edge *currentEdge = graph->edgesHead;
    Edge *prevEdge = NULL;
    
    while(currentEdge != NULL)
    {
        if(currentEdge->source == edge.source && currentEdge->destination == edge.destination)
        {
            if(prevEdge == NULL)
                graph->edgesHead = currentEdge->next;
            else
                prevEdge->next = currentEdge->next;
                
            free(currentEdge);
            break;
        }
        prevEdge = currentEdge;
        currentEdge = currentEdge->next;
    }
    
    graph->totalWeight -= edge.weight;
    graph->edgeCount--;
}

void deleteEdgeUndirected(Graph *graph, Edge edge)
{
    deleteEdgeDirected(graph, edge);
    
    Edge reverseEdge = {edge.destination, edge.source, edge.weight, NULL};
    deleteEdgeDirected(graph, reverseEdge);
    
    graph->totalWeight += edge.weight;
    graph->edgeCount++;
}

void setNodeValue(Graph *graph, unsigned int nodeID, int value)
{
    if (nodeID < graph->nodeCount)
    {
        graph->array[nodeID].value = value;
    }
}

int getNodeValue(Graph *graph, unsigned int nodeID)
{
    if (nodeID < graph->nodeCount)
    {
        return graph->array[nodeID].value;
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

Graph* createGraphFromCSV(char *fileName)
{
    FILE *csv = fopen(fileName,"r");
    if(csv == NULL)
        return NULL;
    char buffer[1024];
    
    unsigned int maxNode = 0;
    
    int row = 0;
    
    while(fgets(buffer, 1024, csv))
    {
        row ++;

        if(row == 1)
            continue;
        

        unsigned int source = (unsigned) atoi(strtok(buffer, ","));
        unsigned int destination = (unsigned) atoi(strtok(NULL, ",")); 
        if(maxNode < source)
            maxNode = source;
        if(maxNode < destination)
            maxNode = destination;
        strtok(NULL, ",");
    }
    
    rewind(csv);
    
    Graph *graph = createGraph(maxNode + 1);

    row = 0;

    while(fgets(buffer, 1024, csv))
    {
        row ++;

        if(row == 1)
            continue;

        Edge tempEdge = {(unsigned) atoi(strtok(buffer, ",")), 
            (unsigned) atoi(strtok(NULL, ",")), (unsigned) atoi(strtok(NULL, ",")), NULL};

        addEdgeUndirected(graph, tempEdge);
        
        if(!searchEdge(graph, tempEdge))
            return NULL;
        
    }

    fclose(csv);
    return graph;
}

void printEdges(Graph *graph)
{
    Edge *head = graph->edgesHead;
    FILE *output = fopen("output.csv","w");
    if(output == NULL)
        return;

    fprintf(stdout,"Edges:\n");
    fprintf(output,"Source,Destination,Weight");

    while(head != NULL)
    {
        fprintf(stdout,"(%u<->%u) = %u\n", head->source, head->destination, head->weight);
        fprintf(output,"\n%u,%u,%u", head->source, head->destination, head->weight);

        head = head->next;
        head = head->next;
    }

    fprintf(stdout,"Total weight: %u\n", graph->totalWeight);

    fclose(output);
}

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

Edge* bubbleSort(Edge * head, unsigned int edgeCount)
{
    if(head == NULL || head->next == NULL)
        return head;

    bool swapped;
    unsigned int i = 0;

    while(i < edgeCount * 2)
    {
        Edge *currEdge = head;
        Edge *prevEdge = head;
        swapped = false;

        while(currEdge->next != NULL)
        {
            Edge *ptr = currEdge->next;

            if(currEdge->weight > ptr->weight)
            {
                swapped = true;

                if(currEdge == head)
                {
                    currEdge->next = ptr->next;
                    ptr->next = currEdge;
                    prevEdge = ptr;
                    head = prevEdge;
                }
                else
                {
                    currEdge->next = ptr->next;
                    ptr->next = currEdge;
                    prevEdge->next = ptr;
                    prevEdge = ptr;
                }

                continue;
            }

            prevEdge = currEdge;
            currEdge = currEdge->next;
        }

        if(!swapped)
            break;

        i ++;
    }

    return head;
}

unsigned int getEdgeWeight(Graph *graph, unsigned int source, unsigned int dest) 
{
    Edge *currentEdge = graph->edgesHead;
    while (currentEdge != NULL) 
    {
        if ((currentEdge->source == source && currentEdge->destination == dest) ||
            (currentEdge->source == dest && currentEdge->destination == source)) 
        {
            return currentEdge->weight;
        }
        currentEdge = currentEdge->next;
    }
    return UINT_MAX; // Edge not found
}

Graph* Kruskal(Graph *graph)
{
    graph->edgesHead = bubbleSort(graph->edgesHead, graph->edgeCount);

    Graph *tree = createGraph(graph->nodeCount);

    Edge *currEdge = graph->edgesHead;

    while(currEdge != NULL)
    {
        addEdgeUndirected(tree, *currEdge);

        if(checkCycle(tree))
            deleteEdgeUndirected(tree, *currEdge);
        
        currEdge = currEdge->next;
    }

    return tree;
}

Graph *Prim(Graph *graph)
{
    Graph *tree = createGraph(graph->nodeCount);
    bool *visited = (bool*)malloc(graph->nodeCount * sizeof(bool));
    
    for (unsigned int i = 0; i < graph->nodeCount; i++)
    {
        visited[i] = false;
    }
    
    visited[0] = true;
    
    unsigned int edgeCount = 0;
    while (edgeCount < graph->nodeCount - 1)
    {
        Edge minEdge = {0, 0, UINT_MAX, NULL};
        
        for (unsigned int i = 0; i < graph->nodeCount; i++)
        {
            if (visited[i])
            {
                Node *current = graph->array[i].head;
                while (current != NULL)
                {
                    if (!visited[current->dest])
                    {
                        unsigned int weight = getEdgeWeight(graph, i, current->dest);
                        
                        if (weight < minEdge.weight)
                        {
                            minEdge.weight = weight;
                            minEdge.source = i;
                            minEdge.destination = current->dest;
                        }
                    }
                    current = current->next;
                }
            }
        }
        
        if (minEdge.weight == UINT_MAX)
        {
            break;
        }
        
        addEdgeUndirected(tree, minEdge);
        visited[minEdge.destination] = true;
        edgeCount++;
    }
    
    free(visited);
    return tree;
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
    
    Edge *currentEdge = graph->edgesHead;
    while (currentEdge != NULL)
    {
        Edge *tempEdge = currentEdge;
        currentEdge = currentEdge->next;
        free(tempEdge);
    }

    free(graph->array);
    free(graph);
}