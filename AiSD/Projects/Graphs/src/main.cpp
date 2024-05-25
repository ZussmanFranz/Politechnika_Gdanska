#include <cstdio>
#include <iostream>
#include <vector> //must be removed!

void parse_graph(std::vector<int> graph[], int graph_size)
{
    for (int i = 0; i < graph_size; i++) {
        for (int j = 0; j < graph_size; j++) {
            if (getchar() == '1') {
                graph[i].push_back(j);
            }
        }
    }
    return;
}

void degree_sequence(std::vector<int> graph[], int graph_size);
void sort_by_degree(int degrees[], int graph_size);

void components(std::vector<int> graph[], int graph_size); //TODO

void bipartiteness(std::vector<int> graph[], int graph_size); //TODO

void eccentricity_sequence(std::vector<int> graph[], int graph_size); //TODO

void planarity(std::vector<int> graph[], int graph_size); //TODO

void colours_greedy(std::vector<int> graph[], int graph_size); //TODO

void colours_LF(std::vector<int> graph[], int graph_size); //TODO

void colours_SLF(std::vector<int> graph[], int graph_size); //TODO

void subgraphs(std::vector<int> graph[], int graph_size); //TODO

void comlements_edges(std::vector<int> graph[], int graph_size); //TODO


int main(int argc, char *argv[])
{
    int graph_size;

    std::cin >> graph_size;

    std::vector<int>* graph = new std::vector<int> [graph_size];
    parse_graph(graph, graph_size);

    degree_sequence(graph, graph_size);
    
    components(graph, graph_size);

    bipartiteness(graph, graph_size);

    planarity(graph, graph_size);

    colours_greedy(graph, graph_size);

    colours_LF(graph, graph_size);

    colours_SLF(graph, graph_size);

    subgraphs(graph, graph_size);

    comlements_edges(graph, graph_size);

    delete [] graph;
    return 0;
}

void degree_sequence(std::vector<int> graph[], int graph_size)
{
    int *degrees = new int[graph_size];

    for (int v = 0; v < graph_size; v++) {
        degrees[v] = graph[v].size();
    }

    sort_by_degree(degrees, graph_size);

    for (int i = 0; i < graph_size; i++) {
        printf("%d ", degrees[i]);
    }

    printf("\n");

    delete [] degrees;
    return;
}

void sort_by_degree(int degrees[], int graph_size)
{
    int temp;
    int sorted = 0;

    while (sorted < graph_size) {
        for (int i = graph_size - 2; i >= sorted; i--) {
            if (degrees[i] < degrees[i + 1]) {
                temp = degrees[i];
                degrees[i] = degrees[i + 1];
                degrees[i + 1] = temp;
            }
        }
        sorted++;
    }

    return;
}

void components(std::vector<int> graph[], int graph_size)
{
    printf("?\n");
    return;
}

void bipartiteness(std::vector<int> graph[], int graph_size)
{
    printf("?\n");
    return;
}

void eccentricity_sequence(std::vector<int> graph[], int graph_size)
{
    printf("?\n");
    return;
}

void planarity(std::vector<int> graph[], int graph_size)
{
    printf("?\n");
    return;
}

void colours_greedy(std::vector<int> graph[], int graph_size)
{
    printf("?\n");
    return;
}


void colours_LF(std::vector<int> graph[], int graph_size)
{
    printf("?\n");
    return;
}

void colours_SLF(std::vector<int> graph[], int graph_size)
{
    printf("?\n");
    return;
}

void subgraphs(std::vector<int> graph[], int graph_size)
{
    printf("?\n");
    return;
}

void comlements_edges(std::vector<int> graph[], int graph_size)
{
    printf("?\n");
    return;
}




