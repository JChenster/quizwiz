#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>

#define SEMKEY 345101
extern int semd;
extern struct sembuf sb;
extern union semun us;

union semun {
  int              val;    /* Value for SETVAL */
  struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
  unsigned short  *array;  /* Array for GETALL, SETALL */
  struct seminfo  *__buf;  /* Buffer for IPC_INFO
                              (Linux-specific) */
};

int singleGame(char* f, int n);;
int createSemaphore();
int removeSemaphore();
int viewLeaderboard();
int updateLeaderboard(char * username, int score);
int resetLeaderboard();
