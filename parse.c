#include "parse.h"
#define MAXCHAR 1000

struct question {
  char * question;
  char * a;
  char * b;
  char * c;
  char * d;
  int ans;
};

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
void getNQuestions(char *filename, int n) {
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
  int ind = 0;
  char *q;
  fp = fopen(filename, "r");
  struct question questions[n];
  for (int i = 0; i < file_length && ind != n; i++) {
    q = fgets(textqs, MAXCHAR, fp); // fgets through file, line by line (i is the line it's currently at)
    if (num_arr[ind] == i) { // if the line is one of the random ones selected
      questions[ind] = parseSingleQuestion(q); // parse the question and add it to the array of questions
      ind++;
    }
  }
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

int main() {
  char *f = "questions.txt";
  getNQuestions(f, 2);
}
