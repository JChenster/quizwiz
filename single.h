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


#define SEMKEY 24601
int semd, fd;
struct sembuf sb;
union semun us;

int game(char * f, int n);
/*
int createSemaphore();
int viewLeaderboard();
int updateLeaderboard(char * username, int score);
*/
