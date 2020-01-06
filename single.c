#include "single.h"
#include "parse.h"

int main(){
  printf("Welcome to the single player quizwiz mode\n");

  char *f = "questions.txt";
  printf("There are currently %d questions in the database\n", getMaxQuestions(f));
  printf("Enter number of questions desired: ");
  int n;
  scanf("%d", &n);
  char ** q = getNQuestions(f, n);
  printQuestions(q, n);
}
