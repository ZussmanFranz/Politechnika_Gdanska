#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

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
    }
}

void monitor_destroy() {
    if (monitor_id != -1) {
        msgctl(monitor_id, IPC_RMID, NULL);
        monitor_id = -1;
    }
}

// Monitor demo
void monitor_func(int *counter, int use_wait) {
    enter_monitor();
    printf("Process %d is in monitor. Counter: %d\n", getpid(), *counter);
    if (use_wait && *counter == 0) {
        printf("Process %d waits\n", getpid());
        monitor_wait();
        printf("Process %d got back from wait\n", getpid());
    }
    (*counter)++;
    sleep(1);
    printf("Process %d is finished. Counter: %d\n", getpid(), *counter);
    if (use_wait) {
        monitor_notify();
    } else {
        exit_monitor();
    }
}

int main() {
    if (monitor_init() == -1) {
        perror("monitor_init");
        return 1;
    }
    atexit(monitor_destroy);
    int counter = 0;
    pid_t pid = fork();
    if (pid == 0) {
        monitor_func(&counter, 1); // first process uses wait/notify
        _exit(0);
    } else {
        sleep(1);
        monitor_func(&counter, 0); // second only increments
        wait(NULL);
    }
    return 0;
}
