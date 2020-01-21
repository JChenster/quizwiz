#include "multi.h"


int removeSegs(){
  int shmd;
  // removing shared memory segments                                                                                                                                                                                                                                                                                                                                 
  shmd = shmget(NUMPLAYERSKEY, 16, 0);
  if (shmd == -1){
    printf("error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  shmctl(shmd, IPC_RMID, 0);
  //printf("shared memory for num players removed\n");                                                                                                                                                                                                                                                                                                               

  shmd = shmget(TURNSKEY, 16, 0);
  if (shmd == -1){
    printf("error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  shmctl(shmd, IPC_RMID, 0);
  //printf("shared memory for turns removed\n");                                                                                                                                                                                                                                                                                                                     

  shmd = shmget(QUESTIONSKEY, 260, 0);
  if (shmd == -1){
    printf("error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  shmctl(shmd, IPC_RMID, 0);
  //printf("shared memory for questions removed\n");                                                                                                                                                                                                                                                                                                                 

  shmd = shmget(QNUMKEY, 16, 0);
  if (shmd == -1){
    printf("error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  shmctl(shmd, IPC_RMID, 0);

  shmd = shmget(USER1KEY, 16, 0);
  if (shmd == -1){
    printf("error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  shmctl(shmd, IPC_RMID, 0);

  shmd = shmget(USER2KEY, 16, 0);
  if (shmd == -1){
    printf("error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  shmctl(shmd, IPC_RMID, 0);

  shmd = shmget(SCORE1KEY, 16, 0);
  if (shmd == -1){
    printf("error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  shmctl(shmd, IPC_RMID, 0);

  shmd = shmget(SCORE2KEY, 16, 0);
  if (shmd == -1){
    printf("error %d: %s\n", errno, strerror(errno));
    return -1;
  }
  shmctl(shmd, IPC_RMID, 0);

  return 0;
}
