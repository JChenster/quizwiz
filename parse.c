#include "parse.h"

// given a line of questions.txt, creates a struct question type accordingly
struct question parseSingleQuestion(char *line) {
  char delim[] = "|";
  struct question q;
  // Makes sure original is not modified
  char * temp = malloc(sizeof(line) - 1);
  strcpy(temp, line);
  char * temp2 = malloc(sizeof(line) - 1);
  temp2 = strtok(temp, delim);
  strncpy(q.question, temp2);
  printf("temp : %s\n", temp);
  q.a = strtok(NULL, delim);
  q.b = strtok(NULL, delim);
  q.c = strtok(NULL, delim);
  q.d = strtok(NULL, delim);
  q.ans = atoi(strtok(0, delim));
  free(temp);
  //printQuestion(q);
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

  /*
  printf("num_arr: [");
  for (int ind = 0; ind<n; ind++){
    printf(" %d,", num_arr[ind]);
  }
  printf("]\n");
  */

  // sort the indices from which to get questions from
  // soort(num_arr, n);

  // populating the array of questtions appropiately
  char ** ans = calloc(n, sizeof(char *));
  for (int i = 0; i < n; i++) {
    ans[i] = malloc (MAXCHAR+ 1);
    if (!ans[i]) {
      free(ans);
      return NULL;
    }
  }

  //int ind = 0;
  char *que;
  fp = fopen(filename, "r");
  //for (int i = 0; i < file_length && ind != n; i++) {
  for (int i = 0; i < file_length; i++) {
    que = fgets(textqs, MAXCHAR, fp); // fgets through file, line by line (i is the line it's currently at)
    /*
    if (num_arr[ind] == i) { // if the line is one of the random ones selected
      //ans[ind] = parseSingleQuestion(que); // parse the question and add it to the array of questions
      //printf("Testing the parse multiple questions:\n");
      //printQuestion(ans[ind]);
      strncpy(ans[ind], que, MAXCHAR);
      ind++;
    }
    */
    // places line in correct slot of array
    for (int j = 0; j<n; j++){
      if (num_arr[j] == i){
        strncpy(ans[j], que, MAXCHAR);
        break;
      }
    }

  }
  fclose(fp);

  /*
  printf("num_arr: [");
  for (int ind = 0; ind<n; ind++){
    printf(" %s,", ans[ind]);
  }
  printf("]\n");
  */
  return ans;
}

// selection sorts an int array
void soort(int arr[], int n) {
  int a, i, j;
  for (i = 0; i < n; ++i) {
    for (j = i + 1; j < n; ++j) {
      if (arr[i] > arr[j]) {
        a =  arr[i];
        arr[i] = arr[j];
        arr[j] = a;
      }
    }
  }
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

/*
int main() {
  char *f = "questions.txt";
  int n = 3;
  char ** q = getNQuestions(f, n);
  printQuestions(q);
}
*/
