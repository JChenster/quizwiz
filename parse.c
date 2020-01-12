#include "parse.h"

// given a line of questions.txt, creates a struct question type accordingly
struct question parseSingleQuestion(char *line) {
  char delim[] = "|";
  struct question q;
  // Makes sure original is not modified
  char temp[260];
  strncpy(temp, line, 260);
  char temp2[128];
  strncpy(temp2, strtok(temp, delim), 128);
  strncpy(q.question, temp2, 128);
  strncpy(q.a, strtok(NULL, delim), 32);
  strncpy(q.b, strtok(NULL, delim), 32);
  strncpy(q.c, strtok(NULL, delim), 32);
  strncpy(q.d, strtok(NULL, delim), 32);
  q.ans = atoi(strtok(0, delim));
  return q;
}

// gets a questions.txt, retrieves n random questions from the file
char ** getNQuestions(char *filename, int n){
  // open file
  FILE *fp;
  char textqs[MAXCHAR];
  fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Could not open file %s", filename);
    return NULL;
  }

  // get number of questions on the file in total
  int file_length = 0;
  char c;
  for (c = getc(fp); c != EOF; c = getc(fp)) {
    if (c == '\n') file_length++;
  }
  fclose(fp);
  //printf("file length: %d\n", file_length);

  // generate n unique random line numbers to get questions from
  // oof for O(n^2)
  srand(time(NULL));
  int num_arr[n];
  for (int i = 0; i < n; i++) {
    num_arr[i] = rand() % (file_length);
    for (int j = 0; j < i; j++) {
      if (num_arr[i] == num_arr[j]) {
        num_arr[i] = rand() % (file_length);
        i--;
        break;
      }
    }
  }

  // populating the array of questtions appropiately
  char ** ans = calloc(n, sizeof(char *));
  for (int i = 0; i < n; i++) {
    ans[i] = malloc (MAXCHAR+ 1);
    if (!ans[i]) {
      free(ans);
      return NULL;
    }
  }

  char *que;
  fp = fopen(filename, "r");
  for (int i = 0; i < file_length; i++) {
    que = fgets(textqs, MAXCHAR, fp); // fgets through file, line by line (i is the line it's currently at)
    // places line in correct slot of array
    for (int j = 0; j<n; j++){
      if (num_arr[j] == i){
        strncpy(ans[j], que, MAXCHAR);
        break;
      }
    }

  }
  fclose(fp);

  return ans;
}

void printQuestions(char ** q, int n){
  for (int i = 0; i<n; i++){
    struct question cur = parseSingleQuestion(q[i]);
    printQuestion(cur);
  }
}

void printQuestion(struct question q){
  printf("%s\nA. %s\nB. %s\nC. %s\nD. %s\nAns: %d\n", q.question, q.a, q.b, q.c, q.d, q.ans);
}

int getMaxQuestions(char * filename){
  FILE *fp;
  char textqs[MAXCHAR];
  fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Could not open file %s", filename);
    return -1;
  }

  // get number of questions on the file in total
  int file_length = 0;
  char c;
  for (c = getc(fp); c != EOF; c = getc(fp)) {
    if (c == '\n') file_length++;
  }
  fclose(fp);
  return file_length;
}
