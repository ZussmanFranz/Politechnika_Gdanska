#include <cstdio>
#include <iostream>

struct node
{
    int number;
    bool checked = false;
    int* connected;
    int graph_size;
};


// void PrintGraphArray(node* graph, int size)
// {
//     for (int i = 0; i < size; i++) {
//         for (int j = 0; j < size; j++) {
//             std::cout << graph[i].connected[j] << " ";
//         }
//         std::cout << '\n';
//     }

//     return;
// }

bool FindCycle(node* current ,node* graph, int* count)
{
    if (current->number == 0) {
        return true;
    }
    else {
        *count = *count + 1;
        current->checked = true;

        for (int i = 0; i < current->graph_size; i++) {
            if ((current->connected[i] == 1) && (graph[i].checked == false)) {
                if (FindCycle(&graph[i], graph, count) == false) {
                    return false;
                }
            }
        }
        return true;
    }
}

int main()
{
    int n_graphs;
    std::cin >> n_graphs;

    for (int g = 0; g < n_graphs; g++) 
    {
        bool failed = false;

        int n_nodes;
        std::cin >> n_nodes;
        getchar(); //skips space

        node* nodes = new node[n_nodes];

        for (int n = 0; n < n_nodes; n++) {
            nodes[n].number = n;
            nodes[n].connected = new int[n_nodes];
            nodes[n].graph_size = n_nodes;

            char c;
            for (int nn = 0; nn < n_nodes; nn++) {
                c = getchar();
                if (c == '1') {
                    nodes[n].connected[nn] = 1;
                }
                else {
                    nodes[n].connected[nn] = 0;
                }
            }
        }

        node* current = &nodes[0];

        // PrintGraphArray(nodes, n_nodes);
        // std::cout << '\n';

        int count = 0;

        for (int i = 0; i < n_nodes; i++) {
            if (nodes[0].connected[i] == 1) {
                if (FindCycle(&nodes[i], nodes, &count) == false) {
                    failed = true;
                    break;
                }
            }
        }

        if (failed) {
            std::cout << 0 << '\n';
            delete [] nodes;
            continue;
        }

        if (count != n_nodes) {
            //std::cout << "real count is " << count << '\n';
            std::cout << 0 << '\n';
        }
        else {
            std::cout << 1 << '\n';
        }

        delete [] nodes;
    }

    return 0;
}