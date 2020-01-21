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
#define QUESTIONSKEY 333222

int removeSegs(){
  int shmd;
  // removing shared memory segments
  shmd = shmget(NUMPLAYERSKEY, 64, 0);
  if (shmd == -1){
    printf("error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  shmctl(shmd, IPC_RMID, 0);
  //printf("shared memory for num players removed\n");

  shmd = shmget(TURNSKEY, 64, 0);
  if (shmd == -1){
    printf("error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  shmctl(shmd, IPC_RMID, 0);
  //printf("shared memory for turns removed\n");

  shmd = shmget(QUESTIONSKEY, 64, 0);
  if (shmd == -1){
    printf("error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  shmctl(shmd, IPC_RMID, 0);
  //printf("shared memory for questions removed\n");
  return 0;
}

int main() {
  printf("------------------------------------------------------------\n");
  printf("\t\tWelcome to QuizWiz!\n");
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
    printf("-----------------------------------------\n");
    printf("Welcome to the multi player QuizWiz mode!\n");
    printf("-----------------------------------------\n");

    // creating shared memory segment for number of players
    int players_shmd = shmget(NUMPLAYERSKEY, 64, IPC_CREAT | 0644);
    if (players_shmd == -1){
      printf("error %d: %s\n", errno, strerror(errno));
      return -1;
    }
    printf("shared memory for number of players created\n");

    // update num of players
    int * numPlayers = shmat(players_shmd, 0, 0);
    int playerNum = * numPlayers;
    (* numPlayers)++;
    printf("There are currently %d players\n", * numPlayers);
    shmdt(numPlayers);
    printf("You are player #%d\n", playerNum + 1);

    // create shared mem for turns
    int turns_shmd = shmget(TURNSKEY, 64, IPC_CREAT | 0644);
    if (turns_shmd == -1){
      printf("error %d: %s\n", errno, strerror(errno));
      return -1;
    }

    // create shared mem for questions
    int qWanted = 5;
    int q_shmd = shmget(QUESTIONSKEY, 260, IPC_CREAT | 0644);
    if (q_shmd == -1){
      printf("error %d: %s\n", errno, strerror(errno));
      return -1;
    }

    // initialize question bank
    char ** questionBank;
    if (playerNum == 0){
      questionBank = getNQuestions(f, qWanted);
      //printf("initialized question bank\n");
    }

    // run turns
    int * curTurns;
    int response;
    int score = 0;
    struct question q;
    while (1){
      curTurns = shmat(turns_shmd, 0, 0);
      if (* curTurns < qWanted * 2){
        // Your turn
        if (* curTurns % 2 == playerNum){

          // load new question into shared memory
          if (*curTurns % 2 == 0){
            char * curQue = questionBank[*curTurns / 2];
            char * cur = shmat(q_shmd, 0, 0);
            strncpy(cur, curQue, 260);
            shmdt(cur);
            q = parseSingleQuestion(curQue);
          }
          else{
            char * cur = shmat(q_shmd, 0, 0);
            q = parseSingleQuestion(cur);
            shmdt(cur);
          }
          //struct question q = parseSingleQuestion(cur);

          printf("-----------------------------------\n");
          printf("%d. %s\nA. %s\nB. %s\nC. %s\nD. %s\n", (*curTurns / 2) + 1, q.question, q.a, q.b, q.c, q.d);
          printf("-----------------------------------\n");

          // receive and parse response
          printf("Enter answer: ");
          response = getchar();
          if ('a' + q.ans - 1 == response || 'A' + q.ans - 1 == response){
            score++;
            printf("Correct! Your current score is: %d\n", score);
          }
          else{
            printf("Incorrect! Your current score is %d\n", score);
          }
          while ( ( response = getchar() ) != '\n' && response != EOF )
          ;
          (*curTurns)++;
        }
        shmdt(curTurns);
      }
      else{
        shmdt(curTurns);
        break;
      }

    }
    printf("Your final score is %d\n", score);
    if (playerNum == 0){
      removeSegs();
    }
    return 0;
  }
}
