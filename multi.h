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

#define NUMPLAYERSKEY 555222
#define TURNSKEY 444222
#define QUESTIONSKEY 333222
#define QNUMKEY 666222
#define USER1KEY 347216
#define USER2KEY 347840
#define SCORE1KEY 718323
#define SCORE2KEY 42069

int removeSegs();
