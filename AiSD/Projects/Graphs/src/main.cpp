#include <cstdio>
#include <cstdlib>
#include <vector> //must be removed!

void parse_graph(std::vector<int> graph[], int degrees[], int start_degrees[], unsigned long long graph_size, unsigned long long* edges_count)
{
    int n_edges;
    int connected;

    for (int i = 0; i < graph_size; i++) 
    {
        scanf("%d",&n_edges);  
        degrees[i] = n_edges;
        start_degrees[i] = n_edges;

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

void merge(int arr[], int indexes_arr[], int left, int mid, int right);
void mergeSort(int arr[], int indexes_arr[], int left, int right);
void merge(int arr[], int left, int mid, int right);
void mergeSort(int arr[], int left, int right);

void components(std::vector<int> graph[], int graph_size);
void DFS(std::vector<int> graph[], int graph_size, int current, int* checked_count, bool checked[]);

bool bipartiteness(std::vector<int> graph[], int graph_size);
bool choose_side(std::vector<int> graph[], int side[], int start);

// void eccentricity_sequence(std::vector<int> graph[], unsigned long long graph_size); //TODO

// void planarity(std::vector<int> graph[], unsigned long long graph_size); //TODO

void colours_greedy(std::vector<int> graph[], unsigned long long graph_size);

void colours_LF(std::vector<int> graph[], unsigned long long graph_size, int degrees[]);

void colours_SLF(std::vector<int> graph[], unsigned long long graph_size, int degrees[]); //TODO

// void subgraphs(std::vector<int> graph[], unsigned long long graph_size); //TODO


int main()
{
    int n_graphs;
    scanf("%d",&n_graphs);

    for (int g = 0; g < n_graphs; g++) 
    {
        unsigned long long graph_size;
        unsigned long long edges_count = 0;

        scanf("%lld",&graph_size);
        unsigned long long max_edges = (graph_size * (graph_size - 1)) / 2;

        std::vector<int>* graph = new std::vector<int> [graph_size];
        int *degrees = new int[graph_size];
        int* start_degrees = new int[graph_size];
        int* degrees_indexes = new int[graph_size];
        for (int i = 0; i < graph_size; i++) {
            degrees_indexes[i] = i;
        }
        

        parse_graph(graph,degrees, start_degrees, graph_size, &edges_count);

        //testing start:
        // for (int i = graph_size - 1; i >= 0 ; i--) {
        //     printf("%d(%d) ", degrees[i], degrees_indexes[i]);
        //     // printf("%d ", degrees[i]);
        // }
        // printf("\n");
        mergeSort(degrees, degrees_indexes, 0, graph_size - 1);
        for (int i = graph_size - 1; i >= 0 ; i--) {
            // printf("%d(%d) ", degrees[i], degrees_indexes[i]);
            printf("%d ", degrees[i]);
        }
        
        components(graph, graph_size);
        // printf("\n?");

        char bipart = (bipartiteness(graph, graph_size)) ? 'T' : 'F';
        printf("%c", bipart);

        // eccentricity_sequence(graph, graph_size);
        printf("\n?");

        // planarity(graph, graph_size);
        printf("\n?");

        colours_greedy(graph, graph_size);
        // printf("\n?");

        colours_LF(graph, graph_size, degrees_indexes);
        // printf("\n?");

        colours_SLF(graph, graph_size, start_degrees);
        // printf("\n?");

        // subgraphs(graph, graph_size);
        printf("\n?");

        // printf("\n?\n");
        printf("\n%llu\n", max_edges - edges_count);

        delete [] graph;
        delete [] degrees;
        delete [] start_degrees;
    }
    
    return 0;
}



// Function to merge two halves
void merge(int arr[], int indexes_arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temp arrays
    int* L1 = (int*)malloc(n1 * sizeof(int));
    int* L2 = (int*)malloc(n1 * sizeof(int));
    int* R1 = (int*)malloc(n2 * sizeof(int));
    int* R2 = (int*)malloc(n2 * sizeof(int));


    // Copy data to temp arrays L[] and R[]
    for (int i = 0; i < n1; i++){
        L1[i] = arr[left + i];
        L2[i] = indexes_arr[left + i];
    }
    for (int j = 0; j < n2; j++){
        R1[j] = arr[mid + 1 + j];
        R2[j] = indexes_arr[mid + 1 + j];
    }

    // Merge the temp arrays back into arr[left..right]
    int i = 0; // Initial index of first subarray
    int j = 0; // Initial index of second subarray
    int k = left; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L1[i] < R1[j]) { // changed <= on < so the smallest ids will be at highest positions
            arr[k] = L1[i];
            indexes_arr[k] = L2[i];
            i++;
        } else {
            arr[k] = R1[j];
            indexes_arr[k] = R2[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L1[i];
        indexes_arr[k] = L2[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R1[j];
        indexes_arr[k] = R2[j];
        j++;
        k++;
    }

    // Free the temporary arrays
    free(L1);
    free(L2);
    free(R1);
    free(R2);
}

// l is for left index and r is right index of the sub-array of arr to be sorted
void mergeSort(int arr[], int indexes_arr[], int left, int right) {
    if (left < right) {
        // Same as (left + right) / 2, but avoids overflow for large left and right
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, indexes_arr, left, mid);
        mergeSort(arr, indexes_arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, indexes_arr, left, mid, right);
    }
}

// Function to merge two halves
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temp arrays
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R= (int*)malloc(n2 * sizeof(int));


    // Copy data to temp arrays L[] and R[]
    for (int i = 0; i < n1; i++){
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++){
        R[j] = arr[mid + 1 + j];
    }

    // Merge the temp arrays back into arr[left..right]
    int i = 0; // Initial index of first subarray
    int j = 0; // Initial index of second subarray
    int k = left; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] < R[j]) { // changed <= on < so the smallest ids will be at highest positions
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
    

    printf("\n%d\n", components_count);

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

bool bipartiteness(std::vector<int> graph[], int graph_size)
{
    int *side = new int[graph_size]();
    side[0] = 1;

    for (int v = 0; v < graph_size; v++)
    {
        if (choose_side(graph, side, v) == false) {
            delete [] side;
            return false;
        }
    }

    delete [] side;
    return true;
}

bool choose_side(std::vector<int> graph[], int side[], int start)
{
    for (int neighbour : graph[start]) 
    {
        if (side[neighbour - 1] == 0) {
            side[neighbour - 1] = (side[start] == 1) ? 2 : 1;
            if (choose_side(graph, side, neighbour - 1) == false) {
                return false;
            }
        }
        else if (side[neighbour - 1] == side[start]) {
            return false;
        }
        else {
            continue;
        }
    }

    return true;
}

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

void colours_greedy(std::vector<int> graph[], unsigned long long graph_size)
{
    int* colors = new int[graph_size]();
    int* colors_used = new int[graph_size](); // 0 - false, 1 - true
    int max_color_index = 1;

    printf("\n");


    for (unsigned long long v = 0; v < graph_size; v++) 
    {
        for (unsigned long long z = 0; z < max_color_index + 1; z++) {
            colors_used[z] = 0;
        }

        for (unsigned long long neighbour : graph[v]) 
        {
            if (colors[neighbour - 1] != 0) {
                colors_used[colors[neighbour - 1]] = 1;
                if (colors[neighbour - 1] > max_color_index) {
                    max_color_index = colors[neighbour - 1];
                }
            }    
        }
        
        for (unsigned long long i = 1; i < graph_size + 1; i++) {
            if (colors_used[i] == 0) {
                colors[v] = i;
                printf("%d ", colors[v]);
                break;
            }
        }
    }

    delete [] colors;
    delete [] colors_used;
    return;
}


void colours_LF(std::vector<int> graph[], unsigned long long graph_size, int degrees_indexes[])
{
    int* colors = new int[graph_size]();
    int* colors_used = new int[graph_size](); // 0 - false, 1 - true
    int max_color_index = 1;

    printf("\n");

    int v;

    for (unsigned long long index = graph_size; index > 0; index--) 
    {
        v = degrees_indexes[index - 1];
        // printf("current index: %d\n", v);

        for (unsigned long long z = 0; z < max_color_index + 1; z++) {
            colors_used[z] = 0;
        }

        for (unsigned long long neighbour : graph[v]) 
        {
            if (colors[neighbour - 1] != 0) {
                colors_used[colors[neighbour - 1]] = 1;
                if (colors[neighbour - 1] > max_color_index) {
                    max_color_index = colors[neighbour - 1];
                }
            }    
        }
        
        for (unsigned long long i = 1; i < graph_size + 1; i++) {
            if (colors_used[i] == 0) {
                colors[v] = i;
                break;
            }
        }
    }

    for (int i = 0; i < graph_size; i++) {
        printf("%d ", colors[i]);
    }

    delete [] colors;
    delete [] colors_used;
    return;
}

void colours_SLF(std::vector<int> graph[], unsigned long long graph_size, int degrees[])
{
    // printf("started SLF, current graph size is %lld", graph_size);
    int* colors = new int[graph_size]();
    int* colors_used = new int[graph_size](); // 0 - false, 1 - true
    int* saturation = new int[graph_size](); 
    int max_color_index = 1;
    int max_saturation;
    int max_degrees;


    //starting index
    unsigned long long index = 0;
    for (int i = 0; i < graph_size; i++) {
        if (degrees[i] > degrees[index]) {
            index = i;
        }
    }
    // colors[index] = 1;
    // saturation[index] = -1;
    // printf("\n  current index is %lld, saturations: ", index + 1);
    // for (int i = 0; i < graph_size; i++) {
    //     printf("%d ", saturation[i]);
    // }  
    // for (unsigned long long neighbor : graph[index]) {
    //     if (saturation[neighbor - 1] != -1) {
    //         saturation[neighbor - 1]++;
    //     }
    // } 

    // printf("\n");

    for (unsigned long long v = 0; v < graph_size; v++) 
    {
        max_saturation = 0;
        max_degrees = 0;

        for (unsigned long long i = 0; i < graph_size; i++) {
            if (colors[i] == 0) { // Only consider uncolored vertices
                if ((saturation[i] > max_saturation) || ((saturation[i] == max_saturation) && (degrees[i] > max_degrees))) {
                    max_saturation = saturation[i];
                    max_degrees = degrees[i];
                    index = i;
                }
            }
        }

        // printf("\n  current index is %lld, saturations: ", index + 1);
        // for (int i = 0; i < graph_size; i++) {
            // if (saturation[i] == -1) {
                // printf("- ");
            // }
            // else {
                // printf("%d ", saturation[i]);
            // }
        // }


        for (unsigned long long z = 0; z < max_color_index + 1; z++) {
            colors_used[z] = 0;
        }

        for (unsigned long long neighbour : graph[index]) 
        {
            if (colors[neighbour - 1] != 0) {
                colors_used[colors[neighbour - 1]] = 1;
                if (colors[neighbour - 1] > max_color_index) {
                    max_color_index = colors[neighbour - 1];
                }
            }    
        }
        
        for (unsigned long long i = 1; i < graph_size + 1; i++) {
            if (colors_used[i] == 0) {
                colors[index] = i;
                saturation[index] = -1;
                // printf("\n  %lld painted ", index + 1);
                break;
            }
        }

        for (unsigned long long neighbor : graph[index]) {
            if (saturation[neighbor - 1] != -1) {
                saturation[neighbor - 1]++;
            }
        }
    }

    printf("\n");
    // Print the colors assigned to each vertex
    for (int i = 0; i < graph_size; i++) {
        printf("%d ", colors[i]);
    }

    delete [] colors;
    delete [] colors_used;
    delete [] saturation;
    return;
}


// void subgraphs(std::vector<int> graph[], int graph_size)
// {
//     printf("?\n");
//     return;
// }




