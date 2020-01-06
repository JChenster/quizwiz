#include "parse.h"
#define MAXCHAR 1000

// given a line of questions.txt, creates a struct question type accordingly
struct question parseSingleQuestion(char *line) {
  char delim[] = "|";
  struct question q;
  q.question = strtok(line, delim);
  q.a = strtok(line, delim);
  q.b = strtok(line, delim);
  q.c = strtok(line, delim);
  q.d = strtok(line, delim);
  q.ans = atoi(strtok(line, delim));
  return q;
}

// gets a questions.txt, retrieves n random questions from the file
void getNQuestions(char *filename, int n, struct question ** q) {
  // open file
  FILE *fp;
  char textqs[MAXCHAR];
  fp = fopen(filename, "r");
  if (fp == NULL) {
        printf("Could not open file %s", filename);
        return;
  }

  // get number of questions on the file in total
  int file_length = 0;
  char c;
  for (c = getc(fp); c != EOF; c = getc(fp)) {
    if (c == '\n') file_length++;
  }
  fclose(fp);

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

  // sort the indices from which to get questions from
  soort(num_arr, n);

  // populating the array of questtions appropiately
  struct question * temp = calloc(n, sizeof(struct question));
  int ind = 0;
  char *que;
  fp = fopen(filename, "r");
  for (int i = 0; i < file_length && ind != n; i++) {
    que = fgets(textqs, MAXCHAR, fp); // fgets through file, line by line (i is the line it's currently at)
    if (num_arr[ind] == i) { // if the line is one of the random ones selected
      *(temp+ind) = parseSingleQuestion(que); // parse the question and add it to the array of questions
      ind++;
    }
  }
  free(*q);
  *q = temp;
  fclose(fp);
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

void printQuestions(struct question q[]){
  int n = 2;
  //printf("n is %d\n", n);
  for (int i = 0; i<n; i++){
    printQuestion(q[i]);
  }
}

void printQuestion(struct question q){
  printf("%s\nA. %s\nB. %s\nC. %s\nD. %s\nAns: %d\n", q.question, q.a, q.b, q.c, q.d, q.ans);
}

int main() {
  char *f = "questions.txt";
  struct question * q = calloc(2, sizeof(struct question));
  getNQuestions(f, 2, &q);
  printQuestions(q);
}
