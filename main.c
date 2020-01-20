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
#include "single.h"
#include "multi.h"
#include "parse.h"

#define NUMPLAYERSKEY 555222
#define TURNSKEY 444222

int removeSegs(){
  int shmd;
  // removing shared memory segments                                                                                                                                               
    shmd = shmget(NUMPLAYERSKEY, 64, 0);
    if (shmd == -1){
      printf("error %d: %s\n", errno, strerror(errno));
      return -1;
    }
    shmctl(shmd, IPC_RMID, 0);
    printf("shared memory for num players removed\n");


    shmd = shmget(TURNSKEY, 64, 0);
    if (shmd == -1){
      printf("error %d: %s\n", errno, strerror(errno));
      return -1;
    }
    shmctl(shmd, IPC_RMID, 0);
    printf("shared memory for turns removed\n");
    return 0;
}


int main() {
  printf("------------------------------------------------------------\n");
  printf("Welcome to QuizWiz!\n");
  printf("Press 'S' for single player mode OR 'M' for multiplayer mode\n");
  printf("------------------------------------------------------------\n");
  int mode = getchar();
  char * f = "questions.txt";
  
  if ('S' == mode || 's' == mode){
  while ( ( mode = getchar() ) != '\n' && mode != EOF )
    ;
  printf("-----------------------------------------\n");
  printf("Welcome to the single player QuizWiz mode!\n");
  printf("-----------------------------------------\n");

  
  // Receive username
  char username[16];
  printf("Enter username: ");
  fgets(username, 16, stdin);
  username[strlen(username)-1] = '\0';
  printf("Welcome %s!\n", username);

  // Sets up semaphores
  us.val = 1;
  sb.sem_num = 0;
  sb.sem_op = -1;
  createSemaphore();

  // receive input of number of questions desired
  int databaseMax = getMaxQuestions(f);
  printf("There are currently %d questions in the database\n", databaseMax);
  printf("Enter number of questions desired: ");
  char input[8];
  fgets(input, 8, stdin);
  int n = atoi(input);
  int score = singleGame(f, n);

  updateLeaderboard(username, score);
  viewLeaderboard();
  removeSemaphore();
  }
  if ('M' == mode || 'm' == mode){
    while ( ( mode = getchar() ) != '\n' && mode != EOF )
      ;

    // creating shared memory segment
    int shmd;
    shmd = shmget(NUMPLAYERSKEY, 64, IPC_CREAT | 0644);
    if (shmd == -1){
      printf("insert error msg\n");
      return -1;
    }
    printf("shared memory for number of players created\n");

    // adjust number of players
    printf("shmget id is %d\n", shmd);
    int * numPlayers = shmat(shmd, 0, 0);
    printf("Players before entrance: %d\n", * numPlayers);
    int playerNum = * numPlayers;
    (* numPlayers)++;
    printf("Now there are %d players\n", * numPlayers);
    shmdt(numPlayers);
    
    shmd = shmget(TURNSKEY, 64, IPC_CREAT | 0644);
    if (shmd == -1){
      printf("error %d: %s\n", errno, strerror(errno));
      return -1;
    }
    printf("shared memory for turns created\n");

    printf("I am the %dth player\n", playerNum);
    //removeSegs();
    /*
    // removing shared memory segments
    shmd = shmget(NUMPLAYERSKEY, 64, 0);
    if (shmd == -1){
      printf("error %d: %s\n", errno, strerror(errno));
      return -1;
    }
    shmctl(shmd, IPC_RMID, 0);
    printf("shared memory for num players removed\n");


    shmd = shmget(TURNSKEY, 64, 0);
    if (shmd == -1){
      printf("error %d: %s\n", errno, strerror(errno));
      return -1;
    }
    shmctl(shmd, IPC_RMID, 0);
    printf("shared memory for turns removed\n");
    */
  }
  
  return 0;
}
/*
int removeSegs(){
  int shmd;
  // removing shared memory segments                                                                                                                                             
    shmd = shmget(NUMPLAYERSKEY, 64, 0);
    if (shmd == -1){
      printf("error %d: %s\n", errno, strerror(errno));
      return -1;
    }
    shmctl(shmd, IPC_RMID, 0);
    printf("shared memory for num players removed\n");


    shmd = shmget(TURNSKEY, 64, 0);
    if (shmd == -1){
      printf("error %d: %s\n", errno, strerror(errno));
      return -1;
    }
    shmctl(shmd, IPC_RMID, 0);
    printf("shared memory for turns removed\n");
    return 0;
}
*/
