    #include <stdlib.h>
    #include <stdio.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/ipc.h>
    #include <sys/sem.h>
    #include <sys/shm.h>
    #define NUM_ELEM 15 /* Number of elements in shared memory buffer */
    #define SEM_MUTEX 0
    #define SEM_EMPTY 1
    #define SEM_FULL 2
    FILE* fp;
    int rc, semID, shmID, status, i, x;
    char elem;
    union semun
    {
    int val;
    struct semid_ds *buf;
    ushort *array;
    } seminfo;
    struct sembuf WaitMutex={SEM_MUTEX, -1, 0};
    struct sembuf SignalMutex={SEM_MUTEX, 1, 0};
    struct sembuf WaitEmpty={SEM_EMPTY, -1, 0};
    struct sembuf SignalEmpty={SEM_EMPTY, 1, 0};
    struct sembuf WaitFull={SEM_FULL, -1, 0};
    struct sembuf SignalFull={SEM_FULL, 1, 0};
    struct shmid_ds shminfo;
    char *shmPtr;
    void initialize();
    void producer();
    void consumer();
    main()
    {
    /* Open file */
    fp= fopen("mytest.dat", "r");
    /* Initialize shared memory and semaphores */
    initialize();
    /* Start a child process and proceed accordingly*/
    if (fork()==0)
    {
    /* Child becomes the consumer */
    consumer();
    /* Child quits after consuming 26 characters */
    exit(0);
    }
    else
    {
    /* Parent becomes the producer */
    producer();
    /* Wait for child to finish */
    //wait(&status);
    /* Remove shared memory */
    shmctl(shmID, IPC_RMID, &shminfo);
    /* Remove semaphores */
    semctl(semID, SEM_MUTEX, IPC_RMID, seminfo);
    /* Close file */
    fclose(fp);
    /* Parent is done cleaning up, so now quits */
    exit(0);
    }
    }
    void initialize()
    {
    /* Init semaphores */
    /* Three semaphores (Empty, Full, Mutex) are created in one set */
    semID=semget(IPC_PRIVATE, 3, 0666 | IPC_CREAT);
    /* Init Mutex to one, allowing access to critical section */
    seminfo.val=1;
    semctl(semID, SEM_MUTEX, SETVAL, seminfo);
    /* Init Empty to number of elements in shared memory (circular buffer) */
    seminfo.val=NUM_ELEM;
    semctl(semID, SEM_EMPTY, SETVAL, seminfo);
    /* Init Full to zero, no elements are produced yet */
    seminfo.val=0;
    semctl(semID, SEM_FULL, SETVAL, seminfo);
    /* Init Shared memory */
    shmID=shmget(IPC_PRIVATE, NUM_ELEM, 0666 | IPC_CREAT);
    }
    void producer()
    {
    /* attach shared memory to process */
    shmPtr=(char*)shmat(shmID, 0, SHM_W);
    while((x = fgetc(fp)) != EOF)
    {
    /* Wait(Empty) - pause if no empty spots in circular buffer (i.e. all filled) */
    semop(semID, &WaitEmpty, 1);
    elem = x;
    printf("Produced elem '%c'\n", elem);
    /* Wait(Mutex) - don't touch shared memory while consumer is using it */
    semop(semID, &WaitMutex, 1);
    /* Put element into shared memory buffer (circular buffer) */
    *(shmPtr + (i%NUM_ELEM))=elem;
    /* Signal(Mutex) - allow consumer to access shared memory now */
    semop(semID, &SignalMutex, 1);
    /* Signal(Full) - record one more filled spot in circular buffer */
    semop(semID, &SignalFull, 1);
    }
    }
    void consumer()
    {
    /* attach shared memory to process */
    shmPtr=(char*)shmat(shmID, 0, SHM_R);
    while((elem != '*'))
    {
    /* Wait(Full) - pause if no filled spots in circular buffer (i.e. all empty) */
    semop(semID, &WaitFull, 1);
    /* Wait(Mutex) - don't touch shared memory while producer is using it */
    semop(semID, &WaitMutex, 1);
    /* Get element from the shared memory buffer (circular buffer) */
    elem=*(shmPtr + (i%NUM_ELEM));
    /* Signal(Mutex) - allow producer to access shared memory now */
    semop(semID, &SignalMutex, 1);
    /* Display character */
    printf("Consumed elem '%c'\n", elem);
    /* Signal(Empty) - record one more empty spot in circular buffer */
    semop(semID, &SignalEmpty, 1);
    }
    }
