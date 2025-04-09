/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/

#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
} NODE;

typedef struct Graph
{
    int node_count;
    int *visited;
    struct Node **adjacency_lists;
} GRAPH;

typedef struct Stack
{
    int top;
    int capacity;
    int *elements;
} STACK;

NODE *createNode(int node_count)
{
    NODE *newNode = malloc(sizeof(NODE));
    if (!newNode) 
    {
        printf("Eroare alocare memorie pentru nod\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = node_count;
    newNode->next = NULL;
    return newNode;
}

void addEdge(GRAPH *graph, int source, int destination)
{
    NODE *newNode = createNode(destination);
    newNode->next = graph->adjacency_lists[source];
    graph->adjacency_lists[source] = newNode;
    newNode = createNode(source);
    newNode->next = graph->adjacency_lists[destination];
    graph->adjacency_lists[destination] = newNode;
}

GRAPH *createGraph(int node_count)
{
    GRAPH *graph = malloc(sizeof(GRAPH));
    if (!graph) 
    {
        printf("Eroare alocare memorie pentru GRAPH\n");
        exit(EXIT_FAILURE);
    }
    graph->node_count = node_count;
    graph->adjacency_lists = malloc(sizeof(NODE *) * node_count);
    graph->visited = malloc(sizeof(int) * node_count);

    for (int i = 0; i < node_count; i++)
    {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    } 
    return graph;
}


STACK *createStack(int capacity)
{
    STACK *stack = malloc(sizeof(STACK));
    if (!stack) {
        printf("Eroare alocare memorie pentru STACK\n");
        exit(EXIT_FAILURE);
    }
    stack->elements = malloc(capacity * sizeof(int));
    stack->top = -1;
    stack->capacity = capacity;

    return stack;
}

void push(STACK *stack, int value)
{
    if (stack->top < stack->capacity - 1) 
    {
        stack->top++;
        stack->elements[stack->top] = value;
    } 
    else
    {
        printf("Stack overflow!\n");
    }
}

void DFS(GRAPH *graph, STACK *stack, int current_node)
{
    NODE *head = graph->adjacency_lists[current_node];
    NODE *aux = head;
    graph->visited[current_node] = 1;
    printf("%d ", current_node);
    push(stack, current_node);
    while (aux != NULL)
    {
        int nextNode = aux->data;
        if (graph->visited[nextNode] == 0)
            DFS(graph, stack, nextNode);
        aux = aux->next;
    }
}

void insertEdges(GRAPH *graph, int edge_number, int number_of_nodes)
{
    int source, destination, i;
    printf("adauga %d muchii (de la 1 la %d)\n", edge_number, number_of_nodes-1);
    for (i = 0; i < edge_number; i++)
    {
        scanf("%d%d", &source, &destination);
        addEdge(graph, source, destination);
    }
}

void wipe(GRAPH *graph, int number_of_nodes)
{
    for (int i = 0; i < number_of_nodes; i++)
    {
        graph->visited[i] = 0;
    }
} 


void clearStack(STACK *stack)
{
    stack->top = -1;
}

int pathBetween(GRAPH *graph, int number_of_nodes, STACK *stack1, STACK *stack2, int source, int destination)
{
    printf("\nParcurgere de la nodul %d: ", source);
    DFS(graph, stack1, source);
    wipe(graph, number_of_nodes);
    printf("\nParcurgere de la nodul %d: ", destination);
    DFS(graph, stack2, destination);
    printf("\n");

    for (int i = 0; i < stack1->top + 1; i++)
    {
        for (int j = 0; j < stack2->top + 1; j++)
        {
            if ((stack1->elements[i] == destination) && (stack2->elements[j] == source))
                return 1;
        }
    }

    clearStack(stack1);
    clearStack(stack2);

    return 0;
}

int main()
{
    int number_of_nodes, edge_number;
    int source, destination;
    int i, result;

    printf("Cate noduri are graful? ");
    scanf("%d", &number_of_nodes);

    printf("Cate muchii are graful? ");
    scanf("%d", &edge_number);

    GRAPH *graph = createGraph(number_of_nodes);

    STACK *stack1 = createStack(2 * number_of_nodes);
    STACK *stack2 = createStack(2 * number_of_nodes);

    printf("Adauga %d muchii (de la 0 la %d):\n", edge_number, number_of_nodes - 1);
    for (i = 0; i < edge_number; i++)
    {
        printf("Muchia %d (source destination): ", i + 1);
        scanf("%d%d", &source, &destination);
        addEdge(graph, source, destination);
    }

    printf("\nVerificam daca exista drum intre doua restaurante:\n");
    printf("Introdu restaurantul de start: ");
    scanf("%d", &source);
    printf("Introdu restaurantul de destinatie: ");
    scanf("%d", &destination);

    result = pathBetween(graph, number_of_nodes, stack1, stack2, source, destination);
    if (result)
        printf("Exista drum intre restaurantele %d si %d.\n", source, destination);
    else
        printf("Nu exista drum intre restaurantele %d si %d.\n", source, destination);

    return 0;
}
