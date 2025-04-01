#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <pqueue.h>
#include <stdbool.h>

char *filename = "queue.dat";

int itemId = 0;
const int maxProduced = 10;

typedef struct item item;
struct item {
	int id;
};


item* produce() {
	int time = rand() % 5 + 1;
	item *it = (item *)malloc(sizeof(item));
	
	sleep(time);
	it->id = itemId;
	itemId += 1;
	return it;
}

void consume(item *it) {
	int time = rand() % 5 + 1;
	sleep(time);
	free(it);
}

void producer(pid_t childPid, pqueue* qu) {
	printf("\t\tproducer %d initialised by %d\n", getpid(), getppid());
	while(true){
		item* it = produce();
		printf("\tproducer %d produced item %d\n", getpid(), it->id);

		// If number of items produced by this producer exceedes threshold, it stops working
		if (it->id > maxProduced){
			printf("\t\tproducer %d (ppid: %d\n) stoped working", getpid(), getppid());
		}
	}
}

void consumer() {
}

int main(int argc, char **argv) {
	pid_t pid;
	pqueue *qu = NULL;
	/* watch -n 1 ps -l --forest */
	
	/* create empty queue */
	qserialize(qu, sizeof(item), filename);

	item* it;
	it->id = 228;
	qinsert(&qu, it, 1);
	
	qunserialize(&qu, sizeof(item), filename);
	return 0;
	

	if (fork() == 0){
		printf("First child process initialised: %d (ppid: %d)\n", getpid(), getppid());
		producer(getpid(), qu);
	} else {
		if (fork() == 0){
			printf("Second child process initialised: %d (ppid: %d)\n", getpid(), getppid());
			producer(getpid(), qu);
		} else {
			printf("Parent process done\n");
		}
	}

	return 0;
}

