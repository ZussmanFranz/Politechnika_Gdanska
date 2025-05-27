#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/shm.h>

#define MONITOR_KEY 2345L
#define ENTRY_MTYPE 1L
#define WAIT_MTYPE 2L

struct msg_buffer {
    long mtype;
    int count; // Number of waiting processes
};

int monitor_id = -1;

// Monitor initialization: puts token on input queue
int monitor_init() {
    monitor_id = msgget(MONITOR_KEY, IPC_CREAT | IPC_EXCL | 0666);
    if (monitor_id == -1) {
        if (errno == EEXIST) {
            monitor_id = msgget(MONITOR_KEY, 0666);
            if (monitor_id == -1) return -1;
            msgctl(monitor_id, IPC_RMID, NULL);
            monitor_id = msgget(MONITOR_KEY, IPC_CREAT | IPC_EXCL | 0666);
            if (monitor_id == -1) return -1;
        } else {
            return -1;
        }
    }
    struct msg_buffer token = {ENTRY_MTYPE, 0};
    if (msgsnd(monitor_id, &token, sizeof(int), 0) == -1) {
        msgctl(monitor_id, IPC_RMID, NULL);
        return -1;
    }
    return 0;
}

void enter_monitor() {
    struct msg_buffer msg;
    msgrcv(monitor_id, &msg, sizeof(int), ENTRY_MTYPE, 0);
}

void exit_monitor() {
    struct msg_buffer msg = {ENTRY_MTYPE, 0};
    msgsnd(monitor_id, &msg, sizeof(int), 0);
}

void monitor_wait() {
    struct msg_buffer msg = {WAIT_MTYPE, 1};
    msgsnd(monitor_id, &msg, sizeof(int), 0);
    exit_monitor(); // left monitor
    msgrcv(monitor_id, &msg, sizeof(int), WAIT_MTYPE, 0); // wait for notify
    enter_monitor(); // back to monitor
}

// Notify on cond. var.
void monitor_notify() {
    struct msg_buffer msg;
    if (msgrcv(monitor_id, &msg, sizeof(int), WAIT_MTYPE, IPC_NOWAIT) != -1) {
        msgsnd(monitor_id, &msg, sizeof(int), 0);
    } else {
        // No one is waiting, release the monitor for the next process
        exit_monitor();
    }
}

void monitor_destroy() {
    if (monitor_id != -1) {
        msgctl(monitor_id, IPC_RMID, NULL);
        monitor_id = -1;
    }
}

// Attach to shared memory for counter
int *get_shared_counter(int *shmid_out) {
    int shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }
    if (shmid_out) *shmid_out = shmid;
    int *ptr = (int*)shmat(shmid, NULL, 0);
    if (ptr == (void*)-1) {
        perror("shmat");
        exit(1);
    }
    *ptr = 0;
    return ptr;
}

void detach_and_remove_shm(int *ptr, int shmid) {
    shmdt(ptr);
    shmctl(shmid, IPC_RMID, NULL);
}

// Updated monitor_func for shared counter and process id
void monitor_func(int *counter, int proc_id, int use_wait, int do_notify) {
    enter_monitor();
    printf("[PID %d] Proc %d: in monitor. Counter: %d\n", getpid(), proc_id, *counter);
    if (use_wait && *counter == 0) {
        printf("[PID %d] Proc %d: waits (monitor_wait)\n", getpid(), proc_id);
        monitor_wait();
        printf("[PID %d] Proc %d: got back from wait\n", getpid(), proc_id);
    }
    (*counter)++;
    printf("[PID %d] Proc %d: incremented counter to %d\n", getpid(), proc_id, *counter);
    sleep(1);
    if (do_notify) {
        printf("[PID %d] Proc %d: notifies (monitor_notify)\n", getpid(), proc_id);
        monitor_notify();
    } else {
        exit_monitor();
    }
    printf("[PID %d] Proc %d: finished.\n", getpid(), proc_id);
}

int main() {
    if (monitor_init() == -1) {
        perror("monitor_init");
        return 1;
    }
    atexit(monitor_destroy);
    int shmid;
    int *counter = get_shared_counter(&shmid);
    int n = 4; // number of processes
    pid_t pids[4];
    for (int i = 0; i < n; ++i) {
        pids[i] = fork();
        if (pids[i] < 0) {
            perror("fork");
            // Clean up and exit if fork fails
            for (int j = 0; j < i; ++j) waitpid(pids[j], NULL, 0);
            detach_and_remove_shm(counter, shmid);
            return 1;
        }
        if (pids[i] == 0) {
            // Child process: break the loop so only one child runs its code
            int use_wait = (i == 0);
            int do_notify = (i == 1);
            monitor_func(counter, i, use_wait, do_notify);
            shmdt(counter);
            _exit(0);
        }
    }
    // Parent waits for all
    for (int i = 0; i < n; ++i) waitpid(pids[i], NULL, 0);
    printf("[Parent] Final counter value: %d\n", *counter);
    detach_and_remove_shm(counter, shmid);
    return 0;
}
