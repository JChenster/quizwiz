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
#define QNUMKEY 666222
#define USER1KEY 347216
#define USER2KEY 347840
#define SCORE1KEY 718323
#define SCORE2KEY 42069

int removeSegs(){
  int shmd;
  // removing shared memory segments
  shmd = shmget(NUMPLAYERSKEY, 16, 0);
  if (shmd == -1){
    printf("error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  shmctl(shmd, IPC_RMID, 0);
  //printf("shared memory for num players removed\n");

  shmd = shmget(TURNSKEY, 16, 0);
  if (shmd == -1){
    printf("error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  shmctl(shmd, IPC_RMID, 0);
  //printf("shared memory for turns removed\n");

  shmd = shmget(QUESTIONSKEY, 260, 0);
  if (shmd == -1){
    printf("error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  shmctl(shmd, IPC_RMID, 0);
  //printf("shared memory for questions removed\n");

  shmd = shmget(QNUMKEY, 16, 0);
  if (shmd == -1){
    printf("error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  shmctl(shmd, IPC_RMID, 0);

  shmd = shmget(USER1KEY, 16, 0);
  if (shmd == -1){
    printf("error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  shmctl(shmd, IPC_RMID, 0);

  shmd = shmget(USER2KEY, 16, 0);
  if (shmd == -1){
    printf("error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  shmctl(shmd, IPC_RMID, 0);

  shmd = shmget(SCORE1KEY, 16, 0);
  if (shmd == -1){
    printf("error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  shmctl(shmd, IPC_RMID, 0);

  shmd = shmget(SCORE2KEY, 16, 0);
  if (shmd == -1){
    printf("error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  shmctl(shmd, IPC_RMID, 0);
  
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

    // Receive username                                                                                                                                      
    char username[16];
    printf("Enter username: ");
    fgets(username, 16, stdin);
    username[strlen(username)-1] = '\0';
    printf("Welcome %s!\n", username);
    
    // creating shared memory segment for number of players
    int players_shmd = shmget(NUMPLAYERSKEY, 16, IPC_CREAT | 0644);
    if (players_shmd == -1){
      printf("error %d: %s\n", errno, strerror(errno));
      return -1;
    }

    // creating qnum shared memory seg
    int qnum_shmd = shmget(QNUMKEY, 16, IPC_CREAT | 0644);
    if (qnum_shmd == -1){
      printf("error %d: %s\n", errno, strerror(errno));
      return -1;
    }
    
    // update num of players
    int * numPlayers = shmat(players_shmd, 0, 0);
    int playerNum = * numPlayers;
    (* numPlayers)++;
    printf("There are currently %d players\n", * numPlayers);
    shmdt(numPlayers);
    printf("You are player #%d\n", playerNum + 1);

    // create shared mem for turns
    int turns_shmd = shmget(TURNSKEY, 16, IPC_CREAT | 0644);
    if (turns_shmd == -1){
      printf("error %d: %s\n", errno, strerror(errno));
      return -1;
    }

    // create shared mem for username for player 1
    int username1_shmd = shmget(USER1KEY, 16, IPC_CREAT | 0644); 
    if (username1_shmd == -1){
      printf("error %d: %s\n", errno, strerror(errno));
      return -1;
    }

    // create shared mem for username for player 2
    int username2_shmd = shmget(USER2KEY, 16, IPC_CREAT | 0644);
    if (username2_shmd == -1){
      printf("error %d: %s\n", errno, strerror(errno));
      return -1;
    }

    // create shared mem for score for player 1
    int score1_shmd = shmget(SCORE1KEY, 16, IPC_CREAT | 0644);
    if (score1_shmd == -1){
      printf("error %d: %s\n", errno, strerror(errno));
      return -1;
    }

    // create shared mem for score for player 2                                                                                                                                                            
    int	score2_shmd = shmget(SCORE2KEY, 16, IPC_CREAT | 0644);
    if (score2_shmd == -1){
      printf("error %d: %s\n", errno, strerror(errno));
      return -1;
    }
    
    int qWanted = 0;
    // receive input of number of questions desired                                                                                                                                                        
    if (playerNum == 0){
      // intialize username 2 shared mem
      char * username1 = shmat(username1_shmd, 0, 0);
      strncpy(username1, username, 16);
      shmdt(username1);
      
      int databaseMax = getMaxQuestions(f);
      printf("There are currently %d questions in the database\n", databaseMax);
      printf("As player #1, enter number of questions desired: ");
      char input[8];
      fgets(input, 8, stdin);
      qWanted = atoi(input);
      int * questionsWanted = shmat(qnum_shmd, 0, 0);
      (* questionsWanted) = qWanted;
      shmdt(questionsWanted);
    }
    // receives number of questions for player #2
    else{
      // intialize username2 shared mem
      char * username2 = shmat(username2_shmd, 0, 0);
      strncpy(username2, username, 16);
      shmdt(username2);
      // waits for player 1 to enter num questions
      while (qWanted == 0){
	int * questionsWanted = shmat(qnum_shmd, 0, 0);
	qWanted = *questionsWanted;
	shmdt(questionsWanted);
      }
      printf("Player #1 started a game with %d questions\n", qWanted);
    }


    char * user1 = shmat(username1_shmd, 0, 0);
    char * user2 = shmat(username2_shmd, 0, 0);
    printf("-----------------------------------\n");
    printf("\tStarting game!\n");
    printf("\tPlayer 1: %s\n", user1);
    printf("\tPlayer 2: %s\n", user2);    

    // create shared mem for questions
    //int qWanted = 5;
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
    // update scores on shared mem
    if (playerNum == 0){
      int * score1temp = shmat(score1_shmd, 0, 0);
      *score1temp = score;
      shmdt(score1temp);
    }
    else{
      int * score2temp = shmat(score2_shmd, 0, 0);
      *score2temp = score;
      shmdt(score2temp);
    }
    // compare scores and print winner
    int * score1 = shmat(score1_shmd, 0, 0);
    int * score2 = shmat(score2_shmd, 0, 0);
    if (*score1 > *score2){
      printf("The winner is %s with %d points!\n", user1, *score1);
    }
    else if(*score1 == *score2){
      printf("It's a tie! Both %s and %s earned %d points!\n", user1, user2, *score1);
    }
    else{
      printf("The winner is %s with %d points!\n", user2, *score2);
    }
    
    shmdt(score1);
    shmdt(score2);
    shmdt(user1);
    shmdt(user2);
    if (playerNum == 0){
      removeSegs();
    }
    return 0;
  }
}
