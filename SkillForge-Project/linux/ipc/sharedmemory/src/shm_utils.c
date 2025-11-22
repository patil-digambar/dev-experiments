#include "shm_utils.h"

// Function to create shared memory
void create_shared_memory() {
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }
    //ftruncate to the specified size meaning set the size of the shared memory object
    if (ftruncate(shm_fd, MAX_SIZE) == -1) {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    close(shm_fd);
}

// Function to write to shared memory
void write_shared_memory(const char *message) {
    int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }
  //map the shared memory object to the process's address space using mmap  
    char *shm_ptr = mmap(NULL, MAX_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Create semaphore for synchronization
    sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0666, 0);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    // Write message to shared memory
    strncpy(shm_ptr, message, MAX_SIZE - 1);
    shm_ptr[MAX_SIZE - 1] = '\0';

    printf("Producer wrote: %s\n", message);

    // Signal the consumer that data is ready
    sem_post(sem);

    // Clean up
    sem_close(sem);
    munmap(shm_ptr, MAX_SIZE);
    close(shm_fd);
}

// Function to read from shared memory
char* read_shared_memory() {
    int shm_fd = shm_open(SHM_NAME, O_RDONLY, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    char *shm_ptr = mmap(NULL, MAX_SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Open semaphore
    sem_t *sem = sem_open(SEM_NAME, 0);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    // Wait for producer to signal data availability
    sem_wait(sem);

    // Read the message
    printf("Consumer read: %s\n", shm_ptr);

    // Cleanup
    sem_close(sem);
    munmap(shm_ptr, MAX_SIZE);
    close(shm_fd);

    return NULL; // Returning NULL as we're printing inside
}

// Function to clean up shared memory
void cleanup_shared_memory() {
    shm_unlink(SHM_NAME);
    sem_unlink(SEM_NAME);
}
