#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>

struct question {
  char * question;
  char * a;
  char * b;
  char * c;
  char * d;
  int ans;
};

void getQuestion(char *question);
void soort(int arr[], int n);
void getNQuestions(char *filename, int n, struct question ** q);
void printQuestions(struct question q[]);
void printQuestion(struct question q);
