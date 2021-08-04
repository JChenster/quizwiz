#include "single.h"
#include "parse.h"

int singleGame(char* f, int n){
  // runs game
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
  int semd = semget(SEMKEY, 1, IPC_CREAT | IPC_EXCL | 0644);
  if (semd == -1) {
    printf("error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  union semun us;
  semctl(semd, 0, SETVAL, us);
  printf("semaphore created\n");
  return 0;
}

int removeSemaphore(){
  int semd = semget(SEMKEY, 1, 0);
  if (semd == -1) {
    printf("error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  struct sembuf sb;
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

  
  struct stat md;
  stat("leaderboard.txt", &md);
  char temp[8];
  sprintf(temp, "%ld", md.st_size);
  int size = atoi(temp);
  printf("size of leaderboard: %dB\n", size);
  printf("Leaderboard last modified: %s", ctime(&md.st_atime));
  
  // reads the contents of the file
  // int size = 1000;
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
  // printf("trying to get in\n");
  int semd = semget(SEMKEY, 1, 0);
  if (semd == -1) {
    printf("error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  struct sembuf sb;
  semop(semd, &sb, 1);

  // creating temp file
  int fd = open("temp.txt", O_CREAT | O_TRUNC | O_WRONLY | O_APPEND, 0644);
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
    FILE *fp;
    char textqs[MAXCHAR];
    fp = fopen(filename, "r");
    if (fp == NULL) {
      printf("Could not open file %s", filename);
      return -1;
    }

    char * entry;
    char delim[] = "\t\t";
    int last = 1;

    for (int i = 0; i < file_length; i++) {
      // obtains username and score of player line by line
      entry = fgets(textqs, MAXCHAR, fp);
      char temp[MAXCHAR];
      strncpy(temp, entry, MAXCHAR);
      char cur_user[16];
      strncpy(cur_user, strtok(temp, delim), 16);
      int cur_score = atoi(strtok(0, delim));
      //printf("%s : %d\n", cur_user, cur_score);

      // if score to add is greater than current score
      if (score > cur_score && last){
        char new[100];
        int written = sprintf(new, "%s\t\t%d\n", username, score);
        write(fd, new, written);
        last = 0;
      }
      char new[100];
      int written = sprintf(new, "%s\t\t%d\n", cur_user, cur_score);
      write(fd, new, written);
    }
    if (last){
      char new[100];
      int written = sprintf(new, "%s\t\t%d\n", username, score);
      write(fd, new, written);
    }

    fclose(fp);
  }

  // close temp.txt and remove leaderboard.txt
  close(fd);
  int e = remove("leaderboard.txt");
  if (e != 0){
    printf("error %d: %s\n", errno, strerror(errno));
    return -1;
  }

  // rename temp.txt to leaderboard.txt
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
