#include "single.h"
#include "parse.h"

int main(){
  printf("-----------------------------------------\n");
  printf("Welcome to the single player QuizWiz mode!\n");
  printf("-----------------------------------------\n");

  char *f = "questions.txt";

  // Receive username
  printf("Enter username: ");
  char username[16];
  fgets(username, 16, stdin);
  username[strlen(username)-1] = '\0';
  printf("Welcome %s!\n", username);

  // receive input of number of questions desired
  printf("There are currently %d questions in the database\n", getMaxQuestions(f));
  printf("Enter number of questions desired: ");
  char input[2];
  fgets(input, 2, stdin);
  int n = atoi(input);
  game(f, n);
}

int game(char * f, int n){
  char ** q = getNQuestions(f, n);
  int response;
  int score = 0;
  for (int i = 0; i<n; i++){
    // parse current question
    char * cur = q[i];
    struct question q = parseSingleQuestion(cur);
    printf("-----------------------------------------\n");
    printf("%d. %s\nA. %s\nB. %s\nC. %s\nD. %s\n", i + 1, q.question, q.a, q.b, q.c, q.d);

    // receive and parse response
    while ( ( response = getchar() ) != '\n' && response != EOF )
      ;
    printf("Enter answer: ");
    response = getchar();
    if ('a' + q.ans - 1 == response || 'A' + q.ans - 1 == response){
      score++;
      printf("Correct! Your current score is: %d\n", score);
    }
    else{
      printf("Incorrect! Game over! Your score is %d\n", score);
      break;
    }
  }
  return score;
}

int viewLeaderboard(){
  fd = open("leaderboard.txt", O_RDONLY);
  if (fd == -1){
    printf("error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  printf("Leaderboard:\n");
  char buff[SEG_SIZE];
  buff[0] = '\0';
  read(fd, buff, SEG_SIZE);
  if (strlen(buff) != 0) {
    *(strrchr(buff, '\n') + 1) = '\0';
  }
  printf("%s\n",buff);
  close(fd);
}

int updateLeaderboard(char * username, int score){
  
}
