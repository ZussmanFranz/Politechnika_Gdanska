#include <cstdio>
#include <iostream>
#include <vector> //must be removed!

void parse_graph(std::vector<int> graph[], int degrees[], int graph_size)
{
    int n_edges;
    int connected;

    for (int i = 0; i < graph_size; i++) 
    {
        std::cin >> n_edges;
        degrees[i] = n_edges;

        for (int e = 0; e < n_edges; e++) {
            std::cin >> connected;
            graph[i].push_back(connected);
        }
    }
    return;
}

int partition(int degrees[], int low, int high);
void quickSort(int degrees[], int low, int high); 

void components(std::vector<int> graph[], int graph_size);
void DFS(std::vector<int> graph[], int graph_size, int current, int* checked_count, bool checked[]);

// void bipartiteness(std::vector<int> graph[], int graph_size); //TODO

// void eccentricity_sequence(std::vector<int> graph[], int graph_size); //TODO

// void planarity(std::vector<int> graph[], int graph_size); //TODO

// void colours_greedy(std::vector<int> graph[], int graph_size); //TODO

// void colours_LF(std::vector<int> graph[], int graph_size); //TODO

// void colours_SLF(std::vector<int> graph[], int graph_size); //TODO

// void subgraphs(std::vector<int> graph[], int graph_size); //TODO

// void comlements_edges(std::vector<int> graph[], int graph_size); //TODO


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
        int *degrees = new int[graph_size];

        parse_graph(graph,degrees, graph_size);

        //testing start:
        quickSort(degrees, 0, graph_size - 1);
        for (int i = 0; i < graph_size; i++) {
            printf("%d ", degrees[i]);
        }
        
        // components(graph, graph_size);
        printf("\n?");

        // bipartiteness(graph, graph_size);
        printf("\n?");

        // eccentricity_sequence(graph, graph_size);
        printf("\n?");

        // planarity(graph, graph_size);
        printf("\n?");

        // colours_greedy(graph, graph_size);
        printf("\n?");

        // colours_LF(graph, graph_size);
        printf("\n?");

        // colours_SLF(graph, graph_size);
        printf("\n?");

        // subgraphs(graph, graph_size);
        printf("\n?");

        // comlements_edges(graph, graph_size);
        printf("\n?");

        delete [] graph;
        delete [] degrees;
    }
    
    return 0;
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

    return;
}


void components(std::vector<int> graph[], int graph_size)
{
    int components_count = 0;
    int checked_count = 0;
    bool *checked = new bool[graph_size];
    
    for (int i = 0; i < graph_size; i++) {
        checked[i] = false;
    }

    
    for (int i = 0; i < graph_size; i++) {
        if (!checked[i]) {
            DFS(graph, graph_size, i, &checked_count, checked);
            components_count++;
        }
    }
    

    printf("%d\n", components_count);

    delete [] checked;
    return;
}

void DFS(std::vector<int> graph[], int graph_size, int current, int* checked_count, bool checked[])
{
    if (checked[current]) {
        return;
    }

    //printf("checking V%d\n", current + 1);

    *checked_count += 1;
    checked[current] = true;

    for (int neighbour : graph[current]) {
        if (!checked[neighbour - 1]) {
            DFS(graph, graph_size, neighbour - 1, checked_count, checked);
        }
    }

    return;
}

// void bipartiteness(std::vector<int> graph[], int graph_size)
// {
//     printf("?\n");
//     return;
// }

// void eccentricity_sequence(std::vector<int> graph[], int graph_size)
// {
//     printf("?\n");
//     return;
// }

// void planarity(std::vector<int> graph[], int graph_size)
// {
//     printf("?\n");
//     return;
// }

// void colours_greedy(std::vector<int> graph[], int graph_size)
// {
//     printf("?\n");
//     return;
// }


// void colours_LF(std::vector<int> graph[], int graph_size)
// {
//     printf("?\n");
//     return;
// }

// void colours_SLF(std::vector<int> graph[], int graph_size)
// {
//     printf("?\n");
//     return;
// }

// void subgraphs(std::vector<int> graph[], int graph_size)
// {
//     printf("?\n");
//     return;
// }

// void comlements_edges(std::vector<int> graph[], int graph_size)
// {
//     printf("?\n");
//     return;
// }




