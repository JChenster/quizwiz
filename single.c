#include "single.h"
#include "parse.h"

int main(){
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
  printf("There are currently %d questions in the database\n", getMaxQuestions(f));
  printf("Enter number of questions desired: ");
  char input[8];
  fgets(input, 8, stdin);
  int n = atoi(input);
  int score = game(n);
  //resetLeaderboard();
  viewLeaderboard();
  updateLeaderboard(username, score);
  viewLeaderboard();
  removeSemaphore();
}

int game(int n){
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

  // opens file
  int fd = open("leaderboard.txt", O_RDONLY);
  if (fd == -1){
    printf("error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  printf("Leaderboard:\n");

  /*
  struct stat md;
  stat("leaderboard.txt", &md);
  char temp[8];
  sprintf(temp, "%ld", md.st_size);
  int size = atoi(temp);
  printf("size: %d\n", size);
  */
  // reads the contents of the file
  int size = 1000;
  char buff[size];
  read(fd, buff, size);

  // removes weird stuff at the end
  if (strlen(buff) != 0) {
    *(strrchr(buff, '\n') + 1) = '\0';
  }
  printf("%s\n",buff);
  close(fd);
  return 0;
}

int updateLeaderboard(char * username, int score){
  printf("trying to get in\n");
  semd = semget(SEMKEY, 1, 0);
  if (semd == -1) {
    printf("error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  semop(semd, &sb, 1);

  // creating temp file
  int fd = open("temp.txt", O_CREAT | O_TRUNC | O_RDWR, 0644);
  if (fd == -1){
    printf("error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  close(fd);

  // opening temp for writing
  fd = open("temp.txt", O_WRONLY | O_APPEND);
  if (fd == -1){
    printf("error %d: %s\n", errno, strerror(errno));
    return -1;
  }

  char * filename = "leaderboard.txt";
  int file_length = getMaxQuestions(filename);

  if (file_length == 0){
    char new[100];
    int written = sprintf(new, "%s\t\t%d\n", username, score);
    write(fd, new, written);
  }
  else{
    // opens file
    printf("got here\n");
    FILE *fp;
    char textqs[MAXCHAR];
    fp = fopen(filename, "r");
    if (fp == NULL) {
      printf("Could not open file %s", filename);
      return -1;
    }

    char * entry;
    char delim[] = "\t\t";
    char * cur_user;
    printf("got here part 2\n");
    for (int i = 0; i < file_length; i++) {
      // obtains username and score of player line by line
      entry = fgets(textqs, MAXCHAR, fp);
      char temp[MAXCHAR];
      strncpy(temp, entry, MAXCHAR);
      char temp2[16];
      strncpy(temp2, strtok(temp, delim), 16);
      strncpy(cur_user, temp2, 16);
      int cur_score = atoi(strtok(0, delim));
      printf("%s : %d\n", cur_user, cur_score);

      // if score to add is greater than current score
      if (score > cur_score){
        char new[100];
        int written = sprintf(new, "%s\t\t%d\n", username, score);
        write(fd, new, written);
      }
      char new[100];
      int written = sprintf(new, "%s\t\t%d\n", cur_user, cur_score);
      write(fd, new, written);
    }

    /*
    int fd = open("leaderboard.txt", O_WRONLY | O_APPEND);
    char new[100];
    int written = sprintf(new, "%s\t\t%d\n", username, score);
    write(fd, new, written);
    close(fd);
    */

    // closes file and reopens semaphore
    fclose(fp);
  }
  close(fd);
  int e = remove("leaderboard.txt");
  if (e != 0){
    printf("error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  e = rename("temp.txt", "leaderboard.txt");
  if (e != 0){
    printf("error %d: %s\n", errno, strerror(errno));
    return -1;
  }

  sb.sem_op = 1;
  semop(semd, &sb, 1);
  return 0;
}

int resetLeaderboard(){
  printf("Resetting leaderboard...\n");
  int e = remove("leaderboard.txt");
  if (e != 0){
    printf("error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  int fd = open("leaderboard.txt", O_CREAT | O_TRUNC | O_RDWR, 0644);
  if (fd == -1){
    printf("error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  close(fd);
  printf("Success!\n");
  return 0;
}
