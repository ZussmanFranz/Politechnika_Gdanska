#include <cstdio>
#include <cstdlib>
#include <vector> //must be removed!

void parse_graph(std::vector<int> graph[], int degrees[], int graph_size, int* edges_count)
{
    int n_edges;
    int connected;

    for (int i = 0; i < graph_size; i++) 
    {
        scanf("%d",&n_edges);  
        degrees[i] = n_edges;

        for (int e = 0; e < n_edges; e++) {
            scanf("%d",&connected);

            if (connected > i + 1) {
                // printf("edge: %d -- %d\n", i + 1, connected);
                *edges_count += 1;
            }

            graph[i].push_back(connected);
        }
    }
    //printf("number of edges: %d\n", *edges_count);
    return;
}

void merge(int arr[], int left, int mid, int right);
void mergeSort(int arr[], int left, int right);

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
    int n_graphs;
    scanf("%d",&n_graphs);

    for (int g = 0; g < n_graphs; g++) 
    {
        int graph_size;
        int edges_count = 0;

        scanf("%d",&graph_size);
        int max_edges = (graph_size * (graph_size - 1)) / 2;

        std::vector<int>* graph = new std::vector<int> [graph_size];
        int *degrees = new int[graph_size];

        parse_graph(graph,degrees, graph_size, &edges_count);

        //testing start:
        mergeSort(degrees, 0, graph_size - 1);
        for (int i = graph_size - 1; i >= 0 ; i--) {
            printf("%d ", degrees[i]);
        }
        
        components(graph, graph_size);
        // printf("\n?");

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
        // printf("\n?\n");
        printf("\n%d\n", max_edges - edges_count);

        delete [] graph;
        delete [] degrees;
    }
    
    return 0;
}



// Function to merge two halves
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temp arrays
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    // Copy data to temp arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Merge the temp arrays back into arr[left..right]
    int i = 0; // Initial index of first subarray
    int j = 0; // Initial index of second subarray
    int k = left; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    // Free the temporary arrays
    free(L);
    free(R);
}

// l is for left index and r is right index of the sub-array of arr to be sorted
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        // Same as (left + right) / 2, but avoids overflow for large left and right
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
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
    

    printf("\n%d", components_count);

    delete [] checked;
    return;
}

void DFS(std::vector<int> graph[], int graph_size, int current, int* checked_count, bool checked[])
{
    if (checked[current]) {
        return;
    }

    // printf("checking V%d\n", current + 1);

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




