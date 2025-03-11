#include <stdio.h>
#include <stdlib.h>
#include "priority_queue_list.h"

void
qlist(pqueue *head, void (*print_data)(void *)) {
	pqueue *p;
	
	for (p = head; p != NULL; p = p->next) {
		printf("%d: ", p->k);
		print_data(p->data);
		printf("\n");
	}
	
}

void
qinsert(pqueue **phead, void *data, int k) {
	pqueue *new_node = malloc(sizeof(pqueue));

    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
	
    new_node->data = data;
    new_node->k = k;
    new_node->next = NULL;

    // If the list is empty or new node has higher priority than head, insert at beginning.
    if (*phead == NULL || k < (*phead)->k) {
        new_node->next = *phead;
        *phead = new_node;
    } else {
        // Find the proper insertion point.
        pqueue *current = *phead;
        while (current->next != NULL && current->next->k <= k) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}


void
qremove(pqueue **phead, int k) {
	if (*phead == NULL) {
        return;  // Queue is empty, nothing to remove.
    }
    
    pqueue *current = *phead;
    
    // Check if the head is the node to remove.
    if (current->k == k) {
        *phead = current->next;
        free(current);
        return;
    }
    
    // Traverse the list to find the node with key k.
    while (current->next != NULL && current->next->k != k) {
        current = current->next;
    }
    
    // If we found such a node, remove it.
    if (current->next != NULL) {
        pqueue *temp = current->next;
        current->next = temp->next;
        free(temp);
    }
}

