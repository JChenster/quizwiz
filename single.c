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

  // Sets up semaphores
  us.val = 1;
  sb.sem_num = 0;
  sb.sem_op = -1;
  createSemaphore();

  // receive input of number of questions desired
  printf("There are currently %d questions in the database\n", getMaxQuestions(f));
  printf("Enter number of questions desired: ");
  char input[8];
  fgets(input, 8, stdin);
  int n = atoi(input);
  printf("n is %d\n", n);
  game(f, n);
  removeSemaphore();
  //viewLeaderboard();
}

int game(char * f, int n){
  char ** q = getNQuestions(f, n);
  int response;
  int score = 0;
  for (int i = 0; i<n; i++){
    // parse current question
    char * cur = q[i];
    //struct question q = parseSingleQuestion(cur);
    struct question q = parseSingleQuestion(cur);
    printf("question : %s\n", q.question);
    printf("-----------------------------------------\n");
    printf("%d. %s\nA. %s\nB. %s\nC. %s\nD. %s\n", i + 1, q.question, q.a, q.b, q.c, q.d);

    // receive and parse response
    printf("Enter answer: ");
    response = getchar();
    if ('a' + q.ans - 1 == response || 'A' + q.ans - 1 == response){
      score++;
      printf("Correct! Your current score is: %d\n", score);
      while ( ( response = getchar() ) != '\n' && response != EOF )
        ;
    }
    else{
      printf("Incorrect! Game over! Your score is %d\n", score);
      break;
    }
  }
  return score;
}

int createSemaphore(){
  semd = semget(SEMKEY, 1, IPC_CREAT | IPC_EXCL | 0644);
  if (semd == -1) {
    printf("error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  semctl(semd, 0, SETVAL, us);
  printf("semaphore created\n");
  return 0;
}

int removeSemaphore(){
  semd = semget(SEMKEY, 1, 0);
  if (semd == -1) {
    printf("error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  semop(semd, &sb, 1);
  semctl(semd, IPC_RMID, 0);
  printf("semaphore removed\n");
}

int viewLeaderboard(){
  fd = open("leaderboard.txt", O_RDONLY);
  if (fd == -1){
    printf("error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  printf("Leaderboard:\n");

  struct stat md;
  stat("leaderboard.txt", &md);
  int size = md.st_size;
  char buff[size];
  buff[0] = '\0';
  read(fd, buff, size);
  if (strlen(buff) != 0) {
    *(strrchr(buff, '\n') + 1) = '\0';
  }
  printf("%s\n",buff);
  close(fd);
  return 0;
}

int updateLeaderboard(char * username, int score){
  return 0;
}
