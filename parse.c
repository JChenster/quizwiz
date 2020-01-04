#include "parse.h"
#define MAXCHAR 1000

struct question{
  char * question;
  char * a;
  char * b;
  char * c;
  char * d;
  int ans;
};

void getQuestion() {
  FILE *fp;
  char str[MAXCHAR];
  char delim[] = "|";
  char *filename = "questions.txt";
  struct question q;

  fp = fopen(filename, "r");
  fgets(str, MAXCHAR, fp);
  q.question = strtok(str, delim);
  q.a = strtok(str, delim);
  q.b = strtok(str, delim);
  q.c = strtok(str, delim);
  q.d = strtok(str, delim);
  q.ans = atoi(strtok(str, delim));
  printf("%s",q.question);
  fclose(fp);
}

int main() {
  getQuestion();
}
