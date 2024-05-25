#include <cstdio>
#include <iostream>
#include <vector> //must be removed!

void parse_graph(std::vector<int> graph[], int graph_size)
{
    int n_edges;
    int connected;

    for (int i = 0; i < graph_size; i++) 
    {
        std::cin >> n_edges;
        for (int e = 0; e < n_edges; e++) {
            std::cin >> connected;
            graph[i].push_back(connected);
        }
    }
    return;
}

void degree_sequence(std::vector<int> graph[], int graph_size);
int partition(int degrees[], int low, int high);
void quickSort(int degrees[], int low, int high); 

void components(std::vector<int> graph[], int graph_size); //TODO

void bipartiteness(std::vector<int> graph[], int graph_size); //TODO

void eccentricity_sequence(std::vector<int> graph[], int graph_size); //TODO

void planarity(std::vector<int> graph[], int graph_size); //TODO

void colours_greedy(std::vector<int> graph[], int graph_size); //TODO

void colours_LF(std::vector<int> graph[], int graph_size); //TODO

void colours_SLF(std::vector<int> graph[], int graph_size); //TODO

void subgraphs(std::vector<int> graph[], int graph_size); //TODO

void comlements_edges(std::vector<int> graph[], int graph_size); //TODO


int main()
{
    std::ios_base::sync_with_stdio(false);

    int n_graphs;
    std::cin >> n_graphs;

    for (int g = 0; g < n_graphs; g++) 
    {
        int graph_size;

        std::cin >> graph_size;

        std::vector<int>* graph = new std::vector<int> [graph_size];
        parse_graph(graph, graph_size);

        //testing start:
        degree_sequence(graph, graph_size);
        
        components(graph, graph_size);

        bipartiteness(graph, graph_size);

        eccentricity_sequence(graph, graph_size);

        planarity(graph, graph_size);

        colours_greedy(graph, graph_size);

        colours_LF(graph, graph_size);

        colours_SLF(graph, graph_size);

        subgraphs(graph, graph_size);

        comlements_edges(graph, graph_size);

        delete [] graph;    
    }
    
    return 0;
}


void degree_sequence(std::vector<int> graph[], int graph_size)
{
    int *degrees = new int[graph_size];

    for (int v = 0; v < graph_size; v++) {
        degrees[v] = graph[v].size();
    }

    //sort_by_degree(degrees, graph_size);
    quickSort(degrees, 0, graph_size - 1);

    for (int i = 0; i < graph_size; i++) {
        printf("%d ", degrees[i]);
    }

    printf("\n");

    delete [] degrees;
    return;
}

int partition(int degrees[], int low, int high) {
    int pivot = degrees[high]; // Choosing the last element as the pivot
    int i = low - 1; // Index of the smaller element

    for (int j = low; j < high; j++) {
        // If the current element is smaller than or equal to the pivot
        if (degrees[j] > pivot){ 
            i++; // Increment index of smaller element
            std::swap(degrees[i], degrees[j]);
        }
    }

    std::swap(degrees[i + 1], degrees[high]); // Swap pivot to its correct position
    return i + 1;
}

void quickSort(int degrees[], int low, int high) {
    if (low < high) {
        // Partitioning index
        int pi = partition(degrees, low, high);

        // Separately sort elements before and after partition
        quickSort(degrees, low, pi - 1);
        quickSort(degrees, pi + 1, high);
    }
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




