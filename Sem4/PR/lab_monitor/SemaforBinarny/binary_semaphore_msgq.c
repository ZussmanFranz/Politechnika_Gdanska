#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>     // For fork, sleep
#include <sys/wait.h>   // For wait
#include <errno.h>      // For errno

// Key for our message queue
#define SEM_KEY 1234L
#define TOKEN_MTYPE 1L // Type of message representing semaphore type

struct msg_buffer {
    long mtype;     
    char mtext[1];  
};

int sem_id = -1; // Global id of message queue

// Creates a queue and puts one token into it (semaphore = 1)
int semaphore_init() {
    sem_id = msgget(SEM_KEY, IPC_CREAT | IPC_EXCL | 0666);
    if (sem_id == -1) {
        if (errno == EEXIST) { // Already exists
            printf("Semaphore (message queue) already exists. Trying to get access.\n");
            sem_id = msgget(SEM_KEY, 0666);
            if (sem_id == -1) {
                perror("msgget (access existing)");
                return -1;
            }

            printf("Removing existing queue to re-initialize.\n");
            if (msgctl(sem_id, IPC_RMID, NULL) == -1) {
                perror("msgctl IPC_RMID on existing queue for re-init");
            }
            sem_id = msgget(SEM_KEY, IPC_CREAT | IPC_EXCL | 0666);
            if (sem_id == -1) {
                perror("msgget (re-create after trying to remove existing)");
                return -1;
            }

        } else {
            perror("msgget (create new)");
            return -1;
        }
    }

    // Put a token into queue
    struct msg_buffer token_msg;
    token_msg.mtype = TOKEN_MTYPE;
    token_msg.mtext[0] = 'T'; // Example content

    if (msgsnd(sem_id, &token_msg, 0, 0) == -1) {
        perror("msgsnd (init token)");
        // Try deleting the queue if token wasn't sent
        msgctl(sem_id, IPC_RMID, NULL);
        return -1;
    }
    printf("Semaphore initialized (msqid: %d). Token sent.\n", sem_id);
    return 0;
}

// P Operation (wait, close)
void semaphore_P() {
    if (sem_id == -1) {
        fprintf(stderr, "Semaphore not initialized.\n");
        exit(EXIT_FAILURE);
    }
    struct msg_buffer rcv_msg;
    
    if (msgrcv(sem_id, &rcv_msg, 0, TOKEN_MTYPE, 0) == -1) {
        perror("msgrcv (P operation)");
        exit(EXIT_FAILURE);
    }
    // printf("Process %d: Semaphore P (acquired token)\n", getpid());
}

// V Operation (signal, open)
void semaphore_V() {
    if (sem_id == -1) {
        fprintf(stderr, "Semaphore not initialized.\n");
        exit(EXIT_FAILURE);
    }
    struct msg_buffer token_msg;
    token_msg.mtype = TOKEN_MTYPE;
    token_msg.mtext[0] = 'T';

    if (msgsnd(sem_id, &token_msg, 0, 0) == -1) {
        perror("msgsnd (V operation)");
        exit(EXIT_FAILURE);
    }
    // printf("Process %d: Semaphore V (released token)\n", getpid());
}

void semaphore_destroy() {
    if (sem_id != -1) {
        if (msgctl(sem_id, IPC_RMID, NULL) == -1) {
            perror("msgctl (destroy semaphore)");
        } else {
            printf("Semaphore (msqid: %d) destroyed.\n", sem_id);
        }
        sem_id = -1;
    }
}


void critical_section_user(int id, int delay_before, int delay_inside) {
    printf("Process %d (PID %d): Waiting for semaphore...\n", id, getpid());
    sleep(delay_before); // Simulation of work before critical section :)

    semaphore_P();
    printf("Process %d (PID %d): Entered critical section.\n", id, getpid());
    sleep(delay_inside); // Simulation of work after critical section 
    printf("Process %d (PID %d): Leaving critical section.\n", id, getpid());
    semaphore_V();
}


int main() {
    if (semaphore_init() == -1) {
        fprintf(stderr, "Failed to initialize semaphore.\n");
        return EXIT_FAILURE;
    }

    // auto destroy semaphore if program ends
    atexit(semaphore_destroy);

    printf("Demonstrating binary semaphore with two processes.\n");

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) { // Child process
        critical_section_user(1, 1, 2); // wait: 1s, work: 2s
        _exit(EXIT_SUCCESS);
    } else { // Parent process
        critical_section_user(0, 0, 3); // wait: 0s, work: 3s

        // Wait for parent process finish
        wait(NULL);
        printf("Parent process: Child finished.\n");
    }

    printf("Main process finished.\n");
    return EXIT_SUCCESS;
}