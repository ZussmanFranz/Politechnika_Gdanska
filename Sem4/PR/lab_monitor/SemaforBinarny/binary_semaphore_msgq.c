#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h> // For fork, sleep
#include <sys/wait.h> // For wait
#include <errno.h>   // For errno

// Klucz do naszej kolejki komunikatów (kanału)
#define SEM_KEY 1234L
#define TOKEN_MTYPE 1L // Typ komunikatu reprezentującego token semafora

// Struktura komunikatu (choć treść nie jest istotna dla semafora binarnego)
struct msg_buffer {
    long mtype;      // Typ komunikatu
    char mtext[1];   // Minimalna treść (nieużywana, ale wymagana)
};

int sem_id = -1; // Globalny identyfikator kolejki komunikatów

// Inicjalizacja semafora binarnego
// Tworzy kolejkę i umieszcza w niej jeden token (semafor = 1)
int semaphore_init() {
    sem_id = msgget(SEM_KEY, IPC_CREAT | IPC_EXCL | 0666);
    if (sem_id == -1) {
        if (errno == EEXIST) { // Kolejka już istnieje
            printf("Semaphore (message queue) already exists. Trying to get access.\n");
            sem_id = msgget(SEM_KEY, 0666);
            if (sem_id == -1) {
                perror("msgget (access existing)");
                return -1;
            }
            // W tym przypadku nie wiemy, czy token jest w kolejce.
            // Dla prostoty, jeśli istnieje, zakładamy, że jest już zainicjalizowana
            // lub inny proces ją kontroluje. W bardziej rozbudowanym systemie
            // można by sprawdzić stan lub usunąć i stworzyć na nowo.
            // Na potrzeby tego zadania, jeśli istnieje, po prostu ją pobieramy.
            // Ale dla czystej inicjalizacji lepiej usunąć starą, jeśli chcemy zagwarantować token.
            // Spróbujmy usunąć i stworzyć na nowo, aby mieć pewność stanu.
            printf("Removing existing queue to re-initialize.\n");
            if (msgctl(sem_id, IPC_RMID, NULL) == -1) {
                perror("msgctl IPC_RMID on existing queue for re-init");
                // Kontynuujemy próbę utworzenia, może się udać jeśli RMID zadziałało asynchronicznie
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

    // Umieść token w kolejce
    struct msg_buffer token_msg;
    token_msg.mtype = TOKEN_MTYPE;
    token_msg.mtext[0] = 'T'; // Dowolna treść

    // Rozmiar mtext (bez mtype)
    if (msgsnd(sem_id, &token_msg, 0, 0) == -1) { // rozmiar 0, bo treść nie ma znaczenia
        perror("msgsnd (init token)");
        // Spróbuj usunąć kolejkę, jeśli token nie mógł być wysłany
        msgctl(sem_id, IPC_RMID, NULL);
        return -1;
    }
    printf("Semaphore initialized (msqid: %d). Token sent.\n", sem_id);
    return 0;
}

// Operacja P (wait, opuść)
void semaphore_P() {
    if (sem_id == -1) {
        fprintf(stderr, "Semaphore not initialized.\n");
        exit(EXIT_FAILURE);
    }
    struct msg_buffer rcv_msg;
    // Odbierz komunikat typu TOKEN_MTYPE (blokująco)
    // Rozmiar 0, bo nie oczekujemy konkretnej treści, tylko samego faktu otrzymania komunikatu
    if (msgrcv(sem_id, &rcv_msg, 0, TOKEN_MTYPE, 0) == -1) {
        perror("msgrcv (P operation)");
        // W przypadku błędu tutaj, sytuacja jest poważna, np. kolejka została usunięta
        exit(EXIT_FAILURE);
    }
    // printf("Process %d: Semaphore P (acquired token)\n", getpid());
}

// Operacja V (signal, podnieś)
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
        // Błąd tutaj może oznaczać np. zapełnienie kolejki (mało prawdopodobne dla semafora binarnego)
        // lub usunięcie kolejki.
        exit(EXIT_FAILURE);
    }
    // printf("Process %d: Semaphore V (released token)\n", getpid());
}

// Usunięcie semafora (kolejki komunikatów)
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

// Funkcja wykonywana przez procesy potomne (lub wątki w innym kontekście)
void critical_section_user(int id, int delay_before, int delay_inside) {
    printf("Process %d (PID %d): Waiting for semaphore...\n", id, getpid());
    sleep(delay_before); // Symulacja pracy przed sekcją krytyczną

    semaphore_P();
    printf("Process %d (PID %d): Entered critical section.\n", id, getpid());
    sleep(delay_inside); // Symulacja pracy w sekcji krytycznej
    printf("Process %d (PID %d): Leaving critical section.\n", id, getpid());
    semaphore_V();
}


int main() {
    if (semaphore_init() == -1) {
        fprintf(stderr, "Failed to initialize semaphore.\n");
        return EXIT_FAILURE;
    }

    // Użyj atexit do automatycznego usunięcia semafora przy zakończeniu programu
    // (nawet w przypadku błędu, o ile nie jest to SIGKILL)
    atexit(semaphore_destroy);

    printf("Demonstrating binary semaphore with two processes.\n");

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) { // Proces potomny
        critical_section_user(1, 1, 2); // Potomek, czeka 1s, pracuje 2s
        exit(EXIT_SUCCESS);
    } else { // Proces macierzysty
        critical_section_user(0, 0, 3); // Rodzic, nie czeka, pracuje 3s

        // Czekaj na zakończenie procesu potomnego
        wait(NULL);
        printf("Parent process: Child finished.\n");
    }

    // semaphore_destroy() zostanie wywołane automatycznie przez atexit
    printf("Main process finished.\n");
    return EXIT_SUCCESS;
}