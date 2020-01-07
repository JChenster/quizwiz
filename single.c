#include "single.h"
#include "parse.h"

int main(){
  printf("-----------------------------------------\n");
  printf("Welcome to the single player QuizWiz mode!\n");
  printf("-----------------------------------------\n");
  game();
}

void game(){
  char *f = "questions.txt";
  // receive input of number of questions desired
  printf("There are currently %d questions in the database\n", getMaxQuestions(f));
  printf("Enter number of questions desired: ");
  char input[2];
  fgets(input, 2, stdin);
  int n = atoi(input);
  //printf("n is %d\n", n);
  char ** q = getNQuestions(f, n);
  //printQuestions(q, n);

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
    while ( ( response = getchar() ) != '\n' && response != EOF )
      ;
    response = getchar();
    //printf("response: %c\n", response);
    if ('a' + q.ans - 1 == response || 'A' + q.ans - 1 == response){
      score++;
      printf("Correct! Your current score is: %d\n", score);
    }
    else{
      printf("Incorrect! Game over! Your score is %d\n", score);
      break;
    }
  }
}
