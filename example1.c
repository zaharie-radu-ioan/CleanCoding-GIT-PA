/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/

#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
} NODE;
/// pentru simplitate, folosim int uri pt a numi restaurantel/locatiile
/// ex: 1 - restaurantul 1 si tot asa

typedef struct Graph
{
    int v;
    int *visited;
    struct Node **alists;
} GPH;

typedef struct Stack
{
    int t;
    int capac;
    int *array;
} STK;

NODE *create_node(int v)
{
    NODE *new_node = malloc(sizeof(NODE));

    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

void add_edge(GPH *graph, int src, int dest)
{
    NODE *new_node = create_node(dest);

    new_node->next = graph->alists[src];
    graph->alists[src] = new_node;

    new_node = create_node(src);

    new_node->next = graph->alists[dest];
    graph->alists[dest] = new_node;
}

GPH *create_graph(int v)
{
    int i;

    GPH *graph = malloc(sizeof(GPH));

    graph->v = v;
    graph->alists = malloc(sizeof(NODE *));
    graph->visited = malloc(sizeof(int) * v);

    for (int i = 0; i < v; i++)
    {
        graph->alists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

STK *create_stack(int capac)
{
    STK *stack = malloc(sizeof(STK));
    stack->array = malloc(capac * sizeof(int));
    stack->t = -1;
    stack->capac = capac;

    return stack;
}

void push(int pushed, STK *stack)
{
    stack->t = stack->t + 1;
    stack->array[stack->t] = pushed;
}

void DFS(GPH *graph, STK *stack, int vertex_nr)
{
    NODE *adj_list = graph->alists[vertex_nr];
    NODE *temp = adj_list;

    graph->visited[vertex_nr] = 1;
    printf("%d ", vertex_nr);
    push(vertex_nr, stack);

    while (temp != NULL)
    {
        int connected_vertex = temp->data;

        if (graph->visited[connected_vertex] == 0)
        {
            DFS(graph, stack, connected_vertex);
        }
        temp = temp->next;
    }
}

void insert_edges(GPH *graph, int nr_of_edges, int nrv)
{
    int src, dest, i;

    printf("adauga %d muchii (de la 1 la %d)\n", nr_of_edges, nrv);

    for (i = 0; i < nr_of_edges; i++)
    {
        scanf("%d%d", &src, &dest);
        add_edge(graph, src, dest);
    }
}

void wipe(GPH *graph, int nrv)
{
    for (int i = 0; i < nrv; i++)
    {
        graph->visited[i] = 0;
    }
}

void canbe(GPH *graph, int nrv, STK *stack1, STK *stack2)
{
    int *canbe = calloc(5, sizeof(int)); // 0 sau 1 daca poate fi sau nu ajuns

    for (int i = 0; i < nrv; i++) // aici i tine loc de numar adica de restaurant
    {
        for (int j = 0; j < 5; j++)
        {
            DFS(graph, stack1, i);

            wipe(graph, nrv);

            DFS(graph, stack2, j);

            for (int j = 0; j < nrv && !ans; j++)
            {
                for (int i = 0; i < nrv && !ans; i++)
                {
                    if ((stack1->array[i] == j) && (stack2->array[j] == i))
                    {
                        canbe = 1;
                    }
                }
            }
        }
    }
}

int main()
{

    int nrv;
    int nr_of_edges;
    int src, dest;
    int i;
    int vertex_1;
    int vertex_2;
    int ans;

    printf("cate noduri are graful?");
    scanf("%d", &nrv);

    printf("cate muchii are graful?");
    scanf("%d", &nr_of_edges);

    GPH *graph = create_graph(nrv);

    STK *stack1 = create_stack(2 * nrv);
    STK *stack2 = create_stack(2 * nrv);

    insert_edges(graph, nr_of_edges, nrv);

    canbe(graph, nrv, stack1, stack2);

    return 0;
}
