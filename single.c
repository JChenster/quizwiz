#include "single.h"
#include "parse.h"

int main(){
  printf("-----------------------------------------\n");
  printf("Welcome to the single player quizwiz mode\n");
  printf("-----------------------------------------\n");
  game();
}

void game(){
  char *f = "questions.txt";
  printf("There are currently %d questions in the database\n", getMaxQuestions(f));
  printf("Enter number of questions desired: ");
  char input[2];
  fgets(input, 2, stdin);
  int n = atoi(input);
  printf("n is %d\n", n);
  char ** q = getNQuestions(f, n);
  //printQuestions(q, n);

  int response;
  for (int i = 0; i<n; i++){
    char * cur = q[i];
    struct question q = parseSingleQuestion(cur);
    printf("%d. %s\nA. %s\nB. %s\nC. %s\nD. %s\n", i + 1, q.question, q.a, q.b, q.c, q.d);
    printf("Enter answer: ");
    while ( ( response = getchar() ) != '\n' && response != EOF )
      ;
    response = getchar();
    printf("response: %c\n", response);
    if ('a' + q.ans - 1 == response){
      printf("correct\n");
    }
    else{
      printf("incorrect\n");
    }
  }
}
